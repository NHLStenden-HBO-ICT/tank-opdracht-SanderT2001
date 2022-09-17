#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    Grid::Grid(int width, int height, int cell_size)
    {
        this->width = width;
        this->height = height;
        this->cell_size = cell_size;

        this->create(width, height, cell_size);
    }

    void Grid::create(int width, int height, int cell_size)
    {
        int total_x_cells = (int) width / cell_size;
        int total_y_cells = (int) height / cell_size;

        this->tank_cell_map.clear();

        this->cells.resize(total_x_cells);
        for (int x = 0; x < total_x_cells; x++) {
            this->cells[x] = std::vector<GridCell*>(total_y_cells);

            for (int y = 0; y < total_y_cells; y++) {
                this->cells[x][y] = new GridCell(x, y);
            }
        }
    }

    std::vector<Tank*> Grid::getTanksInRadius(Tank* tank, int radius) // O(1 x 1 x n) = O(n)
    {
        int backward_tank_collision_radius_x = (int) (*tank).position.x - radius;
        int backward_tank_collision_radius_y = (int) (*tank).position.y - radius;
        int forward_tank_collision_radius_x = (int) (*tank).position.x + radius;
        int forward_tank_collision_radius_y = (int) (*tank).position.y + radius;

        int backward_max_collision_cell_x = (int) backward_tank_collision_radius_x / this->getCellSize();
        int backward_max_collision_cell_y = (int) backward_tank_collision_radius_y / this->getCellSize();
        int forward_max_collision_cell_x = (int) forward_tank_collision_radius_x / this->getCellSize();
        int forward_max_collision_cell_y = (int) forward_tank_collision_radius_y / this->getCellSize();

        std::vector<Tank*> tanks_in_radius;
        for (int x = backward_max_collision_cell_x; x <= forward_max_collision_cell_x; x++) { // constante loop
            for (int y = backward_max_collision_cell_y; y <= forward_max_collision_cell_y; y++) { // constante loop
                std::vector<Tank*> tanks_in_cell = this->cells[x][y]->getTanks();
                for (Tank* tank_in_cell : tanks_in_cell) { // O(n)
                    if (tank_in_cell == tank) {
                        continue;
                    }

                    tanks_in_radius.push_back(tank_in_cell);
                }
            }
        }
        return tanks_in_radius;
    }

    void Grid::addTank(Tank* tank)
    {
        int cell_x = (int) (*tank).position.x / this->getCellSize();
        int cell_y = (int) (*tank).position.y / this->getCellSize();

        this->cells[cell_x][cell_y]->addTank(tank);
        this->tank_cell_map[tank] = this->cells[cell_x][cell_y];
    }

    void Grid::updateTank(Tank* tank)
    {
        GridCell* current_cell = this->tank_cell_map[tank];

        int cell_x = (int) (*tank).position.x / this->getCellSize();
        int cell_y = (int) (*tank).position.y / this->getCellSize();

        bool same_target_cell = ((cell_x == (*current_cell).getX()) && (cell_y == (*current_cell).getY()));
        if (same_target_cell) {
            return;
        }

        (*current_cell).removeTank(tank);

        this->cells[cell_x][cell_y]->addTank(tank);
        this->tank_cell_map[tank] = this->cells[cell_x][cell_y];
    }

    void Grid::removeTank(Tank* tank)
    {
        GridCell* current_cell = this->tank_cell_map[tank];

        (*current_cell).removeTank(tank);
        this->tank_cell_map.erase(tank);
    }

    int Grid::countTanks()
    {
        int total = 0;
        for (int x = 0; x < this->cells.size(); x++) {
            for (int y = 0; y < this->cells[x].size(); y++) {
                total += this->cells[x][y]->getTanksCount();
            }
        }
        return total;
    }
}

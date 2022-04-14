#pragma once

namespace St
{
    class St::GridCell;

    class Grid
    {
        public:
            Grid(int width, int height, int cell_size);
            void addTank(Tank* tank);
            void updateTank(Tank* tank);
            void removeTank(Tank* tank);
            std::vector<Tank*> getTanksInRadius(Tank* tank, int radius);
            int countTanks();

            const int getWidth() { return this->width; }
            const int getHeight() { return this->height; }
            const int getCellSize() { return this->cell_size; }

        private:
            int width;
            int height;
            int cell_size;

            std::vector<std::vector<GridCell*>> cells;
            std::unordered_map<Tank*, GridCell*> tank_cell_map;

            void create(int width, int height, int cell_size);
    };
};

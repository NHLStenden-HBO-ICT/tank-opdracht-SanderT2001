#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridCell::GridCell(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    void GridCell::addTank(Tank* tank)
    {
        this->tanks.push_back(tank);
    }

    void GridCell::removeTank(Tank* tank)
    {
        // @TODO https://www.fluentcpp.com/2018/09/18/how-to-remove-pointers-from-a-vector-in-cpp/
        // TODO: Dit is niet efficient

        std::vector<Tank*> new_tanks;

        for (Tank* tank_in_cell : this->tanks) {
            if (tank_in_cell == tank) {
                continue;
            }

            new_tanks.push_back(tank_in_cell);
        }

        this->tanks = new_tanks;
    }
}

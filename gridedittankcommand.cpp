#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridEditTankCommand::GridEditTankCommand(Tank* tank)
    {
        this->tank = tank;
    }

    void GridEditTankCommand::execute(Grid* grid)
    {
        std::cout << "Grid Edit Tank Command: EXECUTE!" << std::endl;
    }
}

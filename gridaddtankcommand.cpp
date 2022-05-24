#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridAddTankCommand::GridAddTankCommand(Tank* tank)
    {
        this->tank = tank;
    }

    void GridAddTankCommand::execute()
    {
        std::cout << "Grid Add Tank Command: EXECUTE!" << std::endl;
    }
}

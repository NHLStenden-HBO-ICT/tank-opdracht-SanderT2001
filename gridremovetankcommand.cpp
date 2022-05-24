#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridRemoveTankCommand::GridRemoveTankCommand(Tank* tank)
    {
        this->tank = tank;
    }

    void GridRemoveTankCommand::execute()
    {
        std::cout << "Grid Remove Tank Command: EXECUTE!" << std::endl;
    }
}

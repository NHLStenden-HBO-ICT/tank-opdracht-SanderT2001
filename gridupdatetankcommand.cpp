#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridUpdateTankCommand::GridUpdateTankCommand(Tank* tank)
    {
        this->tank = tank;
    }

    void GridUpdateTankCommand::execute(Grid* grid)
    {
        grid->updateTank(this->tank);
    }
}

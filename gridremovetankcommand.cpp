#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridRemoveTankCommand::GridRemoveTankCommand(Tank* tank)
    {
        this->tank = tank;
    }

    void GridRemoveTankCommand::execute(Grid* grid)
    {
        grid->removeTank(this->tank);
    }
}

#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridChangeManager::GridChangeManager(St::Grid* grid)
    {
        this->grid = grid;
    }

    void GridChangeManager::addToQueue(GridChangeCommand* command)
    {
        this->command_queue.push_back(command);
    }

    void GridChangeManager::commitChanges()
    {
        for (GridChangeCommand* command : this->command_queue) {
            command->execute(this->grid);
        }
    }
}

#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    GridChangeManager::GridChangeManager()
    {
    }

    void GridChangeManager::addToQueue(GridChangeCommand* command)
    {
        std::cout << "Grid Change Manager: Add To Queue" << std::endl;
    }

    void GridChangeManager::commitChanges()
    {
        std::cout << "Grid Change Manager: Commit Changes" << std::endl;
    }
}

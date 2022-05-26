#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    SortTanksHealth::SortTanksHealth(St::SortTanksHealthStrategy* strategy)
    {
        this->strategy = strategy;
    }

    std::vector<const Tank*> SortTanksHealth::getSortedTanks(std::vector<Tank*> tanks)
    {
        return this->strategy->execute(tanks);
    }
}

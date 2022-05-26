#pragma once

namespace St
{
    class SortTanksHealth
    {
        public:
            SortTanksHealth(St::SortTanksHealthStrategy* strategy);

            std::vector<const Tank*> getSortedTanks(std::vector<Tank*> tanks);

        private:
            St::SortTanksHealthStrategy* strategy;
    };
};

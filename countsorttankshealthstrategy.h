#pragma once

namespace St
{
    class CountSortTanksHealthStrategy : public SortTanksHealthStrategy
    {
        public:
            CountSortTanksHealthStrategy();

            virtual std::vector<const Tank*> execute(std::vector<Tank*> tanks);

        private:
            Tank* tank;

            int tank_max_health = 1000;
    };
};

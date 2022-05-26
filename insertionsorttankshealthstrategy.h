#pragma once

namespace St
{
    class InsertionSortTanksHealthStrategy : public SortTanksHealthStrategy
    {
        public:
            InsertionSortTanksHealthStrategy();

            virtual std::vector<const Tank*> execute(std::vector<Tank*> tanks);

        private:
            Tank* tank;
    };
};

#pragma once

namespace St
{
    class SortTanksHealthStrategy
    {
        public:
            // Use `~` (virtual destructor), has to do with moving the pointer to the implementing class.
            virtual ~SortTanksHealthStrategy() {}

            // Interface method must be assigned to 0
            virtual std::vector<const Tank*> execute(std::vector<Tank*> tanks) = 0;

        private:
    };
};

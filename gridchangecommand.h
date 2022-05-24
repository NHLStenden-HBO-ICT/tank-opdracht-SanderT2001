#pragma once

namespace St
{
    class GridChangeCommand
    {
        public:
            // Use `~` (virtual destructor), has to do with moving the pointer to the implementing class.
            virtual ~GridChangeCommand() {}
            // Interface method must be assigned to 0
            virtual void execute() = 0;

        private:
    };
};

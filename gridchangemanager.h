#pragma once

namespace St
{
    class GridChangeManager
    {
        public:
            GridChangeManager();

            void addToQueue(GridChangeCommand* command);
            void commitChanges();

        private:
            std::vector<GridChangeCommand*> command_queue;
    };
};

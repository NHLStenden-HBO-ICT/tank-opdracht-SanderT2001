#pragma once

namespace St
{
    class GridChangeManager
    {
        public:
            GridChangeManager(St::Grid* grid);

            void addToQueue(GridChangeCommand* command);
            void commitChanges();

        private:
            St::Grid* grid;
            std::vector<GridChangeCommand*> command_queue;
    };
};

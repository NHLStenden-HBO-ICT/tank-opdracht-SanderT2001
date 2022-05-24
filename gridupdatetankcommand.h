#pragma once

namespace St
{
    class GridUpdateTankCommand : public GridChangeCommand
    {
        public:
            GridUpdateTankCommand(Tank* tank);
            virtual void execute(Grid* grid);

        private:
            Tank* tank;
    };
};

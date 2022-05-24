#pragma once

namespace St
{
    class GridEditTankCommand : public GridChangeCommand
    {
        public:
            GridEditTankCommand(Tank* tank);
            virtual void execute();

        private:
            Tank* tank;
    };
};

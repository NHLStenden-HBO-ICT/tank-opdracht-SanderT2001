#pragma once

namespace St
{
    class GridCell
    {
        public:
            GridCell(int x, int y);

            int getX() { return this->x; }
            int getY() { return this->y; }

            std::vector<Tank*> getTanks() { return this->tanks; }
            int getTanksCount() { return this->tanks.size(); }
            void addTank(Tank* tank);
            void removeTank(Tank* tank);

        private:
            int x;
            int y;

            std::vector<Tank*> tanks;
    };
};

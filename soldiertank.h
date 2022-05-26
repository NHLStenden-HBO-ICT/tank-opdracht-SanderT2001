#pragma once

namespace St
{
    class SoldierTank : public TankTeamMember
    {
        public:
            SoldierTank(Tank* tank);

            int getHealth() { return this->health; }
            int getCombinedHealth();

            void addTankUnderCommand(TankTeamMember* tank) { this->tanks_to_manage.push_back(tank); }

        private:
            int health;
            std::vector<TankTeamMember*> tanks_to_manage;
    };
};

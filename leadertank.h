#pragma once

namespace St
{
    class LeaderTank : public TankTeamMember
    {
        public:
            LeaderTank(Tank* tank);

            std::string getName() { return this->name; }
            void setName(std::string value) { this->name = value; }

            int getHealth() { return this->health; }
            int getCombinedHealth();

            void addTankUnderCommand(TankTeamMember* tank) { this->tanks_to_manage.push_back(tank); }

        private:
            std::string name;
            int health;
            std::vector<TankTeamMember*> tanks_to_manage;
    };
};

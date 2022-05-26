#pragma once

namespace St
{
    class TraineeTank : public TankTeamMember
    {
        public:
            TraineeTank(Tank* tank);

            int getHealth() { return this->health; }
            int getCombinedHealth();

        private:
            int health;
    };
};

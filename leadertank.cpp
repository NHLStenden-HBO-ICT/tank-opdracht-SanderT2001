#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    LeaderTank::LeaderTank(Tank* tank)
    {
        this->health = tank->health;
    }

    int LeaderTank::getCombinedHealth()
    {
        int total = this->health;

        for (TankTeamMember* tank : this->tanks_to_manage) {
            total += tank->getCombinedHealth();
        }

        return total;
    }
}

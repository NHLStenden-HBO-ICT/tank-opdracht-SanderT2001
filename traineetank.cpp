#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    TraineeTank::TraineeTank(Tank* tank)
    {
        this->health = tank->health;
    }

    int TraineeTank::getCombinedHealth()
    {
        return this->health;
    }
}

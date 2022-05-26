#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    InsertionSortTanksHealthStrategy::InsertionSortTanksHealthStrategy()
    {
    }

    std::vector<const Tank*> InsertionSortTanksHealthStrategy::execute(std::vector<Tank*> tanks)
    {
        std::vector<const Tank*> sorted_tanks;
        sorted_tanks.reserve(tanks.size());
        sorted_tanks.emplace_back(tanks.at(0));

        for (int i = 0; i < tanks.size(); i++)
        {
            const Tank* current_tank = tanks.at(i);

            for (int s = (int)sorted_tanks.size() - 1; s >= 0; s--)
            {
                const Tank* current_checking_tank = sorted_tanks.at(s);

                if ((current_checking_tank->compare_health(*current_tank) <= 0))
                {
                    sorted_tanks.insert(1 + sorted_tanks.begin() + s, current_tank);
                    break;
                }

                if (s == 0)
                {
                    sorted_tanks.insert(sorted_tanks.begin(), current_tank);
                    break;
                }
            }
        }

        return sorted_tanks;
    }
}

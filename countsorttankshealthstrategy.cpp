#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    CountSortTanksHealthStrategy::CountSortTanksHealthStrategy()
    {
    }

    std::vector<const Tank*> CountSortTanksHealthStrategy::execute(std::vector<Tank*> tanks)
    {
        std::vector<int> tanks_health_list(tanks.size());
        for (Tank* tank : tanks) {
            tanks_health_list.push_back(tank->health);
        }

        std::vector<int> tanks_health_count_list(tank_max_health);
        for (int i = 0; i <= tanks_health_count_list.size(); i++) {
            tanks_health_count_list[i] = 0;
        }
        for (int tank_health : tanks_health_list) {
            tanks_health_count_list[tank_health] = tanks_health_count_list[tank_health]+1;
        }

        std::vector<int> tanks_health_index(tank_max_health);
        for (int i = 0; i <= tanks_health_index.size(); i++) {
            tanks_health_index[i] = 0;
        }

        for (int i = 0; i <= tanks_health_count_list.size(); i++) {
            int value = tanks_health_count_list[i];

            if (i == 0) {
                tanks_health_index[i] = value;
            } else {
                int previous_value = tanks_health_index[i-1];
                tanks_health_index[i] = previous_value + value;
            }
        }

        std::vector<const Tank*> sorted_tanks(tanks_health_index[tanks_health_index.size()]);
        for (Tank* tank : tanks) {
            int health = tank->health;
            int position_in_sorted_tanks = tanks_health_index[health];

            sorted_tanks[position_in_sorted_tanks] = tank;

            tanks_health_index[health] = tanks_health_index[health]-1;
        }

        // Remove NULL Pointers
        sorted_tanks.erase(std::remove(sorted_tanks.begin(), sorted_tanks.end(), nullptr), sorted_tanks.end());

        return sorted_tanks;
    }
}

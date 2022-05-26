#pragma once

namespace St
{
    class TankTeamMember
    {
        public:
            // Use `~` (virtual destructor), has to do with moving the pointer to the implementing class.
            virtual ~TankTeamMember() {}

            virtual int getHealth() = 0;
            virtual int getCombinedHealth() = 0;

        private:
    };
};

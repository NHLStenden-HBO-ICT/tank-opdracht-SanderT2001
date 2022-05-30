#pragma once

namespace St
{
    class Timer
    {
        public:
            Timer();
            void start();
            void stop();
            void printElapsedTime();

        private:
            std::chrono::time_point<std::chrono::system_clock> start_time;
            std::chrono::time_point<std::chrono::system_clock> end_time;
    };
};

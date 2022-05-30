#include "precomp.h" // include (only) this in every .cpp file

namespace St
{
    Timer::Timer()
    {
    }

    void Timer::start()
    {
        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::milliseconds;

        this->start_time = high_resolution_clock::now();
    }

    void Timer::stop()
    {
        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::milliseconds;

        this->end_time = high_resolution_clock::now();
    }

    void Timer::printElapsedTime()
    {
        using std::chrono::high_resolution_clock;
        using std::chrono::duration_cast;
        using std::chrono::duration;
        using std::chrono::milliseconds;

        /* Getting number of milliseconds as an integer. */
        auto ms_int = duration_cast<milliseconds>(this->end_time - this->start_time);
        std::cout << ms_int.count() << "ms\n";
    }
}

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

namespace Benchmarking
{
    /* source: https://stackoverflow.com/questions/1861294/how-to-calculate-execution-time-of-a-code-snippet-in-c */
    /* Remove if already defined */
    //typedef unsigned long long uint64;

    /* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on both
     * windows and linux. */

    inline double GetTimeMs64()
    {
#ifdef _WIN32
        /* Windows */
        FILETIME ft;
        LARGE_INTEGER li;

        /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
         * to a LARGE_INTEGER structure. */
        GetSystemTimeAsFileTime(&ft);
        li.LowPart = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;

        double ret = li.QuadPart;
        ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
        ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3) intervals */
#else
        /* Linux */
        struct timeval tv;

        gettimeofday(&tv, NULL);

        double ret = tv.tv_usec;
        /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
        ret /= 1000;

        /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
        ret += (tv.tv_sec * 1000);

#endif
        return ret;
    }

    /* Returns the amount of nanoseconds elapsed since the UNIX epoch */
    inline double GetTimeNs64()
    {
        /* milliseconds to nano */
        return GetTimeMs64() * 1000;
    }
}
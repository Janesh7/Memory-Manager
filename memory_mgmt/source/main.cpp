#include <stdio.h>
#include "memory_mgr.hpp"
#include "timer.hpp"

int main ()
{
        void *  data                = nullptr;
        double  start               = 0;
        double  stop                = 0;
        double  time_elapsed_custom = 0;
        double  time_elapsed_system = 0;
        double  percentage_faster   = 0;

    // Measure time for system malloc/free
    start = Timer::GetCurrentTime ();

    for (int j = 0; j < BIG_NUM; j++) {

        data = malloc (SIZE_CHUNK_UNDER_8);
        free (data);
        data = malloc (SIZE_CHUNK_UNDER_16);
        free (data);
        data = malloc (SIZE_CHUNK_UNDER_32);
        free (data);
        data = malloc (SIZE_CHUNK_UNDER_64);
        free (data);
        data = malloc (SIZE_CHUNK_UNDER_128);
        free (data);
        data = malloc (SIZE_CHUNK_UNDER_256);
        free (data);
        data = malloc (SIZE_CHUNK_UNDER_512);
        free (data);
        data = malloc (SIZE_CHUNK_ABOVE_MAX);
        free (data);

    }

    stop = Timer::GetCurrentTime ();
    time_elapsed_system = stop - start;

    printf ("\nSystem malloc/free time for 10,00,000 allocations and frees: %.6f seconds\n", time_elapsed_system);

    // Measure time for custom Malloc/Free
    start = Timer::GetCurrentTime ();

    for (int j = 0; j < BIG_NUM; j++) {

        data = Malloc (SIZE_CHUNK_UNDER_8);
        Free (data);
        data = Malloc (SIZE_CHUNK_UNDER_16);
        Free (data);
        data = Malloc (SIZE_CHUNK_UNDER_32);
        Free (data);
        data = Malloc (SIZE_CHUNK_UNDER_64);
        Free (data);
        data = Malloc (SIZE_CHUNK_UNDER_128);
        Free (data);
        data = Malloc (SIZE_CHUNK_UNDER_256);
        Free (data);
        data = Malloc (SIZE_CHUNK_UNDER_512);
        Free (data);
        data = Malloc (SIZE_CHUNK_ABOVE_MAX);
        Free (data);

    }

    stop = Timer::GetCurrentTime ();
    time_elapsed_custom = stop - start;

    printf ("\nCustom Malloc/free time for 10,00,000 allocations and frees: %.6f seconds\n", time_elapsed_custom);


    // Calculate percentage difference
    percentage_faster = ((time_elapsed_system - time_elapsed_custom) / time_elapsed_system) * 100;

    printf ("\nYour custom Malloc/free is %.2f%% faster than system malloc/free\n", percentage_faster);

    return 0;
}

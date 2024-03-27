#include <stdlib.h>
#include <limits.h>
#include "sched.h"

static int *active_processes = NULL;
static int process_count = 0;
static int current_process = 0;
static int *remaining_time = NULL;

int sched_init(void)
{
    return 0;
}

void sched_clean(void)
{
    if (active_processes)
    {
        free(active_processes);
        active_processes = NULL;
    }
    if (remaining_time)
    {
        free(remaining_time);
        remaining_time = NULL;
    }
    process_count = 0;
    current_process = 0;
}

int add_proc(void)
{
    return process_count++;
}

int sched(int time, int cont)
{
    int i;

    if (!active_processes)
    {
        active_processes = (int *)malloc(process_count * sizeof(int));
        if (!active_processes)
        {
            perror("malloc");
            return -1;
        }
        remaining_time = (int *)malloc(process_count * sizeof(int));
        if (!remaining_time)
        {
            perror("malloc");
            return -1;
        }
        for (i = 0; i < process_count; i++)
        {
            active_processes[i] = 1;
            remaining_time[i] = 0;
        }
        return current_process;
    }

    active_processes[current_process] = cont;
    remaining_time[current_process] += time;

    int next_process = -1;
    int min_remaining_time = INT_MAX;
    for (i = 0; i < process_count; i++)
    {
        if (active_processes[i] && remaining_time[i] < min_remaining_time)
        {
            min_remaining_time = remaining_time[i];
            next_process = i;
        }
    }

    current_process = next_process;
    return current_process;
}

int sched_fin(void)
{
    sched_clean();
    return 0;
}
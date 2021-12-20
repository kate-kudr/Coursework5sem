//
// Created by Катя on 05.12.2021.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string.h>

#define RM_SCHEDULER 0
#define EDF_SCHEDULER 1

#define SCHEDULER_TYPE RM_SCHEDULER

#define MAX_PROCESSES 16

struct task{
    int pid;
    int period;
    int execution_time;
    int deadline;
    float priority;
    int attached;
    int *function;
};

static struct task tasklist[MAX_PROCESSES];

int create_task(int period, int execution_time, int deadline, void *function);

int idle_task();

int processes_number();

int hyperperiod();

int scheduler();

#endif //CONFIG_H

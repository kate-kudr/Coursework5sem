#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "config.h"

//EDF
int earliest_deadline;
int earliest_deadline_index;
int remains_capacity[MAX_PROCESSES];
int next_deadline[MAX_PROCESSES];
int process_new_period[MAX_PROCESSES];

int get_earliest_deadline();

//RMS
int shortest_period;
int shortest_period_index;

int get_shortest_period();

void func1();

#endif //SCHEDULER_H

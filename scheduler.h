#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "config.h"

//both
int remains_capacity[MAX_PROCESSES];
int next_deadline[MAX_PROCESSES];
int process_new_period[MAX_PROCESSES];

//EDF
int earliest_deadline;
int earliest_deadline_index;

int get_earliest_deadline();

void check_new_period_edf();

//RMS
int shortest_period;
int shortest_period_index;

int get_shortest_period();

void check_new_period_rms();

#endif //SCHEDULER_H

#include "config.h"
#include "scheduler.h"

int create_task(int period, int execution_time, int deadline, void *function) {
    int i = 0;
    while (i < MAX_PROCESSES) {
        if (tasklist[i].attached != 1) {
            tasklist[i].pid = i;
            tasklist[i].period = period;
            tasklist[i].execution_time = execution_time;
            tasklist[i].deadline = deadline;
            tasklist[i].function = function;
            tasklist[i].attached = 1;
            break;
        }
        i++;
    }
    return 0;
}


int idle_task() {
    printf("\n");
    return 0;
}

int processes_number() {
    int i;
    int number = 0;
    for (int i = 0; i < MAX_PROCESSES; ++i) {
        if (tasklist[i].attached == 1) {
            number++;
        }
    }
    return number;
}

int hyperperiod() {
    int i;
    int hyperperiod = 0;
    for (i = 0; i < processes_number(); ++i) {
        if (tasklist[i].period > hyperperiod) {
            hyperperiod = tasklist[i].period;
        }
    }
    return hyperperiod;
}

int get_earliest_deadline() {
    earliest_deadline = hyperperiod();
    earliest_deadline_index = -1;
    int j;
    for (j = 0; j < processes_number(); j++) {
        if (remains_capacity[j] > 0) {
            if (earliest_deadline > next_deadline[j]) {
                earliest_deadline = next_deadline[j];
                earliest_deadline_index = j;
            }
        }
    }
    remains_capacity[earliest_deadline_index]--;
    return earliest_deadline_index;
}

int get_shortest_period() {
    shortest_period = hyperperiod();
    shortest_period_index = -1;
    int i;
    for (i = 0; i < processes_number(); i++) {
        if (remains_capacity[i] > 0) {
            if (shortest_period > next_deadline[i]) {
                shortest_period = next_deadline[i];
                shortest_period_index = i;
            }
        }
    }
    remains_capacity[shortest_period_index]--;
    return shortest_period_index;
}

void check_new_period_edf() {
    int i;
    for (i = 0; i < processes_number(); i++) {
        if (process_new_period[i] == (tasklist[i].period - 1)) {
            next_deadline[i] = tasklist[i].deadline;
            remains_capacity[i] = tasklist[i].execution_time;
            process_new_period[i] = 0;
        } else {
            if (next_deadline[i] > 0) {
                next_deadline[i]--;
            }
            process_new_period[i]++;
        }
    }
}

void check_new_period_rms() {
    int i;
    for (i = 0; i < processes_number(); i++) {
        if (process_new_period[i] == (tasklist[i].period - 1)) {
            next_deadline[i] = tasklist[i].period;
            remains_capacity[i] = tasklist[i].execution_time;
            process_new_period[i] = 0;
        } else {
            if (next_deadline[i] > 0) {
                next_deadline[i]--;
            }
            process_new_period[i]++;
        }
    }
}

int scheduler() {
    int i;
    void (*p)(void);

    if (SCHEDULER_TYPE == EDF_SCHEDULER) {
        for (i = 0; i < processes_number(); i++) {
            next_deadline[i] = tasklist[i].deadline;
            remains_capacity[i] = tasklist[i].execution_time;
            process_new_period[i] = 0;
        }

        while (1) {
            for (i = 0; i < processes_number(); i++) {

                get_earliest_deadline();

                if (earliest_deadline_index == -1) {
                    idle_task();
                } else {
                    p = (void *) tasklist[earliest_deadline_index].function;
                    (*p)();
                }

                check_new_period_edf();
            }
        }
    }
    if (SCHEDULER_TYPE == RM_SCHEDULER) {

        for (
                i = 0;
                i < processes_number();
                i++) {
            next_deadline[i] = tasklist[i].
                    period;
            remains_capacity[i] = tasklist[i].
                    execution_time;
            process_new_period[i] = 0;
        }

        while (1) {
            for (
                    i = 0;
                    i < processes_number();
                    i++) {

                get_shortest_period();

                if (shortest_period_index == -1) {
                    idle_task();

                } else {
                    p = (void *) tasklist[shortest_period_index].function;
                    (*p)();
                }

                check_new_period_rms();

            }
        }
    }
    return 0;
}

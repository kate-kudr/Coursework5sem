#include "config.h"
#include "scheduler.h"

int task0();
int task1();
int task2();

int main() {
    create_task(5, 2, 4, task0);
    create_task(10, 2, 8, task1);
    create_task(20, 3, 7, task2);
//    create_task(4, 1, 4, task0);
//    create_task(6, 2, 6, task1);
//    create_task(12, 3, 12, task2);
    scheduler();
    return 0;
}

int task0() {
    printf("Task1 is running\n");
    return 0;
}

int task1() {
    printf("Task2 is running\n");
    return 0;
}

int task2() {
    printf("Task3 is running\n");
    return 0;
}
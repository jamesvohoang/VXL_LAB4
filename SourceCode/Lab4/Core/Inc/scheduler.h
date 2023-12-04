#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define SCH_MAX_TASKS 10

typedef struct
{
    void (*pTask)();
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskId;
}task;

extern task schTasks[SCH_MAX_TASKS];
extern task nextTask;

void SchUpdate(void);
void SchDispatchTasks(void);
uint32_t SchAddTask(void (*func)(), uint16_t delay, uint16_t period);
uint8_t SchDeleteTask(uint32_t id);

#endif /* INC_SCHEDULER_H_ */
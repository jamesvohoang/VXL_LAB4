#include "scheduler.h"

task schTasks[SCH_MAX_TASKS];
//task nextTask;


void SchUpdate(void)
{
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
    {
        if(schTasks[i].pTask != 0x0000)
        {
            if(schTasks[i].Delay == 0)
            {
                schTasks[i].RunMe = 1;
            }
            else
            {
                schTasks[i].Delay -= 1;
            }
        }
    }
}

void SchDispatchTasks(void)
{
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
    {
        if(schTasks[i].RunMe)
        {
            schTasks[i].RunMe = 0;
            (*schTasks[i].pTask)();

            task *temp = (task *)malloc(sizeof(task));
            memcpy(temp, &schTasks[i], sizeof(task));

            if(schTasks[i].Period == 0)
            {
                SchDeleteTask(schTasks[i].TaskId);
            }
            else
            {
                schTasks[i].Delay = temp->Period;
            }

            free(temp);
        }
    }
}

uint32_t SchAddTask(void (*func)(), uint16_t delay, uint16_t period)
{
    // Check blank slot in queue
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
    {
        if(schTasks[i].pTask == 0x0000)
        {
            schTasks[i].pTask = func;
            schTasks[i].Delay = delay;
            schTasks[i].Period = period;
            schTasks[i].TaskId = i + 1;

            return schTasks[i].TaskId;
        }
    }
    return 0;
}

uint8_t SchDeleteTask(uint32_t id)
{
    if(id > SCH_MAX_TASKS)
        return 0;

    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
    {
        if(schTasks[i].TaskId == id)
        {
            for (uint8_t j = i; j < SCH_MAX_TASKS - 1; j++)
            {
                schTasks[j] = schTasks[j+1];
            }
            schTasks[SCH_MAX_TASKS-1].pTask = 0x0000;

            return 1;
        }
    }
    return 0;
}
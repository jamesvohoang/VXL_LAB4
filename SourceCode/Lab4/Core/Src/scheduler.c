#include "scheduler.h"

task schTasks[SCH_MAX_TASKS];
//task nextTask;


void SchUpdate(void)
{
    for (uint8_t i = 0; i < SCH_MAX_TASKS; i++)
    {
        // Check is task need to be done or an blank slot in schTasks array
        if(schTasks[i].pTask != 0x0000)
        {
            // Check is task need to be invoked
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
        // Check does it need to invoke task
        if(schTasks[i].RunMe)
        {
            schTasks[i].RunMe = 0;
            // Invoke task
            (*schTasks[i].pTask)();

            // Copy all attribute of task into a temporary pointer
            task *temp = (task *)malloc(sizeof(task));
            memcpy(temp, &schTasks[i], sizeof(task));

            if(schTasks[i].Period == 0)
            {
                // Delete if period == 0, that means this task just invoke one time
                SchDeleteTask(schTasks[i].TaskId);
            }
            else
            {
                // Extend delay time of task
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
            schTasks[SCH_MAX_TASKS-1].RunMe = 0;
            schTasks[SCH_MAX_TASKS-1].TaskId = 0;

            return 1;
        }
    }
    return 0;
}
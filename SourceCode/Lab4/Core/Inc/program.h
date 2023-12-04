#ifndef INC_PROGRAM_H_
#define INC_PROGRAM_H_

#include "scheduler.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim2;

void ScheduleInit(void);

void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);
void Task5(void);

#endif /* INC_PROGRAM_H_ */
#include "program.h"

void ScheduleInit(void)
{
    HAL_TIM_Base_Start_IT(&htim2);
    SchAddTask(Task1, 0, 10);
    SchAddTask(Task2, 100, 20);
    SchAddTask(Task3, 200, 0);
    SchAddTask(Task4, 300, 40);
    SchAddTask(Task5, 500, 50);
}

void Task1(void)
{   
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
}

void Task2(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
}

void Task3(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}

void Task4(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
}

void Task5(void)
{
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == htim2.Instance)
    {
		SchUpdate();
	}
}
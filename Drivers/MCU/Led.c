#include "stm32f1xx_hal.h"
#include "Led.h"
extern int led_count;
void led_on(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void led_off(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
}

void led_test(void)
{   for (size_t i = 0; i < 10; i++)
{
    /* code */ led_on();
    HAL_Delay(50);
    led_off();
    HAL_Delay(50);
    led_count++;
}


   
}

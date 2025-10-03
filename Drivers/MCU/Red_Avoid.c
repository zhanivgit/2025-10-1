
#include "gpio.h"
#include "stm32f1xx_hal.h"
//当检测到东西的时候返回0，没有东西的时候返回1
uint8_t Red_Avoid_dectect(void)
{
    return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
}

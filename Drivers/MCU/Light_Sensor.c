#include "gpio.h"
//当光敏传感器的灯不亮的时候，返回1,亮是有光
//当光敏传感器的灯亮时，返回0
uint8_t Light_Sensor_dectect(void)
{
	return HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11);
	
}

#ifndef RGBLED_H_
#define RGBLED_H_

#include "stm32f1xx_hal.h"

// 定义RGB LED的引脚和定时器通道
// 假设PA2连接到TIM2_CH3 (Red)
// 假设PB3连接到TIM2_CH2 (Green)
// 假设PA15连接到TIM2_CH1 (Blue)

extern TIM_HandleTypeDef htim2;

void RGB_LED_Init(void);
void RGB_LED_SetColor(uint8_t red, uint8_t green, uint8_t blue);

#endif /* RGBLED_H_ */

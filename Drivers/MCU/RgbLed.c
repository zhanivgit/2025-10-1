#include "RgbLed.h"
#include "stdint.h" // 添加此行

void RGB_LED_Init(void)
{
    // 启动TIM2的PWM通道
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3); // PA2 (Red)
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2); // PB3 (Green)
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // PA15 (Blue)
}

void RGB_LED_SetColor(uint8_t red, uint8_t green, uint8_t blue)
{
    // 将8位颜色值映射到TIM2的Period值 (65535)
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, (uint32_t)red * 257);   // Red (255 * 257 ≈ 65535)
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, (uint32_t)green * 257); // Green
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (uint32_t)blue * 257);  // Blue
}

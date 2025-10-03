#ifndef __HR04_H
#define __HR04_H

#include "stm32f1xx_hal.h"

extern volatile uint8_t TIM4CH3_CAPTURE_STA;  // 捕获状态
extern volatile uint32_t TIM4CH3_CAPTURE_VAL; // 捕获值

void CHL_capture(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif

#include "gpio.h"
#include "stm32f1xx_hal.h"
#include "tim.h"
#include "Hr04.h"

#define TIM4CH3_CAPTURE_FALLING 0x40  // 标记：已捕获上升沿，等待下降沿
#define TIM4CH3_CAPTURE_SUCCESS 0x80  // 标记：捕获成功

volatile uint8_t TIM4CH3_CAPTURE_STA = 0;  // 捕获状态/溢出次数
volatile uint32_t TIM4CH3_CAPTURE_VAL = 0; // 最终捕获到的脉冲宽度值

void CHL_capture(void)
{
    uint32_t i;
    
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
    for(i=0;i<72*40;i++)
        __NOP();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
}

// TIM4通道3输入捕获回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4)
    {
        if((TIM4CH3_CAPTURE_STA & 0x80) == 0) //还未捕获成功
        {
            if(TIM4CH3_CAPTURE_STA & 0x40) //已捕获到上升沿，正在等待下降沿
            {
                if((TIM4CH3_CAPTURE_STA & 0x3F) == 0x3F) //高电平时间太长
                {
                    TIM4CH3_CAPTURE_STA |= 0x80; //标记捕获完成
                    TIM4CH3_CAPTURE_VAL = 0xFFFF;
                }
                else
                {
                    TIM4CH3_CAPTURE_STA++; //溢出计数加一
                }
            }
        }
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM4)
    {
        if((TIM4CH3_CAPTURE_STA & 0x80) == 0) //还未捕获成功
        {
            if(TIM4CH3_CAPTURE_STA & 0x40) //已捕获到下降沿
            {
                TIM4CH3_CAPTURE_STA |= 0x80; //标记捕获完成
                TIM4CH3_CAPTURE_VAL = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_RISING); //恢复为上升沿捕获
            }
            else //捕获到上升沿
            {
                TIM4CH3_CAPTURE_STA = 0;
                TIM4CH3_CAPTURE_VAL = 0;
                TIM4CH3_CAPTURE_STA |= 0x40; //标记已捕获到上升沿
                __HAL_TIM_DISABLE(htim);
                __HAL_TIM_SET_COUNTER(htim, 0);
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_3, TIM_INPUTCHANNELPOLARITY_FALLING); //切换为下降沿捕获
                __HAL_TIM_ENABLE(htim);
            }
        }
    }
}
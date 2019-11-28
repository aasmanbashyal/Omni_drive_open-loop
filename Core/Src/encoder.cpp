#include "encoder.h"
#include "stm32f407xx.h"
#include "math.h"

static encoder encoder_config[4];

void encoder_init(void)
{
    encoder_config[0].set_config(&htim1);
    encoder_config[1].set_config(&htim2);
    encoder_config[2].set_config(&htim3);
    encoder_config[3].set_config(&htim4);
    HAL_TIM_Encoder_Start(encoder_config[0].get_handle(), TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder_config[1].get_handle(), TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder_config[2].get_handle(), TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder_config[3].get_handle(), TIM_CHANNEL_ALL);
}

void encoder::calculate(void)
{
    int16_t c = (int16_t)henc->Instance->CNT;
    float factor = float(PPR * SAMPLE_TIME);
    printf("%d, %f\n", c, factor);
    omega = -((2 * PI * c * 1000.0) / factor);
    count += c;
    henc->Instance->CNT = 0;
}

void calculate_data(int i)
{
    encoder_config[i].calculate();
}

float get_data(int i)
{
    // printf("\nget_omega=%f\n", encoder_config[i].get_omega());
    return encoder_config[i].get_omega();
}

int16_t get_cnt(int i)
{
    return encoder_config[i].get_count();
}

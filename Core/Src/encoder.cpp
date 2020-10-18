//! This code doesnot implement the use of encoder but you can take reference from the encoder.cpp and encoder.h for future implementation

#include "encoder.h"
#include "stm32f407xx.h"

static encoder encoder_config[4];

void encoder_init(void){
    encoder_config[0].set_config(&htim1);
    encoder_config[1].set_config(&htim2);
    encoder_config[2].set_config(&htim3);
    encoder_config[3].set_config(&htim4);
    HAL_TIM_Encoder_Start(encoder_config[0].get_handle(), TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder_config[1].get_handle(), TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder_config[2].get_handle(), TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(encoder_config[3].get_handle(), TIM_CHANNEL_ALL);
}

void encoder::calculate(void){
        omega = ((2* PI* (int16_t)henc->Instance->CNT*1000)/(PPR*SAMPLE_TIME));
        count += int16_t(henc->Instance->CNT);
        henc->Instance->CNT =0;
    }

void calculate_data(int i){
    encoder_config[i].calculate();
}

void get_data(int i){
    encoder_config[i].get_omega();
}

void get_cnt(int i){
    encoder_config[i].get_count();
}

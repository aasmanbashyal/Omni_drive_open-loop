#include "robo_init.h"

motor motor[4];
static motor_config motor_configurations[4];

static void motor_init();


void robo_init()
{
	motor_init();
	encoder_init();
}

void motor_init()
{
	motor_configurations[0].htim = &htim8;
	motor_configurations[0].in1_port = GPIOD;
	motor_configurations[0].in1_pin = GPIO_PIN_0;
	motor_configurations[0].in2_port = GPIOE;
	motor_configurations[0].in2_pin = GPIO_PIN_5;
	motor_configurations[0].channel = TIM_CHANNEL_1;
	motor_configurations[0].max_omega = 70;
	motor_configurations[0].tolerance = 1;

	motor_configurations[1].htim = &htim8;
	motor_configurations[1].in1_port = GPIOA;
	motor_configurations[1].in1_pin = GPIO_PIN_10;
	motor_configurations[1].in2_port = GPIOB;
	motor_configurations[1].in2_pin = GPIO_PIN_5;
	motor_configurations[1].channel = TIM_CHANNEL_2;
	motor_configurations[1].max_omega = 70;
	motor_configurations[1].tolerance = 1;

	motor_configurations[2].htim = &htim8;
	motor_configurations[2].in1_port = GPIOE;
	motor_configurations[2].in1_pin = GPIO_PIN_3;
	motor_configurations[2].in2_port = GPIOD;
	motor_configurations[2].in2_pin = GPIO_PIN_2;
	motor_configurations[2].channel = TIM_CHANNEL_3;
	motor_configurations[2].max_omega = 70;
	motor_configurations[2].tolerance = 1;

	motor_configurations[3].htim = &htim8;
	motor_configurations[3].in1_port = GPIOC;
	motor_configurations[3].in1_pin = GPIO_PIN_13;
	motor_configurations[3].in2_port = GPIOE;
	motor_configurations[3].in2_pin = GPIO_PIN_1;
	motor_configurations[3].channel = TIM_CHANNEL_4;
	motor_configurations[3].max_omega = 70;
	motor_configurations[3].tolerance = 1;

	HAL_TIM_Base_Start(&htim8);
	HAL_TIM_PWM_Start(motor_configurations[0].htim, motor_configurations[0].channel);
	HAL_TIM_PWM_Start(motor_configurations[1].htim, motor_configurations[1].channel);
	HAL_TIM_PWM_Start(motor_configurations[2].htim, motor_configurations[2].channel);
	HAL_TIM_PWM_Start(motor_configurations[3].htim, motor_configurations[3].channel);
	for (int i = 0; i < 4; i++)
	{
		motor[i].set_config(&motor_configurations[i]);
	}
}

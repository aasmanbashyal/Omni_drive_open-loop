#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stm32f4xx_hal.h"
#include "tim.h"
#include <math.h>

enum Direction{
	CLOCKWISE,
	ANTICLOCKWISE,
	STOP
};

struct motor_config{
	float max_omega;
	float tolerance;

	GPIO_TypeDef *in1_port;	
        uint16_t in1_pin;
        GPIO_TypeDef *in2_port;
        uint16_t in2_pin;
        TIM_HandleTypeDef *htim;        // PWM Generating Timer
        uint32_t channel;               // PWM Channel
};

class motor
{
public:
	motor(){motor_ = 0;}
        motor(motor_config *motor) { motor_ = motor; }
	motor(motor &&) = default;
	motor(const motor &) = default;
	motor &operator=(motor &&) = default;
	motor &operator=(const motor &) = default;
	~motor(){}
        void set_config(motor_config *motor) { motor_ = motor;}
	float get_max_omega(){return motor_->max_omega;}
	void set_direction(enum Direction dir);
	void set_omega(float omega);
private:
	motor_config *motor_;
};



#endif //!_MOTOR_H_
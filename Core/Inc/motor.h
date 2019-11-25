#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "stm32f4xx_hal.h"
#include "tim.h"
#include <math.h>
#include "main.h"
#include "pid.h"
#include "encoder.h"

enum Direction
{
	CLOCKWISE,
	ANTICLOCKWISE,
	STOP
};

struct motor_config
{
	float max_omega;
	float tolerance;

	GPIO_TypeDef *in1_port;
	uint16_t in1_pin;
	GPIO_TypeDef *in2_port;
	uint16_t in2_pin;
	TIM_HandleTypeDef *htim; // PWM Generating Timer
	uint32_t channel;			 // PWM Channel
};

class motor
{
public:
	motor() { motor_ = 0; }
	motor(motor_config *motors) { motor_ = motors; }
	motor(motor &&) = default;
	motor(const motor &) = default;
	motor &operator=(motor &&) = default;
	motor &operator=(const motor &) = default;
	~motor() {}
	void set_config(motor_config *motors) { motor_ = motors; }
	float get_max_omega() { return motor_->max_omega; }
	void set_direction(enum Direction dir);
	void motor_input(float setpoint, float iOmega);
	void set_omega(float omega);
	//void set(float omega);

	void setPID_constraints(float kp, float ki, float kd, float upper_limit, float lower_limit)
	{
		Spid.setKp(kp);
		Spid.setKi(ki);
		Spid.setKd(kd);
		Spid.setlimits(upper_limit, lower_limit);
	}

private:
	motor_config *motor_;
	PID Spid;
};

#endif //!_MOTOR_H_
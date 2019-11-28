#include "motor.h"
#include "pid.h"
extern motor gmotor[4];

static uint16_t time_period(uint16_t PWM_frequency)
{
        if (PWM_frequency < 2000)
        { //MIN PWM_FREQUENCY = 1281.738 for time period to be 16 bit
                //_Error_Handler(__FILE__, __LINE__);
        }
        return ((168000000 / 2) / PWM_frequency) - 1; // In Center aligned mode period doubles hence we divide by 2
}

/* SET DUTYCYCLE primary function */
static void set_DutyCycle_Primary(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t dutyCycle)
{
        uint16_t mapped_value;
        mapped_value = (time_period(8000) * dutyCycle) / 65535;
        __HAL_TIM_SET_COMPARE(htim, Channel, mapped_value);
}

static void set_DutyCycle(motor_config *m, uint16_t dutyCycle)
{
        set_DutyCycle_Primary(m->htim, m->channel, dutyCycle);
}

static void set_motorDirection(motor_config *m, Direction d)
{
        if (d == Direction::CLOCKWISE)
        {
                HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_SET);
                HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_RESET);
        }
        else if (d == Direction::ANTICLOCKWISE)
        {
                HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_SET);
        }
        else
        {
                HAL_GPIO_WritePin(m->in1_port, m->in1_pin, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(m->in2_port, m->in2_pin, GPIO_PIN_RESET);
        }
}

static void set_motorOmega(motor_config *m, float omega)
{
        uint16_t new_omega = (65535.0 / m->max_omega) * (omega);
        set_DutyCycle(m, new_omega);
        //printf("omega = %d", (int)(omega*100));
        // printf("\tOCR = %d", (int)new_omega);
}

void motor ::motor_input(float setpoint, float iOmega)
{
        printf("Measured Omega = %f ", iOmega);
        float computed_omega = Spid.computePID(setpoint, iOmega);
        // printf("computed_omega = %f \n", computed_omega);

        this->set_omega(computed_omega);
}

void motor::set_omega(float omega)
{
        // printf("omega = %d", (int)(omega*100));
        if (omega > motor_->max_omega)
        {
                omega = motor_->max_omega;
        }
        else if (omega < -motor_->max_omega)
        {
                omega = -motor_->max_omega;
        }
        if (omega < -motor_->tolerance)
        {
                set_motorDirection(motor_, Direction::CLOCKWISE);
                set_motorOmega(motor_, fabs(omega));
        }
        else if (omega > motor_->tolerance)
        {
                set_motorDirection(motor_, Direction::ANTICLOCKWISE);
                set_motorOmega(motor_, fabs(omega));
        }
        else
        {
                set_motorDirection(motor_, Direction::STOP);
                set_motorOmega(motor_, 0);
        }
}
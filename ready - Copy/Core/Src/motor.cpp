#include"motor.h"
//#define setpoint 34
extern motor gMotors[4];

static uint16_t time_period(uint16_t PWM_frequency)
{
        if (PWM_frequency < 2000) { //MIN PWM_FREQUENCY = 1281.738 for time period to be 16 bit
                //_Error_Handler(__FILE__, __LINE__);
        }
        return ((168000000 / 2) / PWM_frequency) - 1; 		// In Center aligned mode period doubles hence we divide by 2
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

static void set_motorOmega(motor_config *m, float Comega)
{
        uint16_t new_omega = (65535.0 / m->max_omega) * (Comega);
        //printf("New_omega=%d\n",new_omega);
        set_DutyCycle(m, new_omega);
	//printf("omega = %d", (int)(omega*100));
	// printf("\tOCR = %d", (int)new_omega);
}

void motor :: motor_input(float setpoint, float iOmega)
{
       
       float computed_omega=Spid.computePID(setpoint,iOmega);
//         float computed_omega_1=Spid.computePID(setpoint,get_data(1));
//          float computed_omega_2=Spid.computePID(setpoint,get_data(2));
//           float computed_omega_3=Spid.computePID(setpoint,get_data(3));
//        //printf("Computed_omega=%f\n",computed_omega);
          this->set_omega(computed_omega);
//        gMotors[1].set_omega(computed_omega_1);
//        gMotors[2].set_omega(computed_omega_2);
//        gMotors[3].set_omega(computed_omega_3);
       

}



void motor:: set_omega(float Comega)
{
	//  printf("omega = %d", (int)(omega*100));
        // printf("\ninitial omega=%f",omega);
         if (Comega > motor_->max_omega){
	  	Comega = motor_->max_omega;
	  }
	  else if(Comega < -motor_->max_omega){
	  	Comega = -motor_->max_omega;
	  }
        if (Comega < -motor_->tolerance) {
        	set_motorDirection(motor_, Direction::CLOCKWISE);
       		set_motorOmega(motor_, fabs(Comega));
        }
        else if (Comega > motor_->tolerance) {
        	set_motorDirection(motor_, Direction::ANTICLOCKWISE);
       		set_motorOmega(motor_, fabs(Comega));
        }
      
       else {
        	set_motorDirection(motor_, Direction::STOP);
       		set_motorOmega(motor_, 0);
        }

}
// void set(float omega)
// {
//         float computed_omega=Spid.computePID(setpoint,omega);
//        // motor->set_omega(computed_omega);
//        printf("Computed_omega=%f",computed_omega);
//         gMotors[3].set_omega(computed_omega);

       
// }
//*/
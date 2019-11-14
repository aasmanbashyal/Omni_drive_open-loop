#include "pid.h"
#include "math.h"
#define SampleTime 10
//#define max (float)70
//#define min (float)-70
float max, min;
float lastError=0;
float iError=0;

void PID::setKp(float kp){
    Kp=kp;
    //printf("KP=%f",Kp);
    }
void PID::setKi(float ki){Ki=ki;}
void PID::setKd(float kd){Kd=kd;}
void PID::setPID(float kp, float ki, float kd)
{
    setKp(kp);
    setKi(ki);
    setKd(kd);
}
void PID::setlimits(float upp_out, float low_out)
        {
            max=upp_out;
            min=low_out;
           // printf("%f",max);
        }


float PID::computePID(float setpoint, float obtain)
{   
    //float iError=0;
    //float obtain=(*f)(omega);
   // printf("Omega=%f\n",omega);
    float error = setpoint - obtain;
   // printf("PIDomega=%f",omega);
    // printf("\nerror=%f\n",error);
    iError =iError + (error * SampleTime)/1000;
    // printf("iError=%f\n",iError);
    float dError = (error - float(lastError)*1000/ (SampleTime));
    //PID Function
    float output = Kp * error + Ki * iError + Kd * dError;
    
   // printf("%f\n",output);
    //omega = output;
    lastError = error;
    if (output>max)
    {
        output=max;
    }
    else if (output<min)
    {
        output=min;
    }
    // printf("Output=%f\n",output);
    return output;
}


/*

float PID::compute(float error, uint32_t dt_millis)
        {
            
                float Ts = (float)SampleTime / 1000.0;

                float P = Kp;
                float I = Ki;
                float D_by_Ts = Kd / Ts;

                float a = P + D_by_Ts;
                float b = -P + I * Ts - 2 * D_by_Ts;
                float c = D_by_Ts;

                l_output_ += a * error + b * l_err_ + c * ll_err_;

                if (l_output_ > max)
                {
                        l_output_ = max;
                }
                else if (l_output_ < min)
                {
                        l_output_ = min;
                }

                ll_err_ = l_err_;
                l_err_ = error;
		
                return l_output_;
        }
        */
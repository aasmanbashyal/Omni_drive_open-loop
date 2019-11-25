#ifndef _PID_H_
#define _PID_H_
#include "stdio.h"
//extern float SampleTime=10;

class PID
{
    public:
        PID(PID &&) = default;
        PID(const PID &) = default;
        PID &operator=(PID &&) = default;
        PID &operator=(const PID &) = default;
        PID(){setPID(0,0,0);}
        // PID()
        // {
        //     float  l_output_=0;
        //     float l_err_=0;
        //     float ll_err_=0;
        // }
        ~PID() { }
        PID(float kp, float ki, float kd){setPID(kp, ki, kd);}
        float Kp,Ki,Kd;
        float max, min;
        void setKp(float kp);
        void setKi(float ki);
        void setKd(float kd);
        void setPID(float kp, float ki, float kd);
        void setlimits(float upp_out, float low_out);
        //float getUpper_limit();
        //float getLower_limit();
        float getKp(){return Kp;}
        float getKi(){return Ki;}
        float getKd(){return Kd;}
        float Obtain(float obtain);
        float Setpoint(float setpoint);
        float computePID(float setpoint, float omega);
        //float compute(float error, uint32_t dt_millis);
        
        // private:
        //     float  l_output_;
        //     float l_err_;
        //     float ll_err_;
};

#endif
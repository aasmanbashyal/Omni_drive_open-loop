#include "actuator.h"
#include "main.h"
#include "joystick.h"
#include "robo_init.h"
#include "motor.h"

extern motor gmotor[4];
static float velocity_robot[3] = {0, 0, 0};
int32_t time = HAL_GetTick();

static float velocity = 40;
extern JoyStick joystick;
void play(void)
{
    joystick.init();
    task_();
}

void calculate_wheel_velocity()
{
    // printf("here\n");
    float velocity_motor[4] = {0, 0, 0, 0};
    float coupling_matrix[4][3] = {{0.707, -0.707, 1},
                                   {-0.707, -0.707, 1},
                                   {-0.707, 0.707, 1},
                                   {0.707, 0.707, 1}};

    for (int i = 0; i < 4; i++)
    {
        velocity_motor[i] = 0;
        for (int j = 0; j < 3; j++)
        {
            velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
        }
    }

    if ((HAL_GetTick() - time) >= 10)
    {
        time = HAL_GetTick();
        for (int i = 0; i < 4; i++)
        {
            gmotor[i].motor_input(velocity_motor[i], get_data(i)); //pid
        }
    }
}

void forward()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = -velocity;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void back()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = +velocity;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void left()
{
    velocity_robot[0] = -velocity;
    velocity_robot[1] = 0;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void right()
{
    velocity_robot[0] = velocity;
    velocity_robot[1] = 0;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void clockwise()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = 0;
    velocity_robot[2] = 5;
    calculate_wheel_velocity();
}

void anticlockwise()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = 0;
    velocity_robot[2] = -5;
    calculate_wheel_velocity();
}

void stop()
{
    velocity_robot[0] = 0;
    velocity_robot[1] = 0;
    velocity_robot[2] = 0;
    calculate_wheel_velocity();
}

void set_Velocity(float gVelocity)
{
    velocity = gVelocity;
}

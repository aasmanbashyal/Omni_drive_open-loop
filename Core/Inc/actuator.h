#ifndef _ACTUATOR_H_
#define _ACTUATOR_H_

#include "robo_init.h"

void play(void);
void forward();
void back();
void right();
void left();
void stop();


void calculate_wheel_velocity();

#endif //!_ACTUATOR_H_

#ifndef _ROBO_INIT_H_
#define _ROBO_INIT_H_

#include "tim.h"
#include "gpio.h"
#include "main.h"
#include "usart.h"
#include "dma.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_hal_conf.h"
#include "pid.h"

void robo_init(void);

#endif // !_ROBO_INIT_H_

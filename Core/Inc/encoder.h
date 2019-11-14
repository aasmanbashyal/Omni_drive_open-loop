#include "stm32f4xx_hal.h"
#include "tim.h"
#include "stm32f4xx_hal_gpio.h"

#define PPR (800)
#define PI (3.1415)
#define SAMPLE_TIME (5)


class encoder
{
public:
    encoder() {}
    encoder(TIM_HandleTypeDef *e) : henc(e) {}
    encoder(encoder &&) = default;
    encoder(const encoder &) = default;
    encoder &operator=(encoder &&) = default;
    encoder &operator=(const encoder &) = default;
    ~encoder() {}

    void set_config(TIM_HandleTypeDef *e) { henc = e; }
    void calculate(void);
    float get_omega(void) { printf("\n %f", omega); return omega; }
    float get_count(void) { printf("\ncount: %d", count); return count; }
    TIM_HandleTypeDef * get_handle(void) { return henc; }

private:
    TIM_HandleTypeDef *henc;
    float omega = 0;
    int16_t count = 0;
};

void encoder_init(void);
void calculate_data(int i);
void get_data(int i);
void get_cnt(int i);

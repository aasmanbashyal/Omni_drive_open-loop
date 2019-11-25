#include "joystick.h"
#include "actuator.h"
#include "array.h"
#include <math.h>

#define JOYSTICK_START_BYTE (START_BYTE)
#define NUM_JOYSTICK_BYTES (8)

static JoyStick_Handle gJoyStick;
static JoyStick_Data gNull_JData;

static CRC_Hash gJoyStick_CRC(7);
static uint8_t gRx2Data;
void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES]);

JoyStick joystick(&huart2);
struct JoyStick_Data gJoy;
uint8_t gJoy_Data_Arr[NUM_JOYSTICK_BYTES];
static bool gStart_Byte_Rx2 = false;
static uint16_t gRx2_Data_num = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
        __HAL_UART_FLUSH_DRREGISTER(gJoyStick.huart);
        if (!gStart_Byte_Rx2)
        {
                if (gRx2Data == JOYSTICK_START_BYTE)
                {
                        gStart_Byte_Rx2 = true;
                }
        }
        else
        {
                if (gRx2_Data_num < NUM_JOYSTICK_BYTES)
                {
                        gJoy_Data_Arr[gRx2_Data_num] = gRx2Data;
                        ++gRx2_Data_num;
                }
                else
                {
                        gStart_Byte_Rx2 = false;
                        gRx2_Data_num = 0;
                        fill_JoyData(&gJoy, gJoy_Data_Arr);
                }
        }
}

int JoyStick::init()
{
        gJoyStick.huart = huart_;
        gNull_JData.button1 = 0;
        gNull_JData.button2 = 0;
        gNull_JData.lt = 0;
        gNull_JData.rt = 0;
        gNull_JData.l_hatx = 0;
        gNull_JData.l_haty = 0;
        gNull_JData.r_haty = 0;
        HAL_UART_Receive_DMA(huart_, &gRx2Data, 1);
        return 0;
}

void fill_JoyData(JoyStick_Data *joy, uint8_t data[NUM_JOYSTICK_BYTES])
{
        joy->button1 = data[0];
        joy->button2 = data[1];
        joy->lt = data[2];
        joy->rt = data[3];
        joy->l_hatx = data[4];
        joy->l_haty = data[5];
        joy->r_hatx = data[6];
        joy->r_haty = data[7];
}

void task_()
{
        if (gJoy.lt == 0)
                set_Velocity(40);
        if (gJoy.lt != 0)
                set_Velocity(40 - (gJoy.lt / 255) * 30);
        if (gJoy.l_haty <= 127 && gJoy.l_haty != 0)
                forward();
        else if (gJoy.l_haty >= 128)
                back();
        else if (gJoy.r_hatx <= 127 && gJoy.r_hatx != 0)
                right();
        else if (gJoy.r_hatx >= 128)
                left();
        else if (gJoy.button1 == 1)
                clockwise();
        else if (gJoy.button1 == 2)
                anticlockwise();
        else
                stop();
}

// }
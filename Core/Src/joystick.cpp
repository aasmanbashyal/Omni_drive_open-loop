#include "joystick.h"
#include "array.h"
#include <math.h>

#define JOYSTICK_START_BYTE     (START_BYTE)
#define NUM_JOYSTICK_BYTES      (8)

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
   // printf("\n ohh yeah");
   // printf("\n %d",gRx2Data);


       __HAL_UART_FLUSH_DRREGISTER(gJoyStick.huart);
        if (!gStart_Byte_Rx2) {
                if (gRx2Data == JOYSTICK_START_BYTE) {
   printf("\n ohh yeah 1\n");

                        gStart_Byte_Rx2 = true;
                }
        }
        else {
                if (gRx2_Data_num < NUM_JOYSTICK_BYTES) {
                        // printf("%x \n", (int8_t)gRx2Data)
   printf("\n ohh yeah\n");
                        
                        gJoy_Data_Arr[gRx2_Data_num] = gRx2Data;
                        ++gRx2_Data_num;
                }
                else {
                        uint8_t rem = gRx2Data;

                        gStart_Byte_Rx2 = false;
                        gRx2_Data_num = 0;

                        uint8_t hash = gJoyStick_CRC.get_Hash(gJoy_Data_Arr, NUM_JOYSTICK_BYTES);
                        // arrPrint(gJoy_Data_Arr);
                        // printf("\t%d\t", hash);

                        if (hash == rem) {
                                fill_JoyData(&gJoy,gJoy_Data_Arr);
                              //   gJoyStick.data.insert(gJoy);

                            void task();
                                // printf("No Error!!");
                        }
                        else {
                             
                                // printf("%d, %d, %ld", rem, hash, gJoy_Err_Count);
                        }
                        // printf("\n");

                        arrFill(gJoy_Data_Arr, (uint8_t)0);

                }
        }
        void task();
}

int JoyStick::init()
{
   //   printf("\n init"); 
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

 void fill_JoyData(JoyStick_Data *joy,uint8_t data[NUM_JOYSTICK_BYTES])
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
// void initialize(void)
// {
//       joystick.init();
// }
void task()
{
printf("\n %d",gJoy.l_hatx);
printf("\n %d",gJoy.l_haty);
printf("\n %d",gJoy.r_hatx);
printf("\n %d",gJoy.r_haty);

}
#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_
#include "usart.h"
#include "queue_custom.h"
#include "crc_hash.h"


#define START_BYTE      (0xA5)

// Button's bit position in the byte
#define B_X             (7)
#define B_Y             (6)
#define B_A             (5)
#define B_B             (4)
#define B_UP            (3)
#define B_DOWN          (2)
#define B_LB            (1)
#define B_RB            (0)

#define B_START         (7)
#define B_BACK          (6)
#define B_XBOX          (5)
#define B_LEFT          (4)
#define B_RIGHT         (3)
struct JoyStick_Data
{       
        uint8_t button1;
        uint8_t button2;
        uint8_t lt;
        uint8_t rt;
        uint8_t l_hatx;
        uint8_t l_haty;
        uint8_t r_hatx;
        uint8_t r_haty;
};

struct JoyStick_Handle
{
        UART_HandleTypeDef *huart;
        Queue<JoyStick_Data, 2> data;
};

// void initialize(void);

class JoyStick
{
public:
        JoyStick(UART_HandleTypeDef *huart) {
                huart_ = huart;
        }
        JoyStick(JoyStick &&) = default;
        JoyStick(const JoyStick &) = default;
        JoyStick &operator=(JoyStick &&) = default;
        JoyStick &operator=(const JoyStick &) = default;
        ~JoyStick() { }

      //   static JoyStick& get_Instance(UART_HandleTypeDef *huart);
        int init();
      //   bool is_Empty();

      //   JoyStick_Command& parse();

private:
        UART_HandleTypeDef *huart_;
      //   struct JoyStick_Command Joy_Command;

      //   JoyStick_Data read();
      //   void parse_JoyData(JoyStick_Data joy);
};
void task_();
#endif // !_JOYSTICK_H_
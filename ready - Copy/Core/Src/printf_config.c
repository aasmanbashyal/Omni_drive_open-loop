/*
 * printf_config.cpp
 * 
 * Created : 11/10/2018
 *  Author : n-is
 *   email : 073bex422.nischal@pcampus.edu.np
 */

#include "stm32f4xx_hal.h"


int ITM_SendString(char *data, int len)
{
        int i = 0;
        for (; i < len; ++i)
        {
                // gPrintfData[gPrintfDataIndex++] = data[i];
                ITM_SendChar(data[i]);
        }
        return i;
}

int _write(int file, char *data, int len)
{
        int sent = ITM_SendString(data, len);
        return sent;
}

/*
 * uart_ui.c
 *
 *  Created on: Dec 8, 2020
 *      Author: u
 */

#include "usart.h"
#include "uart_ui.h"
#include "string.h"

u8 uart_rx_buf[128];
u16 rx_count = 0;
u8 hello[] = "hello\nPrint h! to help\n";

u32 itoa(s32 n, char s[]);

void Uart_send_val(u16 val)
    {
    char data[16];
    HAL_UART_Transmit(&huart2, (u8*) &data, itoa(val, data), 0xFFFFFFFF);
    }

void Uart_send_str(char *str, u16 len)
    {
    HAL_UART_Transmit(&huart2, (u8*) &str, len, 0xFFFFFFFF);
    }

void Uart_send_char(char a)
    {
    HAL_UART_Transmit(&huart2, (u8*) &a, 1, 0xFFFFFFFF);
    }

/* reverse:  переворачиваем строку s на месте */
void reverse(char s[])
    {
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
	{
	c = s[i];
	s[i] = s[j];
	s[j] = c;
	}
    }

/* itoa:  конвертируем n в символы в s */
u32 itoa(s32 n, char s[])
    {
    s32 i, sign;

    if ((sign = n) < 0) /* записываем знак */
	n = -n; /* делаем n положительным числом */
    i = 0;
    do
	{ /* генерируем цифры в обратном порядке */
	s[i++] = n % 10 + '0'; /* берем следующую цифру */
	}
    while ((n /= 10) > 0); /* удаляем */
    if (sign < 0)
	s[i++] = '-';
    s[i] = '\0';
    reverse(s);
    return i;
    }

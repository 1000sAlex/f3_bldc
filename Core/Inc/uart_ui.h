/*
 * uart_ui.h
 *
 *  Created on: Dec 8, 2020
 *      Author: u
 */

#ifndef INC_UART_UI_H_
#define INC_UART_UI_H_

#include "main.h"

void Uart_send(u16 val);
void Uart_send_val(u16 val);
void Uart_send_char(char a);
void Uart_send_str(char *str, u16 len);

#endif /* INC_UART_UI_H_ */

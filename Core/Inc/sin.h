/*
 * sin.h
 *
 *  Created on: Mar 16, 2021
 *      Author: u
 */

#ifndef INC_SIN_H_
#define INC_SIN_H_
#include "main.h"

#define PLOT_DATA_SIZE 360

typedef struct adc_plot_data
    {
	u16 vout_a[PLOT_DATA_SIZE]; //обратная связь по току фаза A
	u16 vout_b[PLOT_DATA_SIZE]; //обратная связь по току фаза B
	u16 vout_c[PLOT_DATA_SIZE]; //обратная связь по току фаза C
	u16 cur_fdbk_a[PLOT_DATA_SIZE]; //обратная связь по току фаза A
	u16 cur_fdbk_b[PLOT_DATA_SIZE]; //обратная связь по току фаза B
	u16 cur_fdbk_c[PLOT_DATA_SIZE]; //обратная связь по току фаза C
	u16 bemf_a[PLOT_DATA_SIZE]; //эдс самоиндукции фаза A
	u16 bemf_b[PLOT_DATA_SIZE]; //эдс самоиндукции фаза B
	u16 bemf_c[PLOT_DATA_SIZE]; //эдс самоиндукции фаза C
	u16 point;
	u8 flag_uart;
    } plot_data_t;


#endif /* INC_SIN_H_ */

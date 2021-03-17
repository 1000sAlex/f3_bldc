/*
 *sin.c
 *
 *Createdon:Mar16,2021
 *Author:u
 */

#include "sin.h"
#include "uart_ui.h"

u16 sin_data_pos_a = 0;
u16 sin_data_pos_b = 20;
u16 sin_data_pos_c = 40;

plot_data_t plot;

//@formatter:off
const u16 sin_data[60] =
{
    1024,1131,1236,1340,1440,1536,1625,1709,1784,1852,1910,1959,1997,
    2025,2042,2048,2042,2025,1997,1959,1910,1852,1784,1709,1625,1536,
    1440,1340,1236,1131,1024,916,811,707,607,512,422,338,263,195,137,
    88,50,22,5,0,5,22,50,88,137,195,263,338,422,512,607,707,811,916,
};
//{
//    0,53,107,160,212,265,316,366,416,464,512,557,601,644
//    ,685,724,760,795,828,858,886,912,935,955,973,989,1001
//    ,1011,1018,1022,1024,1022,1018,1011,1001,989,973,955
//    ,935,912,886,858,828,795,760,724,685,644,601,557,512
//    ,464,416,366,316,265,212,160,107,53
//};
//@formatter:on

extern adc_data_t ADC_data;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
u16 phase_a, phase_b, phase_c;

void plot_grab_data(plot_data_t *p)
    {
    p->vout_a[p->point] = phase_a;
    p->vout_b[p->point] = phase_b;
    p->vout_c[p->point] = phase_c;
    p->cur_fdbk_a[p->point] = ADC_data.cur_fdbk_a;
    p->cur_fdbk_b[p->point] = ADC_data.cur_fdbk_b;
    p->cur_fdbk_c[p->point] = ADC_data.cur_fdbk_c;
    p->bemf_a[p->point] = ADC_data.bemf_a;
    p->bemf_b[p->point] = ADC_data.bemf_b;
    p->bemf_c[p->point] = ADC_data.bemf_c;
    p->point++;
    if (p->point == 120)
	{
	p->flag_uart = 1;
	p->point = 0;
	}
    }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
    {
    if (htim->Instance == TIM6) //check if the interrupt comes from TIM1
	{
//htim->Instance->CCR1 = ADC_data.speed;
	phase_a = sin_data[sin_data_pos_a];
	phase_b = sin_data[sin_data_pos_b];
	phase_c = sin_data[sin_data_pos_c];
	htim1.Instance->CCR1 = phase_a;
	htim1.Instance->CCR2 = phase_b;
	htim1.Instance->CCR3 = phase_c;
	sin_data_pos_a++;
	sin_data_pos_b++;
	sin_data_pos_c++;
	if (sin_data_pos_a == 60)
	    {
	    sin_data_pos_a = 0;
	    if (plot.flag_uart == 2)
		{
		plot.flag_uart = 0;
		}
	    }
	if (sin_data_pos_b == 60)
	    {
	    sin_data_pos_b = 0;
	    }
	if (sin_data_pos_c == 60)
	    {
	    sin_data_pos_c = 0;
	    }
	if (plot.flag_uart == 0)
	    {
	    plot_grab_data(&plot);
	    }
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
	}
//    if (htim->Instance == TIM1)
//	{
    htim6.Instance->ARR = ADC_data.speed + 100;
//	}
    }

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//    {
//    if ( htim->Instance == TIM1)
//	{
//	volatile u32 sadf = 5343;
//	sadf = 4;
//	sadf = 4*53;
//	sadf = 4/sadf;
//	}
//    }


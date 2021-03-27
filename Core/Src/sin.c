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
//{
//    1024,1131,1236,1340,1440,1536,1625,1709,1784,1852,1910,1959,1997,
//    2025,2042,2048,2042,2025,1997,1959,1910,1852,1784,1709,1625,1536,
//    1440,1340,1236,1131,1024,916,811,707,607,512,422,338,263,195,137,
//    88,50,22,5,0,5,22,50,88,137,195,263,338,422,512,607,707,811,916,
//};
{
	0, 26, 53, 80, 106, 132, 158, 183, 208, 232, 256, 278, 300,
	322, 342, 362, 380, 397, 414, 429, 443, 456, 467, 477, 486,
	494, 500, 505, 509, 511, 512, 511, 509, 505, 500, 494, 486,
	477, 467, 456, 443, 429, 414, 397, 380, 362, 342, 322, 300,
	278, 256, 232, 208, 183, 158, 132, 106, 80, 53, 26,
};
//@formatter:on

#define PWM_POWER (512)

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
    if (p->point == PLOT_DATA_SIZE)
	{
	p->flag_uart = 1;
	p->point = 0;
	}
    }

void plot_grab_data2(plot_data_t *p, u16 step)
    {
    p->vout_a[p->point] = step;
    p->vout_b[p->point] = 0;
    p->vout_c[p->point] = 0;
    if ((step >= 0) && (step < 60))
	{
	p->cur_fdbk_a[p->point] = ADC_data.cur_fdbk_a;
	p->cur_fdbk_b[p->point] = ADC_data.cur_fdbk_b;
	p->cur_fdbk_c[p->point] = 0;
	p->bemf_a[p->point] = 0;
	p->bemf_b[p->point] = 0;
	p->bemf_c[p->point] = ADC_data.bemf_c;
	htim1.Instance->CCR1 = 1;
	}
    if ((step >= 60) && (step < 120))
	{
	p->cur_fdbk_a[p->point] = ADC_data.cur_fdbk_a;
	p->cur_fdbk_b[p->point] = 0;
	p->cur_fdbk_c[p->point] = ADC_data.cur_fdbk_c;
	p->bemf_a[p->point] = 0;
	p->bemf_b[p->point] = ADC_data.bemf_b;
	p->bemf_c[p->point] = 0;
	}
    if ((step >= 120) && (step < 180))
	{
	p->cur_fdbk_a[p->point] = 0;
	p->cur_fdbk_b[p->point] = ADC_data.cur_fdbk_b;
	p->cur_fdbk_c[p->point] = ADC_data.cur_fdbk_c;
	p->bemf_a[p->point] = ADC_data.bemf_a;
	p->bemf_b[p->point] = 0;
	p->bemf_c[p->point] = 0;
	}
    if ((step >= 180) && (step < 240))
	{
	p->cur_fdbk_a[p->point] = ADC_data.cur_fdbk_a;
	p->cur_fdbk_b[p->point] = ADC_data.cur_fdbk_b;
	p->cur_fdbk_c[p->point] = 0;
	p->bemf_a[p->point] = 0;
	p->bemf_b[p->point] = 0;
	p->bemf_c[p->point] = ADC_data.bemf_c;
	}
    if ((step >= 240) && (step < 300))
	{
	p->cur_fdbk_a[p->point] = ADC_data.cur_fdbk_a;
	p->cur_fdbk_b[p->point] = 0;
	p->cur_fdbk_c[p->point] = ADC_data.cur_fdbk_c;
	p->bemf_a[p->point] = 0;
	p->bemf_b[p->point] = ADC_data.bemf_b;
	p->bemf_c[p->point] = 0;
	}
    if ((step >= 300) && (step < 360))
	{
	p->cur_fdbk_a[p->point] = 0;
	p->cur_fdbk_b[p->point] = ADC_data.cur_fdbk_b;
	p->cur_fdbk_c[p->point] = ADC_data.cur_fdbk_c;
	p->bemf_a[p->point] = ADC_data.bemf_a;
	p->bemf_b[p->point] = 0;
	p->bemf_c[p->point] = 0;
	}
    p->point++;
    if (p->point == PLOT_DATA_SIZE)
	{
	p->flag_uart = 1;
	p->point = 0;
	}
    }

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
    {
    static u32 count = 0;
    if (htim->Instance == TIM1) //check if the interrupt comes from TIM1
	{

//	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 1);
////htim->Instance->CCR1 = ADC_data.speed;
//	HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);
	}
    if (htim->Instance == TIM6)
	{
	if (plot.flag_uart == 0)
	    {
	    plot_grab_data2(&plot, count);
	    }
//	phase_a = sin_data[sin_data_pos_a];
//	phase_b = sin_data[sin_data_pos_b];
//	phase_c = sin_data[sin_data_pos_c];
//	htim1.Instance->CCR1 = phase_a;
//	htim1.Instance->CCR2 = phase_b;
//	htim1.Instance->CCR3 = phase_c;
//	sin_data_pos_a++;
//	sin_data_pos_b++;
//	sin_data_pos_c++;
//	if (sin_data_pos_a == 60)
//	    {
//	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 0);
//	    sin_data_pos_a = 0;
//	    if (plot.flag_uart == 2)
//		{
//		plot.flag_uart = 0;
//		}
//	    }
//	if (sin_data_pos_b == 60)
//	    {
//	    sin_data_pos_b = 0;
//	    }
//	if (sin_data_pos_c == 60)
//	    {
//	    sin_data_pos_c = 0;
//	    }
	if (count == 360)
	    {
	    count = 0;
	    if (plot.flag_uart == 2)
		{
		plot.flag_uart = 0;
		}
	    }
	else
	    {
	    count++;
	    }
	if ((count >= 0) && (count < 60))
	    {

	    htim1.Instance->CCR1 = 0;
	    //PHASE_A_OUT_GPIO_Port->ODR &= ~PHASE_A_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 1);
	    htim1.Instance->CCR2 = PWM_POWER;
	    //PHASE_B_OUT_GPIO_Port->ODR |= PHASE_B_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 1);
	    htim1.Instance->CCR3 = 0;
	    //PHASE_C_OUT_GPIO_Port->ODR &= ~PHASE_C_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 0);
	    }
	if ((count >= 60) && (count < 120))
	    {
	    htim1.Instance->CCR1 = 0;
	    //PHASE_A_OUT_GPIO_Port->ODR &= ~PHASE_A_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 1);
	    htim1.Instance->CCR2 = 0;
	    //PHASE_B_OUT_GPIO_Port->ODR &= ~PHASE_B_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 0);
	    htim1.Instance->CCR3 = PWM_POWER;
	    //PHASE_C_OUT_GPIO_Port->ODR |= PHASE_C_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 1);
	    }
	if ((count >= 120) && (count < 180))
	    {
	    htim1.Instance->CCR1 = 0;
	    //PHASE_A_OUT_GPIO_Port->ODR &= ~PHASE_A_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 0);
	    htim1.Instance->CCR2 = 0;
	    //PHASE_B_OUT_GPIO_Port->ODR &= ~PHASE_B_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 1);
	    htim1.Instance->CCR3 = PWM_POWER;
	    //PHASE_C_OUT_GPIO_Port->ODR |= PHASE_C_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 1);
	    }
	if ((count >= 180) && (count < 240))
	    {
	    htim1.Instance->CCR1 = PWM_POWER;
	    //PHASE_A_OUTPIO_Port->ODR |= PHASE_A_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 1);
	    htim1.Instance->CCR2 = 0;
	    //PHASE_B_OUT_GPIO_Port->ODR &= ~PHASE_B_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 1);
	    htim1.Instance->CCR3 = 0;
	    //PHASE_C_OUT_GPIO_Port->ODR &= ~PHASE_C_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 0);
	    }
	if ((count >= 240) && (count < 300))
	    {
	    htim1.Instance->CCR1 = PWM_POWER;
	    //PHASE_A_OUTPIO_Port->ODR |= PHASE_A_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 1);
	    htim1.Instance->CCR2 = 0;
	    //PHASE_B_OUT_GPIO_Port->ODR &= ~PHASE_B_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 0);
	    htim1.Instance->CCR3 = 0;
	    //PHASE_C_OUT_GPIO_Port->ODR &= ~PHASE_C_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 1);
	    }
	if ((count >= 300) && (count < 360))
	    {
	    htim1.Instance->CCR1 = 0;
	    //PHASE_A_OUTPIO_Port->ODR &= ~PHASE_A_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 0);
	    htim1.Instance->CCR2 = PWM_POWER;
	    //PHASE_B_OUT_GPIO_Port->ODR |= PHASE_B_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 1);
	    htim1.Instance->CCR3 = 0;
	    //PHASE_C_OUT_GPIO_Port->ODR &= ~PHASE_C_OUT_Pin;
	    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 1);
	    }

	htim6.Instance->ARR = ADC_data.speed + 100;
	}
    }


/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "sin.h"
#include "uart_ui.h"
adc_data_t ADC_data;
extern plot_data_t plot;
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
    {
    LD2_GPIO_Port->ODR ^= LD2_Pin;
    }
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
    {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART2_UART_Init();
    MX_ADC1_Init();
    MX_TIM1_Init();
    MX_TIM6_Init();
    /* USER CODE BEGIN 2 */

    HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
    //HAL_ADC_Start_IT(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &ADC_data, sizeof(ADC_data) / 2);
    HAL_GPIO_WritePin(PHASE_A_EN_GPIO_Port, PHASE_A_EN_Pin, 1);
    HAL_GPIO_WritePin(PHASE_B_EN_GPIO_Port, PHASE_B_EN_Pin, 1);
    HAL_GPIO_WritePin(PHASE_C_EN_GPIO_Port, PHASE_C_EN_Pin, 1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_OC_Start(&htim1, TIM_CHANNEL_6);
    HAL_TIM_Base_Start_IT(&htim1);
    HAL_TIM_Base_Start_IT(&htim6);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
	{
	HAL_Delay(2000);
	while (plot.flag_uart == 0)
	    ;
//	Uart_send_str("cur_fdbk_a\t ", sizeof("cur_fdbk_a\t "));
//	Uart_send_str("cur_fdbk_b\t ", sizeof("cur_fdbk_b\t "));
//	Uart_send_str("cur_fdbk_c\t ", sizeof("cur_fdbk_c\t "));
//	Uart_send_str("bemf_a\t ", sizeof("bemf_a\t "));
//	Uart_send_str("bemf_b\t ", sizeof("bemf_b\t "));
//	Uart_send_str("bemf_c\t ", sizeof("bemf_c\t "));
	for (u16 i = 0; i < PLOT_DATA_SIZE; i++)
	    {
	    Uart_send_val(plot.vout_a[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.vout_b[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.vout_c[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.cur_fdbk_a[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.cur_fdbk_b[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.cur_fdbk_c[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.bemf_a[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.bemf_b[i]);
	    Uart_send_char('\t');
	    Uart_send_val(plot.bemf_c[i]);
	    Uart_send_char('\n');
	    }
	Uart_send_char('\n');
	Uart_send_char('\n');
	Uart_send_char('\n');
	plot.flag_uart = 2;
//	Uart_send_val(plot.cur_fdbk_a[5]);
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    /* USER CODE END 3 */
    }

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
    {
    RCC_OscInitTypeDef RCC_OscInitStruct =
	{
	0
	};
    RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{
	0
	};
    RCC_PeriphCLKInitTypeDef PeriphClkInit =
	{
	0
	};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
	Error_Handler();
	}
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
	    | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
	Error_Handler();
	}
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_TIM1;
    PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	{
	Error_Handler();
	}
    }

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
    {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
	{
	}
    /* USER CODE END Error_Handler_Debug */
    }

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

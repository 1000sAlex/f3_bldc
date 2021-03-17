/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

typedef uint8_t u8;
typedef int8_t s8;
typedef uint16_t u16;
typedef int16_t s16;
typedef uint32_t u32;
typedef int32_t s32;

typedef struct adc_input_data
    {
	u16 cur_fdbk_a; //обратная связь по току фаза A
	u16 cur_fdbk_b; //обратная связь по току фаза B
	u16 cur_fdbk_c; //обратная связь по току фаза C
	u16 bemf_a; //эдс самоиндукции фаза A
	u16 bemf_b; //эдс самоиндукции фаза B
	u16 bemf_c; //эдс самоиндукции фаза C
	u16 speed; //переменник скорости
	u16 power_v; //напряжение питания
    } adc_data_t;
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define CURRENT_FEEDBACK_C_Pin GPIO_PIN_0
#define CURRENT_FEEDBACK_C_GPIO_Port GPIOC
#define CURRENT_FEEDBACK_B_Pin GPIO_PIN_1
#define CURRENT_FEEDBACK_B_GPIO_Port GPIOC
#define TEMP_SENCE_Pin GPIO_PIN_2
#define TEMP_SENCE_GPIO_Port GPIOC
#define BEMF_A_Pin GPIO_PIN_3
#define BEMF_A_GPIO_Port GPIOC
#define CURRENT_FEEDBACK_A_Pin GPIO_PIN_0
#define CURRENT_FEEDBACK_A_GPIO_Port GPIOA
#define POWER_VBUS_Pin GPIO_PIN_1
#define POWER_VBUS_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define ERR_DIAG_BKN_Pin GPIO_PIN_6
#define ERR_DIAG_BKN_GPIO_Port GPIOA
#define BEMF_C_Pin GPIO_PIN_7
#define BEMF_C_GPIO_Port GPIOA
#define BEMF_B_Pin GPIO_PIN_0
#define BEMF_B_GPIO_Port GPIOB
#define SPEED_Pin GPIO_PIN_1
#define SPEED_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_2
#define LED_RED_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_13
#define LD2_GPIO_Port GPIOB
#define BEMF_DIGITAL_IN_Pin GPIO_PIN_9
#define BEMF_DIGITAL_IN_GPIO_Port GPIOC
#define PHASE_A_OUT_Pin GPIO_PIN_8
#define PHASE_A_OUT_GPIO_Port GPIOA
#define PHASE_B_OUT_Pin GPIO_PIN_9
#define PHASE_B_OUT_GPIO_Port GPIOA
#define PHASE_C_OUT_Pin GPIO_PIN_10
#define PHASE_C_OUT_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define PHASE_A_EN_Pin GPIO_PIN_10
#define PHASE_A_EN_GPIO_Port GPIOC
#define PHASE_B_EN_Pin GPIO_PIN_11
#define PHASE_B_EN_GPIO_Port GPIOC
#define PHASE_C_EN_Pin GPIO_PIN_12
#define PHASE_C_EN_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

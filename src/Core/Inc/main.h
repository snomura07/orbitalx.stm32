/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SENS1B_Pin GPIO_PIN_0
#define SENS1B_GPIO_Port GPIOA
#define SENS1A_Pin GPIO_PIN_1
#define SENS1A_GPIO_Port GPIOA
#define ENCB_Pin GPIO_PIN_2
#define ENCB_GPIO_Port GPIOA
#define SENS2B_Pin GPIO_PIN_3
#define SENS2B_GPIO_Port GPIOA
#define SENS2A_Pin GPIO_PIN_4
#define SENS2A_GPIO_Port GPIOA
#define ENCA_Pin GPIO_PIN_5
#define ENCA_GPIO_Port GPIOA
#define BATT_Pin GPIO_PIN_6
#define BATT_GPIO_Port GPIOA
#define TACT_SW_Pin GPIO_PIN_0
#define TACT_SW_GPIO_Port GPIOB
#define SENS_ON_A_Pin GPIO_PIN_1
#define SENS_ON_A_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_8
#define LED3_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_9
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_10
#define USART_RX_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_12
#define LED4_GPIO_Port GPIOA
#define SENS_ON_B_Pin GPIO_PIN_13
#define SENS_ON_B_GPIO_Port GPIOA
#define LED1_Pin GPIO_PIN_14
#define LED1_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_15
#define PWMA_GPIO_Port GPIOA
#define MOTA_IN1_Pin GPIO_PIN_3
#define MOTA_IN1_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_4
#define PWMB_GPIO_Port GPIOB
#define MOTB_IN1_Pin GPIO_PIN_5
#define MOTB_IN1_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_6
#define SCL_GPIO_Port GPIOB
#define SDA_Pin GPIO_PIN_7
#define SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

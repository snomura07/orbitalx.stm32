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
#include "stm32g4xx_hal.h"

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
#define LED5_Pin GPIO_PIN_1
#define LED5_GPIO_Port GPIOF
#define ENCA_Pin GPIO_PIN_0
#define ENCA_GPIO_Port GPIOA
#define SENS2A_Pin GPIO_PIN_1
#define SENS2A_GPIO_Port GPIOA
#define SENS2B_Pin GPIO_PIN_2
#define SENS2B_GPIO_Port GPIOA
#define SENS_ON_B_Pin GPIO_PIN_3
#define SENS_ON_B_GPIO_Port GPIOA
#define SPI_CS_Pin GPIO_PIN_4
#define SPI_CS_GPIO_Port GPIOA
#define SPI_SCLK_Pin GPIO_PIN_5
#define SPI_SCLK_GPIO_Port GPIOA
#define SPI_SDO_Pin GPIO_PIN_6
#define SPI_SDO_GPIO_Port GPIOA
#define SPI_SDI_Pin GPIO_PIN_7
#define SPI_SDI_GPIO_Port GPIOA
#define BATT_Pin GPIO_PIN_0
#define BATT_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_10
#define LED1_GPIO_Port GPIOB
#define SENS1B_Pin GPIO_PIN_11
#define SENS1B_GPIO_Port GPIOB
#define SENS1A_Pin GPIO_PIN_12
#define SENS1A_GPIO_Port GPIOB
#define ENCB_Pin GPIO_PIN_14
#define ENCB_GPIO_Port GPIOB
#define SENS_ON_A_Pin GPIO_PIN_15
#define SENS_ON_A_GPIO_Port GPIOB
#define LED6_Pin GPIO_PIN_8
#define LED6_GPIO_Port GPIOA
#define USART_TX_Pin GPIO_PIN_9
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_10
#define USART_RX_GPIO_Port GPIOA
#define LED4_Pin GPIO_PIN_11
#define LED4_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_12
#define LED2_GPIO_Port GPIOA
#define MOTA_IN1_Pin GPIO_PIN_15
#define MOTA_IN1_GPIO_Port GPIOA
#define PWMA_Pin GPIO_PIN_3
#define PWMA_GPIO_Port GPIOB
#define MOTB_IN1_Pin GPIO_PIN_4
#define MOTB_IN1_GPIO_Port GPIOB
#define PWMB_Pin GPIO_PIN_5
#define PWMB_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_9
#define LED3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

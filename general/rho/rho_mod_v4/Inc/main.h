/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define CPI0_Pin GPIO_PIN_0
#define CPI0_GPIO_Port GPIOA
#define CPI1_Pin GPIO_PIN_1
#define CPI1_GPIO_Port GPIOA
#define CPI2_Pin GPIO_PIN_2
#define CPI2_GPIO_Port GPIOA
#define CPI3_Pin GPIO_PIN_3
#define CPI3_GPIO_Port GPIOA
#define CPI4_Pin GPIO_PIN_4
#define CPI4_GPIO_Port GPIOA
#define CPI5_Pin GPIO_PIN_5
#define CPI5_GPIO_Port GPIOA
#define CPI6_Pin GPIO_PIN_6
#define CPI6_GPIO_Port GPIOA
#define CPI7_Pin GPIO_PIN_7
#define CPI7_GPIO_Port GPIOA
#define VSYNC_Pin GPIO_PIN_0
#define VSYNC_GPIO_Port GPIOB
#define VSYNC_EXTI_IRQn EXTI0_IRQn
#define HREF_Pin GPIO_PIN_1
#define HREF_GPIO_Port GPIOB
#define HREF_EXTI_IRQn EXTI1_IRQn
#define MCLK_Pin GPIO_PIN_8
#define MCLK_GPIO_Port GPIOA
#define SIOC_Pin GPIO_PIN_9
#define SIOC_GPIO_Port GPIOA
#define SIOD_Pin GPIO_PIN_10
#define SIOD_GPIO_Port GPIOA
#define PWDN_Pin GPIO_PIN_11
#define PWDN_GPIO_Port GPIOA
#define EN_1V5_Pin GPIO_PIN_12
#define EN_1V5_GPIO_Port GPIOA
#define CAM_EN_Pin GPIO_PIN_15
#define CAM_EN_GPIO_Port GPIOA
#define PCLK_Pin GPIO_PIN_3
#define PCLK_GPIO_Port GPIOB
#define UCK_Pin GPIO_PIN_5
#define UCK_GPIO_Port GPIOB
#define UTX_Pin GPIO_PIN_6
#define UTX_GPIO_Port GPIOB
#define URX_Pin GPIO_PIN_7
#define URX_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
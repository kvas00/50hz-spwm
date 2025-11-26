/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
static void System_Init_NoHAL(void);
static void GPIO_Init_NoHAL(void);
static void TIM10_Init_NoHAL(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE BEGIN Init */
  /* System initialization without HAL */
  System_Init_NoHAL();
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  GPIO_Init_NoHAL();
  TIM10_Init_NoHAL();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    // Toggle LED on PC13 using direct register access
    GPIOC->ODR ^= GPIO_PIN_13;

    // Precise 500ms delay using TIM10
    delay_ms(500);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization without HAL - direct register access
  * @param None
  * @retval None
  */
static void GPIO_Init_NoHAL(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable - direct register access */
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;  // Enable GPIOC clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;  // Enable GPIOH clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;  // Enable GPIOA clock

  // Wait for clocks to stabilize
  __DSB();

  /*Configure PC13 as output (LED) - direct register access
   * PC13 -> bit 13
   * MODER: 00 = Input, 01 = Output, 10 = Alternate, 11 = Analog
   * OTYPER: 0 = Push-pull, 1 = Open-drain
   * OSPEEDR: 00 = Low, 01 = Medium, 10 = High, 11 = Very High
   * PUPDR: 00 = No pull, 01 = Pull-up, 10 = Pull-down, 11 = Reserved
   */

  // Set PC13 to Output mode (01 in MODER bits 27:26)
  GPIOC->MODER &= ~(0x3UL << (13 * 2));   // Clear bits
  GPIOC->MODER |= (0x1UL << (13 * 2));    // Set to Output (01)

  // Set PC13 to Push-Pull (0 in OTYPER bit 13)
  GPIOC->OTYPER &= ~(1UL << 13);

  // Set PC13 to Low speed (00 in OSPEEDR bits 27:26)
  GPIOC->OSPEEDR &= ~(0x3UL << (13 * 2));

  // Set PC13 to No pull-up/pull-down (00 in PUPDR bits 27:26)
  GPIOC->PUPDR &= ~(0x3UL << (13 * 2));

  // Set initial output level to LOW (LED off)
  GPIOC->ODR &= ~(1UL << 13);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
  * @brief System Initialization without HAL - direct register access
  * @param None
  * @retval None
  *
  * Replaces HAL_Init() functionality:
  * - Enable Flash instruction cache
  * - Enable Flash data cache
  * - Enable Flash prefetch buffer
  * - Set NVIC priority grouping
  */
static void System_Init_NoHAL(void)
{
  // Enable Flash instruction cache
  FLASH->ACR |= FLASH_ACR_ICEN;

  // Enable Flash data cache
  FLASH->ACR |= FLASH_ACR_DCEN;

  // Enable Flash prefetch buffer
  FLASH->ACR |= FLASH_ACR_PRFTEN;

  // Set NVIC Priority Grouping to 4 (4 bits for pre-emption priority, 0 bits for subpriority)
  // This matches NVIC_PRIORITYGROUP_4 from HAL
  NVIC_SetPriorityGrouping(0x03); // 0x03 = 4 bits preemption, 0 bits sub-priority

  // Note: We don't need SysTick since we use TIM10 for delays
}

/**
  * @brief TIM10 Initialization without HAL - direct register access
  * @param None
  * @retval None
  *
  * TIM10 configuration:
  * - APB2 clock: 84 MHz
  * - Prescaler: 83 -> 84 MHz / 84 = 1 MHz
  * - Auto-reload: 65535 (max for 16-bit timer)
  * - Timer tick: 1 microsecond
  */
static void TIM10_Init_NoHAL(void)
{
  // Enable TIM10 clock (bit 17 in RCC_APB2ENR)
  RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;

  // Wait for clock to stabilize
  __DSB();

  // Configure TIM10
  TIM10->PSC = 83;          // Prescaler: 84 MHz / 84 = 1 MHz (1 us tick)
  TIM10->ARR = 0xFFFF;      // Auto-reload: maximum value for 16-bit timer
  TIM10->CNT = 0;           // Reset counter

  // Enable auto-reload preload
  TIM10->CR1 |= TIM_CR1_ARPE;

  // Generate update event to load prescaler value
  TIM10->EGR |= TIM_EGR_UG;

  // Clear update flag
  TIM10->SR &= ~TIM_SR_UIF;

  // Start timer
  TIM10->CR1 |= TIM_CR1_CEN;
}

/**
  * @brief Precise microsecond delay using TIM10
  * @param us: delay in microseconds (max ~65535 us per call)
  * @retval None
  */
void delay_us(uint32_t us)
{
  // Reset counter
  TIM10->CNT = 0;

  // Wait for specified microseconds
  while(TIM10->CNT < us);
}

/**
  * @brief Precise millisecond delay using TIM10
  * @param ms: delay in milliseconds
  * @retval None
  */
void delay_ms(uint32_t ms)
{
  for(uint32_t i = 0; i < ms; i++)
  {
    delay_us(1000);  // 1ms = 1000us
  }
}

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

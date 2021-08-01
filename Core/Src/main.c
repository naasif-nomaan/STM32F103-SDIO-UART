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
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "File_Handling.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
FATFS fs;
FRESULT fresult;
unsigned char buffer[64];
unsigned char cmd;
 char path;

unsigned char getingpath(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SD_HandleTypeDef hsd;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

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
	RCC->AHBENR |= 1<<10; // enabling clock for SDIO
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
  MX_SDIO_SD_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */

/* Errors: FR_DISK_ERR(this), FR_NOT_READY(SDIO_F103VET) */


  Mount_SD("/");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */


	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0)==0){



		   fresult = f_mount(&fs, "/", 1);


		    if(fresult==FR_OK) HAL_UART_Transmit(&huart1, "FR_OK", 5, 200);
			else if(fresult==FR_DISK_ERR) HAL_UART_Transmit(&huart1, "FR_DISK_ERR", 11, 200);
			else if(fresult==FR_INT_ERR) HAL_UART_Transmit(&huart1, "FR_INT_ERR", 10, 200);
			else if(fresult==FR_NOT_READY) HAL_UART_Transmit(&huart1, "FR_NOT_READY", 12, 200);
			else if(fresult==FR_NO_FILE) HAL_UART_Transmit(&huart1, "FR_NO_FILE", 10, 200);
			else if(fresult==FR_NO_PATH) HAL_UART_Transmit(&huart1, "FR_NO_PATH", 10, 200);
			else if(fresult==FR_INVALID_NAME) HAL_UART_Transmit(&huart1, "FR_INVALID_NAME", 15, 200);
			else if(fresult==FR_DENIED) HAL_UART_Transmit(&huart1, "FR_DENIED", 9, 200);
			else if(fresult==FR_EXIST) HAL_UART_Transmit(&huart1, "FR_EXIST", 8, 200);
			else if(fresult==FR_INVALID_OBJECT) HAL_UART_Transmit(&huart1, "FR_INVALID_OBJECT", 17, 200);
			else if(fresult==FR_WRITE_PROTECTED) HAL_UART_Transmit(&huart1, "FR_WRITE_PROTECTED", 18, 200);
			else if(fresult==FR_INVALID_DRIVE) HAL_UART_Transmit(&huart1, "FR_INVALID_DRIVE", 16, 200);
			else if(fresult==FR_NOT_ENABLED) HAL_UART_Transmit(&huart1, "FR_NOT_ENABLED", 14, 200);
			else if(fresult==FR_NO_FILESYSTEM) HAL_UART_Transmit(&huart1, "FR_NO_FILESYSTEM", 16, 200);
			else if(fresult==FR_MKFS_ABORTED) HAL_UART_Transmit(&huart1, "FR_MKFS_ABORTED", 15, 200);
			else if(fresult==FR_TIMEOUT) HAL_UART_Transmit(&huart1, "FR_TIMEOUT", 10, 200);
			else if(fresult==FR_LOCKED) HAL_UART_Transmit(&huart1, "FR_LOCKED", 9, 200);
			else if(fresult==FR_NOT_ENOUGH_CORE) HAL_UART_Transmit(&huart1, "FR_NOT_ENOUGH_CORE", 18, 200);
			else if(fresult==FR_TOO_MANY_OPEN_FILES) HAL_UART_Transmit(&huart1, "FR_TOO_MANY_OPEN_FILES", 22, 200);
			else if(fresult==FR_INVALID_PARAMETER) HAL_UART_Transmit(&huart1, "FR_INVALID_PARAMETER", 20, 200);
			else HAL_UART_Transmit(&huart1, "Invalid!", 8, 200);


	  }



    /* USER CODE BEGIN 3 */

	  	  while (buffer[0]!='\0' && buffer[1]!='\0' )
	  	  {
	  		  Get_string(buffer);
	  		  int len = length(buffer);
	  		  path= getingpath();

	  		  if (!(strncmp ("ls", buffer,len))) cmd = 'l';
	  		  if (!(strncmp ("mkdir", buffer,len))) cmd = 'm';
	  		  if (!(strncmp ("mkfil", buffer, len))) cmd = 'c';
	  		  if (!(strncmp ("read", buffer, len))) cmd = 'r';
	  		  if (!(strncmp ("write", buffer, len))) cmd = 'w';
	  		  if (!(strncmp ("rm", buffer, len))) cmd = 'd';
	  		  if (!(strncmp ("update", buffer, len))) cmd = 'u';
	  		  if (!(strncmp ("checkfile", buffer, len))) cmd = 'f';
	  		  if (!(strncmp ("checksd", buffer, len))) cmd = 's';


	  		  switch (cmd)
	  		  {
	  		  	  case ('l'):
	  		  			  scan_files(path);
	  		  	  	  	  cmd =0;
	  		  	  	  	  clear_buffer();
	  		  	  	  	  clear_path();
	  		  	  	  	  break;

	  			  case ('m'):
	  					  Create_Dir(path);
	  			  	  	  cmd=0;
	  			  	  	  clear_path();
	  			  	  	  break;

	  			  case ('c'):
	  					  Create_File(path);
	  			  	  	  cmd = 0;
	  			  	  	  clear_path();
	  			  	  	  break;

	  			  case ('r'):
	  					  Read_File(path);
	  			  	  	  cmd = 0;
	  			  	  	  clear_path();
	  			  	  	  break;

	  			  case ('d'):
	  					  Remove_File(path);
	  			  	  	  cmd = 0;
	  			  	  	  clear_path();
	  			  	  	  break;

	  			  case ('w'):
	  					  Write_File(path,buffer);
	  			  	  	  cmd = 0;
	  			  	  	  clear_path();
	  			  	  	  break;

	  			  case ('u'):
	  					  Update_File(path,buffer);
	  			  	  	  cmd = 0;
	  			  	  	  clear_path();
	  			  	  	  break;



	  			  case ('s'):
	  					  Check_SD_Space();
	  			  	  	  cmd = 0;
	  			  	  	  clear_path();
	  			  	  	  break;

	  			  default :
	  				  clear_buffer();
	  				  clear_path();
	  				  break;
	  		  }
	  	  }

  /* USER CODE END 3 */
}

}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);
}

/**
  * @brief SDIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDIO_SD_Init(void)
{

  /* USER CODE BEGIN SDIO_Init 0 */


  /* USER CODE END SDIO_Init 0 */

  /* USER CODE BEGIN SDIO_Init 1 */

  /* USER CODE END SDIO_Init 1 */
  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_4B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_ENABLE;
  hsd.Init.ClockDiv = 1;
  /* USER CODE BEGIN SDIO_Init 2 */

  /* USER CODE END SDIO_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pin : PE2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB12 PB13 PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void Get_string(char *buffer){

HAL_UART_Receive(&huart1, buffer, 64, 300);



}

int length(char *buffer){
	uint8_t len=0;
	while(*buffer!='\0' || *buffer!='\n'){
		len++;
	}
	len--;


	return len;
}

unsigned char getingpath(void){

	int start = length(buffer)+1;
	int end = length(buffer)-2;

	int j=0;
	for (int i=start; i<end; i++)
	{
		if (buffer[i] != ' ') return buffer[i];

	}
}



void clear_buffer (void)
{
	for (int i=0; i<64; i++) buffer[i] = '\0';
}

void clear_path (void)
{
	for (int i=0; i<64; i++) path = '\0';
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

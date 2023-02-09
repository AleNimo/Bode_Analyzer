/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "cmsis_os.h"
#include "app_touchgfx.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "transferenciaADC_calibrado.h"
#include "timer_calibrado.h"

#include "ILI9341.h"
#include "AD9833.h"
#include "Touch.h"
#include <math.h>

#include "usbd_customhid.h"

#include "stdlib.h"
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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

CRC_HandleTypeDef hcrc;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
float freq[MAX_FREQ_POINTS];

float mag[MAX_FREQ_POINTS];

float phase[MAX_FREQ_POINTS];

uint8_t touchEnabled;
unsigned char data_ready;
unsigned int total_points;
int progress;

//Vector DMA para ADC
uint32_t ADC_buffer_DMA[MOD_SAMPLES];	//Solo una muestra de entrada y salida

//Variables globales para medicion con IC
uint16_t IC_in;
uint16_t IC_out;
uint8_t medicion_realizada;

//Variable global para handler de usb
extern USBD_HandleTypeDef hUsbDeviceFS;

//FreeRTOS
SemaphoreHandle_t sem_measure;

SemaphoreHandle_t sem_mod;
SemaphoreHandle_t sem_ADC;

SemaphoreHandle_t sem_phase;
SemaphoreHandle_t sem_IC;

SemaphoreHandle_t sem_USB;

QueueHandle_t queue_mod;

QueueHandle_t queue_freq_phase;
QueueHandle_t queue_phase;

QueueHandle_t queue_IC;

QueueHandle_t queue_USB_MOD;
QueueHandle_t queue_USB_PHASE;

QueueHandle_t queue_hab_phase;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_SPI2_Init(void);
static void MX_CRC_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
void SPI_ChangeParameters(SPI_HandleTypeDef* hspi, uint32_t dataSize, uint32_t clkPolarity);
void TIM_ConfigPrescaler(uint32_t prescaler);

float ADCLinearInterpolation(uint32_t codigoADC);
float TimerLinearInterpolation_us(float mcuTime);

extern void touchgfxSignalVSync(void);
//FreeRTOS
void StartHardwareTask(void *pvParameters);

void MeasureTask(void *pvParameters);
void ModuleTask(void *pvParameters);
void PhaseTask(void *pvParameters);

void USBTask(void *pvParameters);
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
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_CRC_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */

  LCD_Init();

  AD9833_Init();

  AD9833_SetEnabled(TRUE);

  HAL_Delay(5000);

  //Reconfiguro polaridad de clock a la que necesita el touch
  SPI_ChangeParameters(&hspi2, SPI_DATASIZE_8BIT, SPI_POLARITY_LOW);
  touchEnabled = 1;
  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  sem_measure = xSemaphoreCreateBinary();

  sem_mod = xSemaphoreCreateBinary();
  sem_ADC = xSemaphoreCreateBinary();

  sem_phase = xSemaphoreCreateBinary();
  sem_IC = xSemaphoreCreateBinary();

  sem_USB = xSemaphoreCreateBinary();

  xSemaphoreTake(sem_measure, 0);

  xSemaphoreTake(sem_mod, 0);
  xSemaphoreTake(sem_ADC, 0);

  xSemaphoreTake(sem_phase, 0);
  xSemaphoreTake(sem_IC, 0);

  xSemaphoreTake(sem_USB, 0);
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  queue_mod = xQueueCreate(1, sizeof(float));
  queue_phase = xQueueCreate(1, sizeof(float));

  queue_freq_phase = xQueueCreate(1, sizeof(uint16_t));
  queue_IC = xQueueCreate(2, sizeof(uint16_t));

  queue_USB_MOD = xQueueCreate(MOD_SAMPLES, sizeof(float));
  queue_USB_PHASE = xQueueCreate(PHASE_SAMPLES, sizeof(float));

  queue_hab_phase = xQueueCreate(1, sizeof(uint8_t));

  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  xTaskCreate(StartHardwareTask, "HW_init", 1500, NULL, tskIDLE_PRIORITY+1, NULL);
  xTaskCreate(MeasureTask, "Measure", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  xTaskCreate(ModuleTask, "Module", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  xTaskCreate(PhaseTask, "Phase", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  xTaskCreate(USBTask, "USB", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN WHILE */

  vTaskStartScheduler();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_2;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_3;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief CRC Initialization Function
  * @param None
  * @retval None
  */
static void MX_CRC_Init(void)
{

  /* USER CODE BEGIN CRC_Init 0 */

  /* USER CODE END CRC_Init 0 */

  /* USER CODE BEGIN CRC_Init 1 */

  /* USER CODE END CRC_Init 1 */
  hcrc.Instance = CRC;
  if (HAL_CRC_Init(&hcrc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CRC_Init 2 */

  /* USER CODE END CRC_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_16BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 71;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 8399;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 30;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, DB0_Pin|DB1_Pin|DB2_Pin|DB3_Pin
                          |DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin
                          |DB8_Pin|DB9_Pin|DB10_Pin|DB11_Pin
                          |DB12_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_RESET_Pin|LCD_WR_Pin|LCD_RD_Pin|LCD_RS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, DB13_Pin|DB14_Pin|DB15_Pin|RST_VIN_Pin
                          |RST_VOUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin|TOUCH_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(DDS_CS_GPIO_Port, DDS_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : DB0_Pin DB1_Pin DB2_Pin DB3_Pin
                           DB4_Pin DB5_Pin DB6_Pin DB7_Pin
                           DB8_Pin DB9_Pin DB10_Pin DB11_Pin
                           DB12_Pin */
  GPIO_InitStruct.Pin = DB0_Pin|DB1_Pin|DB2_Pin|DB3_Pin
                          |DB4_Pin|DB5_Pin|DB6_Pin|DB7_Pin
                          |DB8_Pin|DB9_Pin|DB10_Pin|DB11_Pin
                          |DB12_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_RESET_Pin LCD_WR_Pin LCD_RD_Pin LCD_RS_Pin
                           DDS_CS_Pin */
  GPIO_InitStruct.Pin = LCD_RESET_Pin|LCD_WR_Pin|LCD_RD_Pin|LCD_RS_Pin
                          |DDS_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : DB13_Pin DB14_Pin DB15_Pin LCD_CS_Pin
                           TOUCH_CS_Pin RST_VIN_Pin RST_VOUT_Pin */
  GPIO_InitStruct.Pin = DB13_Pin|DB14_Pin|DB15_Pin|LCD_CS_Pin
                          |TOUCH_CS_Pin|RST_VIN_Pin|RST_VOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TOUCH_IRQ_Pin */
  GPIO_InitStruct.Pin = TOUCH_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(TOUCH_IRQ_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void SPI_ChangeParameters(SPI_HandleTypeDef* hspi, uint32_t dataSize, uint32_t clkPolarity)
{
	__HAL_SPI_DISABLE(hspi);

	hspi->Init.DataSize = dataSize;
	hspi->Init.CLKPolarity = clkPolarity;

	if (HAL_SPI_Init(hspi) != HAL_OK)
	{
		Error_Handler();
	}
	/* Enable SPI peripheral so SPI phase and polarity are changed before SPI peripheral in selected (otherwise trouble!!!) */
	__HAL_SPI_ENABLE(hspi);
}

void TIM_ConfigPrescaler(uint32_t prescaler)
{
	htim1.Init.Prescaler = prescaler;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}

	TIM1->EGR = TIM_EGR_UG; //Genero un evento para cambiar el prescaler inmediatamente (sino se cambia al hacer overflow)
}

float ADCLinearInterpolation(uint32_t codigoADC)
{
	uint16_t index = 0;

	while(codigoADC > CODIGOS_ADC[index])	//Busco el código en la tabla obtenida en la calibracion
		index++;

	if (codigoADC == CODIGOS_ADC[index])	//Si el código está en la tabla, devuelvo la tensión correspondiente
		return TENSIONES_ADC[index];

	else	//Si es menor al codigo de la tabla, realizo una interpolacion lineal
		return (TENSIONES_ADC[index-1] * (CODIGOS_ADC[index]-codigoADC) + TENSIONES_ADC[index] * (codigoADC-CODIGOS_ADC[index-1])) / (CODIGOS_ADC[index] - CODIGOS_ADC[index-1]);
}

float TimerLinearInterpolation_us(float mcuTime)
{
	uint8_t index = 0;

	while(mcuTime > TIME_US_MCU[index])	//Busco el tiempo en la tabla obtenida en la calibracion
		index++;

	if (mcuTime == TIME_US_MCU[index])	//Si el tiempo está en la tabla, devuelvo el tiempo patrón (corregido) correspondiente
		return (float)TIME_US_PATRON[index];

	else	//Si es menor al tiempo de la tabla, realizo una interpolacion lineal
		return (float)(TIME_US_PATRON[index-1] * (TIME_US_MCU[index]-mcuTime) + TIME_US_PATRON[index] * (mcuTime-TIME_US_MCU[index-1])) / (float)(TIME_US_MCU[index] - TIME_US_MCU[index-1]);
}

void StartHardwareTask(void* pvParameters)
{
	/* init code for USB_DEVICE */
	MX_USB_DEVICE_Init();
	/* USER CODE BEGIN 5 */
	HAL_TIM_Base_Start_IT(&htim2);
	MX_TouchGFX_Process();
	while(1)
	{

	}
}

void MeasureTask(void* pvParameters)
{
	uint16_t i;
	uint8_t phase_medida;

	while(1)
	{
		xSemaphoreTake(sem_measure, portMAX_DELAY);

		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)&total_points,sizeof(total_points)); //Envío la cantidad de puntos total

		vTaskDelay(pdMS_TO_TICKS(10));//Delay para evitar pérdida de paquetes

		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)freq,total_points*4);	//Envío vector de frecuencias

		vTaskDelay(pdMS_TO_TICKS(100));

		//Reconfiguro el spi a lo que necesita el AD9833
		touchEnabled = 0;	//Deshabilito el touch (ver TouchGFX/target/STM32TouchController.cpp)
		SPI_ChangeParameters(&hspi2, SPI_DATASIZE_16BIT, SPI_POLARITY_HIGH);

		//Para cada punto de frecuencia
		for(i = 0; i< total_points; i++)
		{
			//Reseteo detectores de pico (descargo capacitores)
			HAL_GPIO_WritePin(RST_VIN_GPIO_Port, RST_VIN_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(RST_VOUT_GPIO_Port, RST_VOUT_Pin, GPIO_PIN_SET);

			//Cambio de frecuencia (frecuencia redondeada a entero por el momento)
			//Reescribo freq[i] con el valor que verdaderamente se genera (para realizar los calculos y graficar correctamente)
			freq[i] = AD9833_SetFrequency(freq[i]);

			vTaskDelay(pdMS_TO_TICKS(1));

			//Desactivo mosfets que descargan capacitores
			HAL_GPIO_WritePin(RST_VIN_GPIO_Port, RST_VIN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(RST_VOUT_GPIO_Port, RST_VOUT_Pin, GPIO_PIN_RESET);

			if(i>0)
				xSemaphoreGive(sem_USB);

			vTaskDelay(pdMS_TO_TICKS(1000));

			//libero tarea de MEDICION DE MAGNITUD:
			xSemaphoreGive(sem_mod);

			//Espero medicion de magnitud
			xQueueReceive(queue_mod, &mag[i], portMAX_DELAY);

			//libero tarea de MEDICION DE FASE:

			if(mag[i]>-30 && freq[i] < 20000)
			{
				xQueueSend(queue_freq_phase, &i, portMAX_DELAY);
				xQueueReceive(queue_phase, &phase[i], portMAX_DELAY);
				phase_medida = 1;
			}
			else if (i==0)
			{
				phase[i] = 0;
				phase_medida = 0;
			}

			else
			{
				phase[i] = phase[i-1];
				phase_medida = 0;
			}

			xQueueSend(queue_hab_phase, &phase_medida, portMAX_DELAY);	//Informo a taskUSB si se realizó la medicion de fase o no

			//Actualizo la barra de progreso (0% a 100%)
			progress = ((i+1)*100) / total_points;
		}
		xSemaphoreGive(sem_USB);
		//Reconfiguro el spi a lo que necesita el touch
		SPI_ChangeParameters(&hspi2, SPI_DATASIZE_8BIT, SPI_POLARITY_LOW);

		touchEnabled = 1; //Habilito touch

		data_ready = 1;
	}
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	static uint8_t mediciones = 0;

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	mediciones++;

	if(mediciones == 10)
	{
		HAL_ADC_Stop_DMA(&hadc1);

		mediciones = 0;

		xSemaphoreGiveFromISR(sem_ADC, &xHigherPriorityTaskWoken );

		portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
	}
}

void ModuleTask(void *pvParameters)
{
	float v_samples[MOD_SAMPLES];

	float v_in_acum = 0;
	float v_out_acum = 0;

	float mag;

	while(1)
	{
		xSemaphoreTake(sem_mod, portMAX_DELAY);

		//Realizo MOD_SAMPLES mediciones: mitad de entrada y mitad de salida separadas 54.67us entre sí

		HAL_ADC_Start_DMA(&hadc1, ADC_buffer_DMA, MOD_SAMPLES);

		xSemaphoreTake(sem_ADC, portMAX_DELAY);

		v_in_acum = 0;
		v_out_acum = 0;
		//Obtengo tensiones a partir de cuentas con transferencia calibrada de ADC (realizando interpolación lineal)
		for(uint8_t j=0; j<MOD_SAMPLES; j+=2)
		{
			v_samples[j] = ADCLinearInterpolation(ADC_buffer_DMA[j]);
			v_in_acum += v_samples[j];
			v_samples[j+1] = ADCLinearInterpolation(ADC_buffer_DMA[j+1]);
			v_out_acum += v_samples[j+1];
		}

		mag = 20*log10(v_out_acum/v_in_acum);

		for(uint8_t i=0; i<MOD_SAMPLES; i++)
			xQueueSend(queue_USB_MOD, &v_samples[i], portMAX_DELAY);

		xQueueSend(queue_mod, &mag, portMAX_DELAY);
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	static uint8_t first_capture = 0;

	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		if(first_capture == 0 && medicion_realizada == 0)	//Primer flanco ascendente
		{
			HAL_TIM_IC_Stop_IT(&htim1, TIM_CHANNEL_2);
			IC_in = htim->Instance->CCR2;
			first_capture = 1;
		}
	}
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	{
		if(first_capture)	//Si ya se capturó el primer flanco en el canal 2
		{
			HAL_TIM_IC_Stop_IT(&htim1, TIM_CHANNEL_3);
			medicion_realizada = 1;
			IC_out = htim->Instance->CCR3;
			first_capture = 0;
		}
	}
}

void PhaseTask(void *pvParameters)
{
	float time_diff[PHASE_SAMPLES];

	uint16_t index;

	float phase_met1;	//Valor auxiliar correspondiente a metodo 1 de medicion de fase

	float phase_val;	//Vector con PHASE_SAMPLES muestras de frecuencia puntual

	float phase_val_acum = 0;	//acumulador para hacer el promedio

	while(1)
	{
		phase_val_acum = 0;
		xQueueReceive(queue_freq_phase, &index, portMAX_DELAY);

		//Calculo prescaler para que las cuentas del timer alcancen un período completo
		if(freq[index] < 15.259)
		{
			TIM_ConfigPrescaler(ceil((long double)FREQ_TIM1/(65535*freq[index]) - 1));
			vTaskDelay(pdMS_TO_TICKS(1));
		}
		else if(htim1.Init.Prescaler != 71)	//Prescaler mínimo de 71 para que el timer funcione correctamente
		{
			TIM_ConfigPrescaler(71);
			vTaskDelay(pdMS_TO_TICKS(1));
		}

		for(uint8_t i = 0; i<PHASE_SAMPLES; i++)
		{
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_3);

			medicion_realizada = 0;	//Fuerzo a que vuelva a medir

			while(medicion_realizada == 0);

			if (IC_out >= IC_in)
				time_diff[i] = (float)(IC_out - IC_in) * (htim1.Init.Prescaler+1) / FREQ_TIM1;

			else if (IC_in > IC_out) //Entre IC_in e IC_out se llenó el registro de la cuenta
				time_diff[i] = (float)((65535 - IC_in) + IC_out) * (htim1.Init.Prescaler+1) / FREQ_TIM1;

			time_diff[i] = TimerLinearInterpolation_us(time_diff[i]*1000000)/1000000;

			//El metodo de medicion siempre es FaseOut - FaseIn (Método 1), luego
			//matematicamente lo pasamos a FaseIn - FaseOut (Método 2) de ser necesario:

			phase_met1 = -2*180*freq[index]*time_diff[i];	//fase en grados sexagecimales (Metodo 1)

			if(abs(phase_met1) > 360) //Detecto si hay ruido de comparador (no puede haber desfasaje mayor a 360)
				i--;

			else
			{
				if(phase_met1 < -180)	//Hay que pasar al metodo 2
					phase_val = phase_met1 + 360;

				else
					phase_val = phase_met1; //Sigo con metodo 1

				phase_val_acum += phase_val;
			}
			medicion_realizada = 0;

		}
		phase_val_acum /= (float)PHASE_SAMPLES;

		for(uint8_t j = 0; j< PHASE_SAMPLES; j++)
			xQueueSend(queue_USB_PHASE, &time_diff[j], portMAX_DELAY);

		xQueueSend(queue_phase, &phase_val_acum, portMAX_DELAY);
	}
}

void USBTask(void *pvParameters)
{
	uint8_t phase_medida;

	float v_samples[MOD_SAMPLES];
	float time_diff[PHASE_SAMPLES];

	while(1)
	{
		for(uint8_t i=0; i< MOD_SAMPLES; i++)
			xQueueReceive(queue_USB_MOD, &v_samples[i], portMAX_DELAY);

		xQueueReceive(queue_hab_phase, &phase_medida, portMAX_DELAY);

		if(phase_medida)	//Si se realizó la medición de fase obtengo los valores, sino se mantienen
		{
			for(uint8_t i=0; i< PHASE_SAMPLES; i++)
				xQueueReceive(queue_USB_PHASE, &time_diff[i], portMAX_DELAY);
		}

		xSemaphoreTake(sem_USB, portMAX_DELAY);

		USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)v_samples,MOD_SAMPLES * 4);	//Envío vector con muestras de tensiones

		vTaskDelay(pdMS_TO_TICKS(500));	//Delay para evitar pérdida de paquetes

		if(phase_medida)
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)time_diff,PHASE_SAMPLES * 4);	//Envío vector con desfasajes temporales
		else
		{
			time_diff[0] = 0;
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t*)time_diff,1);	//Informo que no se realizó medición de fase a la PC
		}
	}
}


/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
  if (htim->Instance == TIM2)
	  touchgfxSignalVSync();

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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

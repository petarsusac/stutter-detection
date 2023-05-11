#include "nucleo_uart.h"

#include "stm32f7xx_hal.h"

#define USART_INSTANCE USART3
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_TX_Pin GPIO_PIN_9

static UART_HandleTypeDef huart;

// Redefinition of function called by HAL_UART_Init()
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
	if(huart->Instance==USART3)
	{
		/** Initializes the peripherals clock
		 */
		PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3;
		PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
		if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
		{
			while(1);
		}

		/* Peripheral clock enable */
		__HAL_RCC_USART3_CLK_ENABLE();

		__HAL_RCC_GPIOD_CLK_ENABLE();
		/**USART3 GPIO Configuration
    	PD8     ------> USART3_TX
    	PD9     ------> USART3_RX
		 */
		GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	}

}

// Redefinition of putchar, allows UART to be used as stdout
int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart, (uint8_t *) &ch, 1, 0xFFFF);
	return ch;
}

void nucleo_uart_init()
{
	huart.Instance = USART_INSTANCE;
	huart.Init.BaudRate = 115200;
	huart.Init.WordLength = UART_WORDLENGTH_8B;
	huart.Init.StopBits = UART_STOPBITS_1;
	huart.Init.Parity = UART_PARITY_NONE;
	huart.Init.Mode = UART_MODE_TX_RX;
	huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart.Init.OverSampling = UART_OVERSAMPLING_16;
	huart.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart) != HAL_OK)
	{
		while(1);
	}
}


/* -----INCLUDES----- */
#include "main.h"
#include "core_init.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

/* -----DEFINES----- */
UART_HandleTypeDef huart1;
#define MAX_STRING_PARSE_SIZE 200

/* -----STRUCTS | ENUMS | UNIONS----- */
ErrorTable_t error_string_table[] = {
    {eStringIsTooLarge	,	"STRING IS TOO LARGE1\r" },
    {eNegativeFrequency	,	"NEGATIVE FREQUENCY IS SET\r" },
    /* Insert additional values based on error conditions */
};
/* -----LOCAL VARIABLES----- */

/* -----FUNCTIONS----- */
void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
        Error_Handler();
    }
}

void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET);

    /*Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* Configure GPIO pins : PA5 PA6 PA7 */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


/*
    Initial API handler. Enables different API's based on set flags. Has to be run at the start.
    Example: Enabler (true, true, false, false, true, false);
*/
void Enabler (bool gpio_flag,
              bool usart1_flag,
              bool sysclock_flag,
              bool hal_flag,
              bool tim1_flag,
              bool tim2_flag) {
    if (gpio_flag == true) {
        MX_GPIO_Init();
    } else {
        //#warning "GPIO interface is disabled by api!"
    }
    if (usart1_flag == true) {
        MX_USART1_UART_Init();
    } else {
        //#warning "USART1 interface is disabled by api!"
    }
    if (sysclock_flag == true) {
        SystemClock_Config();
    } else {
        //#warning "USART2 interface is disabled by api!"
    }
    if (hal_flag == true) {
        HAL_Init();
    } else {
        //#warning "USART3 interface is disabled by api!"
    }
    if (tim1_flag == true) {
        /* insert handler */
    } else {
        //#warning "TIM1 interface is disabled by api!"
    }
    if (tim2_flag == true) {
        /* insert handler */
    } else {
        //#warning "TIM2 interface is disabled by api!"
    }
}

/*
    Function to parse only string over USART1;
    Function appends "CR" - carriage return symbol to parsed string.
*/
void USART1_String_Parse (char* data) {
    const char* carriage_return_append = "\r";
    char ptr[MAX_STRING_PARSE_SIZE];
    memset(ptr, 0, strlen(ptr));
    if (strlen(data) > MAX_STRING_PARSE_SIZE) {
        HAL_UART_Transmit(&huart1, (uint8_t *)error_string_table[eStringIsTooLarge].ErrorStr, strlen(error_string_table[eStringIsTooLarge].ErrorStr), 15);
    } else {
        strncpy(ptr, data, strlen(data));
        strcat(ptr, carriage_return_append);
        HAL_UART_Transmit(&huart1, (uint8_t *)ptr, strlen(data)+strlen(carriage_return_append), 100);
    }
}

/*
    Main function for debugging purposes. Uses USART1 to parse any type of raw data to terminal.
    Function is based on printf();
    Example: print("Current version: %d", 101)
*/
int print (char * str, ...) {
    va_list vl;
    int i = 0, j=0;
    char buff[100]={0}, tmp[20];
    char * str_arg;
    va_start( vl, str );
    while (str && str[i]) {
        if(str[i] == '%') {
            i++;
            switch (str[i]) {
                case 'c': {
                    buff[j] = (char)va_arg( vl, int );
                    j++;
                    break;
                }
                case 'd': {
                    itoa(va_arg( vl, int ), tmp, 10);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 'x': {
                    itoa(va_arg( vl, int ), tmp, 16);
                    strcpy(&buff[j], tmp);
                    j += strlen(tmp);
                    break;
                }
                case 's': {
                    str_arg = va_arg( vl, char* );
                    strcpy(&buff[j], str_arg);
                    j += strlen(str_arg);
                    break;
                }
            }
        } else {
            buff[j] =str[i];
            j++;
        }
    i++;
    }
    USART1_String_Parse(buff);
    va_end(vl);
    return j;
}

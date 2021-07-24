#ifndef INC_CORE_INIT_H_
#define INC_CORE_INIT_H_

/* -----INCLUDES----- */
#include <stdbool.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "gpio_app.h"
#include "main.h"
#include <stdio.h>

/* -----STRUCTS | ENUMS | UNIONS----- */
typedef enum {
    eStringIsTooLarge,
    eNegativeFrequency,
    /* Insert additional error conditions */
} ErrorValues_t;

typedef struct {
    ErrorValues_t errval;
    char* ErrorStr;
} ErrorTable_t;

/* -----FUNCTION PROTOTYPES----- */
void        MX_USART1_UART_Init(void);
void        USART1_String_Parse(char* data);
void        SystemClock_Config(void);
void        MX_GPIO_Init(void);
int         print (char * str, ...);
void        Enabler (bool gpio_flag, bool usart1_flag, bool sysclock_flag, bool hal_flag, bool tim1_flag, bool tim2_flag);

#endif /* INC_CORE_INIT_H_ */
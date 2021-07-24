/* -----INCLUDES----- */
#include "main.h"
#include "core_init.h"

/* -----DEFINES----- */
#define _USART1   (true)
#define _GPIO     (true)
#define _HAL      (true)
#define _SYSCLOCK (true)
#define _TIM1     (false)
#define _TIM2     (false)

/* -----STRUCTS | ENUMS | UNIONS----- */

/* -----LOCAL VARIABLES----- */
char data[100] = "batonas";

/* -----MAIN FUNCTION----- */
int main(void) {
    Enabler(_GPIO, _USART1, _SYSCLOCK, _HAL, _TIM1, _TIM2);

    while (1) {
        print("hex: %x", 0x4a);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(200);
    }
}

/* -----ERROR HANDLER----- */
void Error_Handler(void) {
    __disable_irq();
    while (1) {
    }
}
/* -----INCLUDES----- */
#include "core_init.h"
#include "gpio_app.h"
#include "math.h"
/* -----DEFINES----- */

/* -----STRUCTS | ENUMS | UNIONS----- */

/* -----LOCAL VARIABLES----- */

/* -----FUNCTIONS----- */
void Blink_Led(eLeds_t which_led, float frequency) {
    float period_ms = 0;

    if (frequency < 0) {
        frequency = 0;
    }

    period_ms = (1/(float)frequency)*1000;
    if ((which_led == eDEBUG_LED) && (frequency != 0)) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(period_ms);
    /* If frequency is set to zero, just toggle LED */
    } else if ((which_led == eDEBUG_LED) && (frequency == 0)){
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }

}
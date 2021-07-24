#ifndef INC_GPIO_APP_H_
#define INC_GPIO_APP_H_

/* -----INCLUDES----- */
#include "core_init.h"

/* -----STRUCTS | ENUMS | UNIONS----- */
typedef enum {
    eDEBUG_LED,
    /* Insert other LEDs */
} eLeds_t;

/* -----FUNCTION PROTOTYPES----- */
void Blink_Led(eLeds_t which_led, float frequency);

#endif /* INC_GPIO_APP_H_ */
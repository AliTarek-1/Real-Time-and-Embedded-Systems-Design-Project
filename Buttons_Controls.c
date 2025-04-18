#include "tm4c123gh6pm.h"
#include "motor_driver.h"
#include "Buttons_Contols.h"
#define BUTTON_UP     0x01  // PA0
#define BUTTON_DOWN   0x02  // PA1
#define LIMIT_SWITCH  0x04  // PA2

void Buttons_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x01; // Enable Port A clock
    while ((SYSCTL_PRGPIO_R & 0x01) == 0); // Wait

    GPIO_PORTA_DIR_R &= ~(BUTTON_UP | BUTTON_DOWN | LIMIT_SWITCH); // Set as input
    GPIO_PORTA_DEN_R |= (BUTTON_UP | BUTTON_DOWN | LIMIT_SWITCH);  // Digital enable
    GPIO_PORTA_PUR_R |= (BUTTON_UP | BUTTON_DOWN | LIMIT_SWITCH);  // Pull-up
}

int Mode_IsAuto(void) {
    return (GPIO_PORTA_DATA_R & LIMIT_SWITCH) != 0;
}

ButtonState Buttons_Read(void) {
    uint32_t data = GPIO_PORTA_DATA_R;
    ButtonState state;
    state.up = (data & BUTTON_UP) == 0;   // Active LOW
    state.down = (data & BUTTON_DOWN) == 0;
    return state;
}
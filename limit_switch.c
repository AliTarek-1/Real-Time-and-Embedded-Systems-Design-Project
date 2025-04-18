#include "limit_switch.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>

void LimitSwitch_Init(void) {
    GPIO_PORTA_DIR_R &= ~((1 << 2) | (1 << 3));
    GPIO_PORTA_DEN_R |= (1 << 2) | (1 << 3);
}

bool LimitSwitch_UpperTriggered(void) {
    return (GPIO_PORTA_DATA_R & (1 << 2)) == 0;
}

bool LimitSwitch_LowerTriggered(void) {
    return (GPIO_PORTA_DATA_R & (1 << 3)) == 0;
}

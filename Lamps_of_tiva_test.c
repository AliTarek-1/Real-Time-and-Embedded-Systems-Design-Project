#include <stdint.h>
#include "tm4c123gh6pm.h"

void PortF_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20;      // 1. Enable clock for Port F (bit 5)
    while ((SYSCTL_PRGPIO_R & 0x20) == 0); // 2. Wait until Port F is ready

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // 3. Unlock PF0
    GPIO_PORTF_CR_R |= 0x0E;        // 4. Allow changes to PF1–PF3
    GPIO_PORTF_DIR_R |= 0x0E;       // 5. Set PF1–PF3 as output
    GPIO_PORTF_DEN_R |= 0x0E;       // 6. Digital enable PF1–PF3
}
// Turn ON PF1 (Red lamp)
void Lamp1_On(void) {
    GPIO_PORTF_DATA_R |= 0x02; // PF1 = 1
}

// Turn OFF PF1
void Lamp1_Off(void) {
    GPIO_PORTF_DATA_R &= ~0x02; // PF1 = 0
}

// Turn ON PF2 (Blue lamp)
void Lamp2_On(void) {
    GPIO_PORTF_DATA_R |= 0x04; // PF2 = 1
}

// Turn OFF PF2
void Lamp2_Off(void) {
    GPIO_PORTF_DATA_R &= ~0x04; // PF2 = 0
}

// Turn ON PF3 (Green lamp)
void Lamp3_On(void) {
    GPIO_PORTF_DATA_R |= 0x08; // PF3 = 1
}

// Turn OFF PF3
void Lamp3_Off(void) {
    GPIO_PORTF_DATA_R &= ~0x08; // PF3 = 0
}

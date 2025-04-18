// Driver: Buzzer Alert
#include "buzzer_alert.h"
#include "tm4c123gh6pm.h"

#define BUZZER_PIN 0x04 // PF2

void BuzzerAlertInit() {
    // Enable clock for Port F
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Wait until Port F is ready

    GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock PF
    GPIO_PORTF_CR_R |= BUZZER_PIN; // Allow changes to PF2

    GPIO_PORTF_DIR_R |= BUZZER_PIN;   // Set PF2 as output
    GPIO_PORTF_DEN_R |= BUZZER_PIN;   // Digital enable PF2
    GPIO_PORTF_AFSEL_R &= ~BUZZER_PIN; // Disable alternate functions
    GPIO_PORTF_AMSEL_R &= ~BUZZER_PIN; // Disable analog mode
    GPIO_PORTF_DATA_R &= ~BUZZER_PIN;  // Start with buzzer off
}

void Buzzer_On(void) {
    GPIO_PORTF_DATA_R |= BUZZER_PIN;
}

void Buzzer_Off(void) {
    GPIO_PORTF_DATA_R &= ~BUZZER_PIN;
}

void Buzzer_Toggle(void) {
    GPIO_PORTF_DATA_R ^= BUZZER_PIN;
}

void Buzzer_UpdateAlert(void) {
    // Placeholder for system condition-based alert
    // For example, pulse the buzzer if an obstacle is detected
    Buzzer_Toggle();
}

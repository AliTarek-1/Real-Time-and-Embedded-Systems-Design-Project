// Driver: Gpio Init
//we can delete this file later if we need
#include "gpio_init.h"
#include "tm4c123gh6pm.h"

void GpioInitInit() {
    // Enable clocks for Ports: A, B, D, E, F
    SYSCTL_RCGCGPIO_R |= 0x2B; // (00101011) = Ports A, B, D, E, F
    while ((SYSCTL_PRGPIO_R & 0x2B) != 0x2B); // Wait for all to be ready

    // --- Motor Pins: PB0 (IN1), PB1 (IN2), PB2 (EN) ---
    GPIO_PORTB_DIR_R |= 0x07;     // Set PB0, PB1, PB2 as output
    GPIO_PORTB_DEN_R |= 0x07;     // Digital enable
    GPIO_PORTB_AFSEL_R &= ~0x07;  // Disable alternate functions
    GPIO_PORTB_AMSEL_R &= ~0x07;  // Disable analog

    // --- Buzzer: PF2 ---
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_CR_R |= 0x04;
    GPIO_PORTF_DIR_R |= 0x04;     // PF2 output
    GPIO_PORTF_DEN_R |= 0x04;
    GPIO_PORTF_AFSEL_R &= ~0x04;
    GPIO_PORTF_AMSEL_R &= ~0x04;

    // --- Obstacle Sensor: PE0 (input) ---
    GPIO_PORTE_DIR_R &= ~0x01;    // PE0 input
    GPIO_PORTE_DEN_R |= 0x01;
    GPIO_PORTE_AMSEL_R &= ~0x01;
    GPIO_PORTE_AFSEL_R &= ~0x01;
    GPIO_PORTE_PUR_R |= 0x01;     // Enable pull-up

    // --- Limit Switch Top: PE1 (input) ---
    GPIO_PORTE_DIR_R &= ~0x02;    // PE1 input
    GPIO_PORTE_DEN_R |= 0x02;
    GPIO_PORTE_AMSEL_R &= ~0x02;
    GPIO_PORTE_AFSEL_R &= ~0x02;
    GPIO_PORTE_PUR_R |= 0x02;

    // --- Limit Switch Bottom: PE2 (input) ---
    GPIO_PORTE_DIR_R &= ~0x04;    // PE2 input
    GPIO_PORTE_DEN_R |= 0x04;
    GPIO_PORTE_AMSEL_R &= ~0x04;
    GPIO_PORTE_AFSEL_R &= ~0x04;
    GPIO_PORTE_PUR_R |= 0x04;

    // --- Encoder Input: PD6 ---
    GPIO_PORTD_LOCK_R = 0x4C4F434B;
    GPIO_PORTD_CR_R |= 0x40;
    GPIO_PORTD_DIR_R &= ~0x40;    // PD6 input
    GPIO_PORTD_DEN_R |= 0x40;
    GPIO_PORTD_AMSEL_R &= ~0x40;
    GPIO_PORTD_AFSEL_R &= ~0x40;
    GPIO_PORTD_PUR_R |= 0x40;
}

/*#include "tm4c123gh6pm.h"
#include "gpio_init.h"

void GPIO_Init(void) {
    // Enable clocks for Ports A-F
    SYSCTL_RCGCGPIO_R |= 0x3F;
    while ((SYSCTL_PRGPIO_R & 0x3F) != 0x3F);

    // Example: Configure PortF Pin1 as output for LED
    GPIO_PORTF_DIR_R |= (1 << 1);
    GPIO_PORTF_DEN_R |= (1 << 1);

    // Motor control: Assume using PortB (PB0, PB1)
    GPIO_PORTB_DIR_R |= (1 << 0) | (1 << 1);
    GPIO_PORTB_DEN_R |= (1 << 0) | (1 << 1);

    // IR sensor input on PortE pin 0
    GPIO_PORTE_DIR_R &= ~(1 << 0);
    GPIO_PORTE_DEN_R |= (1 << 0);

    // Encoder input on PortC pin 4,5
    GPIO_PORTC_DIR_R &= ~((1 << 4) | (1 << 5));
    GPIO_PORTC_DEN_R |= (1 << 4) | (1 << 5);

    // Limit switches input on PortD pin 0 and 1
    GPIO_PORTD_DIR_R &= ~((1 << 0) | (1 << 1));
    GPIO_PORTD_DEN_R |= (1 << 0) | (1 << 1);

    // Buttons input for window control (PortA pin 2, 3)
    GPIO_PORTA_DIR_R &= ~((1 << 2) | (1 << 3));
    GPIO_PORTA_DEN_R |= (1 << 2) | (1 << 3);

    // Buzzer output (PortF pin 2)
    GPIO_PORTF_DIR_R |= (1 << 2);
    GPIO_PORTF_DEN_R |= (1 << 2);
}
*/
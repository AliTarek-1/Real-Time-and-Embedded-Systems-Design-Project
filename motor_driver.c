#include "motor_driver.h"
#include "tm4c123gh6pm.h"

#define MOTOR_IN1 0x01  // PB0
#define MOTOR_IN2 0x02  // PB1
#define MOTOR_EN  0x04  // PB2

void Motor_Init(void) {
    // Enable clock for GPIO Port B
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) == 0); // Wait until clock is ready

    // Set PB0, PB1, PB2 as output
    GPIO_PORTB_DIR_R |= (MOTOR_IN1 | MOTOR_IN2 | MOTOR_EN);
    GPIO_PORTB_DEN_R |= (MOTOR_IN1 | MOTOR_IN2 | MOTOR_EN);
    GPIO_PORTB_AFSEL_R &= ~(MOTOR_IN1 | MOTOR_IN2 | MOTOR_EN); // Disable alternate functions
    GPIO_PORTB_AMSEL_R &= ~(MOTOR_IN1 | MOTOR_IN2 | MOTOR_EN); // Disable analog functions
	//we could ignore all the initialization at the begining as we made it in the gpio_init()
    Motor_Stop(); // Ensure motor is off at startup
}

void Motor_Up(void) {
    GPIO_PORTB_DATA_R |= MOTOR_IN1;     // IN1 = 1
    GPIO_PORTB_DATA_R &= ~MOTOR_IN2;    // IN2 = 0
    GPIO_PORTB_DATA_R |= MOTOR_EN;      // Enable motor
}

void Motor_Down(void) {
    GPIO_PORTB_DATA_R &= ~MOTOR_IN1;    // IN1 = 0
    GPIO_PORTB_DATA_R |= MOTOR_IN2;     // IN2 = 1
    GPIO_PORTB_DATA_R |= MOTOR_EN;      // Enable motor
}

void Motor_Stop(void) {
    GPIO_PORTB_DATA_R &= ~(MOTOR_IN1 | MOTOR_IN2); // IN1 = 0, IN2 = 0
    GPIO_PORTB_DATA_R &= ~MOTOR_EN;                // Disable motor
}

void Motor_Up_Auto(void) {
    // One-touch auto-up simulation: Start motor up
    Motor_Up();
    // Auto-stop condition should be handled by position tracking task
}

void Motor_Down_Auto(void) {
    // One-touch auto-down simulation: Start motor down
    Motor_Down();
    // Auto-stop condition should be handled by position tracking task
}

// Driver: Ir Sensor
#include "ir_sensor.h"
#include "tm4c123gh6pm.h"

#define IR_SENSOR_PIN 0x01  // PE0

void IrSensorInit() {
    // Enable clock for Port E
    SYSCTL_RCGCGPIO_R |= 0x10;             // Port E
    while ((SYSCTL_PRGPIO_R & 0x10) == 0); // Wait until Port E is ready

    GPIO_PORTE_DIR_R &= ~IR_SENSOR_PIN;    // Set PE0 as input
    GPIO_PORTE_DEN_R |= IR_SENSOR_PIN;     // Digital enable PE0
    GPIO_PORTE_AMSEL_R &= ~IR_SENSOR_PIN;  // Disable analog
    GPIO_PORTE_AFSEL_R &= ~IR_SENSOR_PIN;  // Disable alternate functions
    GPIO_PORTE_PUR_R |= IR_SENSOR_PIN;     // Enable pull-up resistor
}

short IrSensorIsObstacleDetected() {
    // IR sensor pulls line LOW when obstacle is present
    return (GPIO_PORTE_DATA_R & IR_SENSOR_PIN) ? 0 : 1;
}

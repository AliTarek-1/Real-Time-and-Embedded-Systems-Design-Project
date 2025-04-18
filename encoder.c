#include "encoder.h"
#include "tm4c123gh6pm.h"

TaskHandle_t encoderTaskHandle = NULL;
volatile int encoderPosition = 0;

void EncoderInit(void) {
    SYSCTL_RCGCGPIO_R |= 0x08;             // Enable clock for Port D
    while ((SYSCTL_PRGPIO_R & 0x08) == 0); // Wait for Port D

    GPIO_PORTD_LOCK_R = 0x4C4F434B; // Unlock PD
    GPIO_PORTD_CR_R |= 0x40;        // Allow changes to PD6

    GPIO_PORTD_DIR_R &= ~0x40;      // PD6 as input
    GPIO_PORTD_DEN_R |= 0x40;       // Digital enable
    GPIO_PORTD_AFSEL_R &= ~0x40;    // Disable alternate functions
    GPIO_PORTD_AMSEL_R &= ~0x40;    // Disable analog
    GPIO_PORTD_PUR_R |= 0x40;       // Enable pull-up

    GPIO_PORTD_IS_R &= ~0x40;       // Edge-sensitive
    GPIO_PORTD_IBE_R &= ~0x40;      // Not both edges
    GPIO_PORTD_IEV_R &= ~0x40;      // Falling edge
    GPIO_PORTD_ICR_R |= 0x40;       // Clear interrupt
    GPIO_PORTD_IM_R |= 0x40;        // Unmask interrupt

    NVIC_EN0_R |= (1 << 3);         // Enable interrupt 3 (Port D)

    // Create the encoder task
    xTaskCreate(EncoderTask, "EncoderTask", 128, NULL, 2, &encoderTaskHandle);
}

void GPIOPortD_Handler(void) {
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if (GPIO_PORTD_RIS_R & 0x40) {
        vTaskNotifyGiveFromISR(encoderTaskHandle, &xHigherPriorityTaskWoken);
        GPIO_PORTD_ICR_R |= 0x40;
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

void EncoderTask(void *pvParameters) {
    for (;;) {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        encoderPosition++;
        // Optional: Add debounce, filtering, or threshold logic
    }
}

int Encoder_ReadPosition(void) {
    return encoderPosition;
}

void Encoder_ResetTop(void) {
    encoderPosition = 100; // Set top limit
}

void Encoder_ResetBottom(void) {
    encoderPosition = 0;
}

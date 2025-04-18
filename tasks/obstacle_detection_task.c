//#include "obstacle_detection_task.h"
//#include "ir_sensor.h"
//#include "motor_driver.h"
//#include "buzzer_alert.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"

//SemaphoreHandle_t xObstacleDetectedSemaphore;
//int current_IR_value=0;
//int previous_IR_value=0;

//void ObstacleDetectionTask(void *pvParameters) {
//    while (1) {
//			current_IR_value=IrSensorIsObstacleDetected();
//        if (current_IR_value && current_IR_value!=previous_IR_value ) {
//						previous_IR_value=current_IR_value;
//            // Notify other tasks
//					
//					//nshof dh momken neb'a neshelo aw neghyro
//            xSemaphoreGive(xObstacleDetectedSemaphore);

//            // Stop the motor and move down slightly to avoid obstacle
//            Motor_Stop();
//            Motor_Down();
//            vTaskDelay(pdMS_TO_TICKS(500)); // Move away from obstacle
//            Motor_Stop();

//            // Sound alert
//            Buzzer_On();
//            vTaskDelay(pdMS_TO_TICKS(200));
//            Buzzer_Off();

//            // Wait before checking again (avoid repeated triggers)
//            vTaskDelay(pdMS_TO_TICKS(500));
//        }
//				

//        // Check periodically
//        vTaskDelay(pdMS_TO_TICKS(100));
//    }
//}


#include "obstacle_detection_task.h"
#include "ir_sensor.h"
#include "motor_driver.h"
#include "buzzer_alert.h"
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdbool.h>

SemaphoreHandle_t xObstacleDetectedSemaphore;
bool obstaclePresent = false;  // Shared flag

void ObstacleDetectionTask(void *pvParameters) {
    // Initialize LED (PF1 = red)
    SYSCTL_RCGCGPIO_R |= 0x20;             // Enable Port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0); // Wait
    GPIO_PORTF_DIR_R |= 0x02;              // PF1 output
    GPIO_PORTF_DEN_R |= 0x02;              // PF1 digital enable
    GPIO_PORTF_DATA_R &= ~0x02;            // PF1 off initially

    short previousIR = 0;

    while (1) {
        short currentIR = IrSensorIsObstacleDetected();

        if (currentIR && !previousIR) {
            previousIR = 1;
            obstaclePresent = true;

            GPIO_PORTF_DATA_R |= 0x02; // Turn ON red LED

            xSemaphoreGive(xObstacleDetectedSemaphore);

            Motor_Stop();
            Motor_Down();
            vTaskDelay(pdMS_TO_TICKS(500));
            Motor_Stop();

            Buzzer_On();
            vTaskDelay(pdMS_TO_TICKS(200));
            Buzzer_Off();
        }

        // Obstacle cleared
        if (!currentIR && previousIR) {
            previousIR = 0;
            obstaclePresent = false;

            GPIO_PORTF_DATA_R &= ~0x02; // Turn OFF red LED
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

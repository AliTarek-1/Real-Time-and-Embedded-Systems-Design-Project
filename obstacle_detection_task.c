#include "obstacle_detection_task.h"
#include "ir_sensor.h"
#include "motor_driver.h"
#include "buzzer_alert.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

extern SemaphoreHandle_t xObstacleDetectedSemaphore;

void ObstacleDetectionTask(void *pvParameters) {
    while (1) {
        if (IR_Sensor_ObstacleDetected()) {
            // Notify other tasks
            xSemaphoreGive(xObstacleDetectedSemaphore);

            // Stop the motor and move down slightly to avoid obstacle
            Motor_Stop();
            Motor_Down();
            vTaskDelay(pdMS_TO_TICKS(500)); // Move away from obstacle
            Motor_Stop();

            // Sound alert
            Buzzer_On();
            vTaskDelay(pdMS_TO_TICKS(200));
            Buzzer_Off();

            // Wait before checking again (avoid repeated triggers)
            vTaskDelay(pdMS_TO_TICKS(500));
        }

        // Check periodically
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

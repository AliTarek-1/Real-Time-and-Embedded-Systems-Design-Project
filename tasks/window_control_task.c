//#include "window_control_task.h"
//#include "motor_driver.h"
//#include "limit_switch.h"
//#include "FreeRTOS.h"
//#include "task.h"
//#include "semphr.h"
//#include <stdio.h>
//#include <stdbool.h>

//extern SemaphoreHandle_t xWindowControlSemaphore;
//extern SemaphoreHandle_t xObstacleDetectedSemaphore;

//extern bool isAutoMode;
//extern bool isMovingDown;
//extern bool windowLock;

//void WindowControlTask(void *pvParameters) {
//    while (1) {
//        // Wait for window control trigger
//        if (xSemaphoreTake(xWindowControlSemaphore, portMAX_DELAY)) {
//            
//            // Skip operation if lock is enabled
//            if (windowLock) {
//                Motor_Stop();
//                continue;
//            }

//            if (isMovingDown) {
//                // DOWNWARD movement
//                if (LimitSwitch_LowerTriggered()) {
//                    Motor_Stop();
//                } else {
//                    Motor_Down();

//                    // In auto mode, keep running until limit is reached or obstacle
//                    if (isAutoMode) {
//                        while (!LimitSwitch_LowerTriggered()) {
//                            // Check for obstacle
//                            if (xSemaphoreTake(xObstacleDetectedSemaphore, 0)) {
//                                Motor_Stop();
//                                break;
//                            }
//                            vTaskDelay(pdMS_TO_TICKS(50));
//                        }
//                        Motor_Stop();
//                    } else {
//                        vTaskDelay(pdMS_TO_TICKS(100)); // manual small step
//                        Motor_Stop();
//                    }
//                }
//            } else {
//                // UPWARD movement
//                if (LimitSwitch_UpperTriggered()) {
//                    Motor_Stop();
//                } else {
//                    Motor_Up();

//                    if (isAutoMode) {
//                        while (!LimitSwitch_UpperTriggered()) {
//                            // Check for obstacle
//                            if (xSemaphoreTake(xObstacleDetectedSemaphore, 0)) {
//                                Motor_Stop();
//                                break;
//                            }
//                            vTaskDelay(pdMS_TO_TICKS(50));
//                        }
//                        Motor_Stop();
//                    } else {
//                        vTaskDelay(pdMS_TO_TICKS(100));
//                        Motor_Stop();
//                    }
//                }
//            }
//        }
//    }
//}


#include "window_control_task.h"
#include "motor_driver.h"
#include "Buttons_Contols.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdbool.h>

extern SemaphoreHandle_t xWindowControlSemaphore;
extern SemaphoreHandle_t xObstacleDetectedSemaphore;
extern bool obstaclePresent;  // From obstacle_detection_task.c

extern bool windowLock;

void WindowControlTask(void *pvParameters) {
    ButtonState buttonState;
    bool isMovingDown;
    bool isAutoMode;

    while (1) {
        if (xSemaphoreTake(xWindowControlSemaphore, portMAX_DELAY)) {

            // Skip operation if lock is enabled
            if (windowLock) {
                Motor_Stop();
                continue;
            }

            // Read button and mode status
            buttonState = Buttons_Read();
            isAutoMode = Mode_IsAuto();

            // Determine direction
            if (buttonState.down) {
                isMovingDown = true;
            } else if (buttonState.up) {
                isMovingDown = false;
            } else {
                Motor_Stop();
                continue;
            }

            // Execute motor action
            if (isMovingDown) {
                Motor_Down();
                if (isAutoMode) {
                    while (Buttons_Read().down && !xSemaphoreTake(xObstacleDetectedSemaphore, 0)) {
                        vTaskDelay(pdMS_TO_TICKS(50));
                    }
                } else {
                    vTaskDelay(pdMS_TO_TICKS(100));
                }
                Motor_Stop();
            } else {
								if (obstaclePresent) {
								Motor_Stop(); // Do not allow movement
								continue;
								}

                Motor_Up();
                if (isAutoMode) {
                    while (Buttons_Read().up && !xSemaphoreTake(xObstacleDetectedSemaphore, 0)) {
                        vTaskDelay(pdMS_TO_TICKS(50));
                    }
                } else {
                    vTaskDelay(pdMS_TO_TICKS(100));
                }
                Motor_Stop();
            }
        }
    }
}

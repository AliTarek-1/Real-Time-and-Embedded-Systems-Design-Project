#include "FreeRTOS.h"
#include "task.h"
#include "gpio_init.h"
#include "motor_driver.h"
#include "encoder.h"
#include "ir_sensor.h"
#include "limit_switch.h"
#include "buzzer_alert.h"
#include "lcd_display.h"
#include "window_control_task.h"
#include "obstacle_detection_task.h"
#include "position_tracking_task.h"
#include "system_status_task.h"
#include "Buttons_Contols.h"

SemaphoreHandle_t xWindowControlSemaphore;

int main(void) {
    GpioInitInit();
    Motor_Init();
    IrSensorInit();
    EncoderInit();
    LimitSwitch_Init();
    BuzzerAlertInit();
    LCD_Init();
		Buttons_Init();
    xWindowControlSemaphore = xSemaphoreCreateBinary();

    xTaskCreate(WindowControlTask, "WindowCtrl", 128, NULL, 2, NULL);
    xTaskCreate(ObstacleDetectionTask, "Obstacle", 128, NULL, 2, NULL);
    xTaskCreate(PositionTrackingTask, "Encoder", 128, NULL, 1, NULL);
    xTaskCreate(SystemStatusTask, "Status", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);
}

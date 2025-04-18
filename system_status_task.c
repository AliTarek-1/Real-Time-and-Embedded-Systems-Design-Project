#include "system_status_task.h"
#include "lcd_display.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdbool.h>

// External flags for system status
extern bool windowLock;
extern bool isAutoMode;
extern bool isMovingDown;

void SystemStatusTask(void *pvParameters) {
    char statusBuffer[32];

    while (1) {
        LCD_SetCursor(0, 0); // First row
        LCD_DisplayString("System: Active  ");

        // Compose mode and direction
        LCD_SetCursor(1, 0); // Second row
        if (windowLock) {
            LCD_DisplayString("Mode: LOCKED    ");
        } else {
            snprintf(statusBuffer, sizeof(statusBuffer), "Mode:%s %s   ",
                     isAutoMode ? "Auto" : "Manual",
                     isMovingDown ? "Down" : "Up");
            LCD_DisplayString(statusBuffer);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

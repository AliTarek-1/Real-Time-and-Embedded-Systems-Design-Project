#include "position_tracking_task.h"
#include "encoder.h"
#include "lcd_display.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void PositionTrackingTask(void *pvParameters) {
    char lcdBuffer[16];

    while (1) {
        int32_t pos = Encoder_ReadPosition();

        // Format and display the position on the LCD
        snprintf(lcdBuffer, sizeof(lcdBuffer), "Pos: %ld", pos);
        LCD_SetCursor(1, 0); // Second row, start at column 0
        LCD_DisplayString("                "); // Clear previous content
        LCD_SetCursor(1, 0);
        LCD_DisplayString(lcdBuffer);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

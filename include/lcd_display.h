#ifndef _LCD_DISPLAY_H_
#define _LCD_DISPLAY_H_

#include <stdint.h>

// Initialization
void LCD_Init(void);

// Commands
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);

// Data Display
void LCD_DisplayString(const char* str);

// Internal Helper Functions (optional to expose)
void LCD_SendCommand(uint8_t cmd);
void LCD_SendData(uint8_t data);

#endif // _LCD_DISPLAY_H_

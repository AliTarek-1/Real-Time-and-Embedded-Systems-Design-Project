#include "lcd_display.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <string.h>

#define LCD_DATA_PORT GPIO_PORTB_DATA_R
#define LCD_CTRL_PORT GPIO_PORTD_DATA_R

#define RS 0x01   // PD0
#define RW 0x02   // PD1
#define EN 0x04   // PD2

void LCD_EnablePulse(void) {
    LCD_CTRL_PORT |= EN;
    for (volatile int i = 0; i < 1000; i++);
    LCD_CTRL_PORT &= ~EN;
    for (volatile int i = 0; i < 1000; i++);
}

void LCD_SendNibble(uint8_t nibble) {
    LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (nibble & 0x0F);
    LCD_EnablePulse();
}

void LCD_SendCommand(uint8_t cmd) {
    LCD_CTRL_PORT &= ~(RS | RW);
    LCD_SendNibble(cmd >> 4);
    LCD_SendNibble(cmd & 0x0F);
    for (volatile int i = 0; i < 10000; i++);
}

void LCD_SendData(uint8_t data) {
    LCD_CTRL_PORT |= RS;
    LCD_CTRL_PORT &= ~RW;
    LCD_SendNibble(data >> 4);
    LCD_SendNibble(data & 0x0F);
    for (volatile int i = 0; i < 1000; i++);
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
}

void LCD_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x0A;  // Enable clock for Port B and D
    while ((SYSCTL_PRGPIO_R & 0x0A) == 0);

    GPIO_PORTB_DIR_R |= 0x0F;
    GPIO_PORTB_DEN_R |= 0x0F;

    GPIO_PORTD_DIR_R |= (RS | RW | EN);
    GPIO_PORTD_DEN_R |= (RS | RW | EN);

    LCD_CTRL_PORT &= ~(RS | RW | EN);

    LCD_SendCommand(0x28); // Function set: 4-bit, 2 line, 5x8 dots
    LCD_SendCommand(0x0C); // Display ON, Cursor OFF
    LCD_SendCommand(0x06); // Entry mode
    LCD_Clear();
}

void LCD_DisplayString(const char* str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address = (row == 0) ? col : (0x40 + col);
    LCD_SendCommand(0x80 | address);
}

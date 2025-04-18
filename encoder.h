#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <stdint.h>
#include <stdbool.h>
#include "FreeRTOS.h"
#include "task.h"

void EncoderInit(void);
int Encoder_ReadPosition(void);
void Encoder_ResetTop(void);
void Encoder_ResetBottom(void);
void EncoderTask(void* pvParameters);

extern TaskHandle_t encoderTaskHandle;

#endif // _ENCODER_H_

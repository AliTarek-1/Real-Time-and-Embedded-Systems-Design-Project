#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdint.h>

void Motor_Init(void);
void Motor_Up(void);
void Motor_Down(void);
void Motor_Stop(void);
void Motor_Up_Auto(void);
void Motor_Down_Auto(void);

#endif // _MOTOR_DRIVER_H_

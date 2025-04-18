#ifndef _BUZZER_ALERT_H_
#define _BUZZER_ALERT_H_

#include <stdbool.h>
#include <stdint.h>

void BuzzerAlertInit(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_Toggle(void);
void Buzzer_UpdateAlert(void);

#endif // _BUZZER_ALERT_H_

#ifndef _LIMIT_SWITCH_H_
#define _LIMIT_SWITCH_H_

#include <stdbool.h>
#include <stdint.h>

void LimitSwitch_Init(void);
bool LimitSwitch_UpperTriggered(void);
bool LimitSwitch_LowerTriggered(void);

#endif // _LIMIT_SWITCH_H_

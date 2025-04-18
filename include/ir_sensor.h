#ifndef _IR_SENSOR_H_
#define _IR_SENSOR_H_

#include <stdint.h>
#include <stdbool.h>

void IrSensorInit(void);
short IrSensorIsObstacleDetected(void);

#endif // _IR_SENSOR_H_

#ifndef POSITION_TRACKING_TASK_H
#define POSITION_TRACKING_TASK_H

#include "FreeRTOS.h"
#include "task.h"

/**
 * @brief Task that handles position tracking and display
 *
 * This task continuously reads the encoder position and displays it
 * on the LCD screen with a refresh rate of 200ms.
 *
 * @param pvParameters Task parameters (unused)
 */
void PositionTrackingTask(void* pvParameters);

#endif // POSITION_TRACKING_TASK_H
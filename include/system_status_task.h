#ifndef SYSTEM_STATUS_TASK_H
#define SYSTEM_STATUS_TASK_H

#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

	void SystemStatusTask(void* pvParameters);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_STATUS_TASK_H
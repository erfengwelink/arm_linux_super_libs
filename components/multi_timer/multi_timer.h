/*****************************************************************************
 Copyright 2023 WRT. https://www.wrtsz.com/

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 ******************************************************************************/

#ifndef _MULTI_TIMER_H_
#define _MULTI_TIMER_H_
#include "list.h"
#include <stdint.h>

#ifdef __cplusplus  
extern "C" {  
#endif

typedef uint64_t (*PlatformTicksFunction_t)(void);

typedef struct MultiTimerHandle MultiTimer;

typedef void (*MultiTimerCallback_t)(MultiTimer* timer, void* userData);

struct MultiTimerHandle {
    MultiTimer* next;
    uint64_t deadline;
    MultiTimerCallback_t callback;
    void* userData;
};

/**
 * @brief Platform ticks function.
 * 
 * @param ticksFunc ticks function.
 * @return int 0 on success, -1 on error.
 */
int MultiTimerInstall(PlatformTicksFunction_t ticksFunc);

/**
 * @brief Start the timer work, add the handle into work list.
 * 
 * @param timer target handle strcut.
 * @param timing Set the start time.
 * @param callback deadline callback.
 * @param userData user data.
 * @return int 0: success, -1: fail.
 */
int MultiTimerStart(MultiTimer* timer, uint64_t timing, MultiTimerCallback_t callback, void* userData);

/**
 * @brief Stop the timer work, remove the handle off work list.
 * 
 * @param timer target handle strcut.
 * @return int 0: success, -1: fail.
 */
int MultiTimerStop(MultiTimer* timer);

/**
 * @brief Check the timer expried and call callback.
 * 
 * @return int The next timer expires.
 */
int MultiTimerYield(void);

#ifdef __cplusplus
} 
#endif



#endif /* _MULTI_TIMER_H_ */


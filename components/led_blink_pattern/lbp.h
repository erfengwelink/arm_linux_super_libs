#ifndef _LED_BLK_PATTERN_H_
#define _LED_BLK_PATTERN_H_


#include <stdint.h>
#include "../multi_timer/multi_timer.h"




typedef struct {
    int n;
    int16_t *delay;
} led_status_pattern_t;


#define LED_BLINK_PATTERN(...) { \
    .n = sizeof((int16_t[])__VA_ARGS__) / sizeof(int16_t), \
    .delay = (int16_t[])__VA_ARGS__, \
}

typedef struct {
    uint8_t gpio;
    uint8_t active;
    MultiTimer timer;
    int n;
    led_status_pattern_t *pattern;
    led_status_pattern_t *signal_pattern;
} led_status_t;


led_status_t led_status_init(uint8_t gpio, uint8_t active_level);
void led_status_done(led_status_t *status);

// Set looped pattern that will be executing until changed.
// Passing NULL as pattern disables blinking.
void led_status_set(led_status_t *status, led_status_pattern_t *pattern);

// Execute given pattern once and then return to pattern set by led_status_set().
void led_status_signal(led_status_t *status, led_status_pattern_t *pattern);









#endif /* _LED_BLK_PATTERN_H_ */
#include "lbp.h"
#include <stdio.h>

#define STATUS_LED_PIN 13
// 1000ms ON, 1000ms OFF
led_status_pattern_t waiting_wifi = LED_BLINK_PATTERN({1000, -1000});
// static 
led_status_t status = {0};
int main(int argc, char **argv)
{
    // static 
    status = led_status_init(STATUS_LED_PIN, 1);
    printf("1111111 \r\n");
    led_status_set(&status, &waiting_wifi);
    printf("hello,  lbp ! \r\n");
    while(1) {
        usleep(10 * 1000);
        MultiTimerYield();
    }
    return 0;
}
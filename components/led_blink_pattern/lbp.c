#include <stdio.h>
#include <stdlib.h>
#include "lbp.h"

//-----------------------------------------------------------------------------

static MultiTimer leds_timer[3] = {0};
//-----------------------------------------------------------------------------

#define ABS(x) (((x) < 0) ? -(x) : (x))

static void led_status_write(led_status_t *status, bool on) {
    // gpio_write( ? status->active : !status->active);
    printf(" gpio_write gpio: %d , st %d \r\n", status->gpio, on);
}

static void led_status_tick(MultiTimer* timer, void *status) {
    led_status_t *pst = (led_status_t *)status;
    led_status_pattern_t *p = pst->signal_pattern ? pst->signal_pattern : pst->pattern;
    if (!p) {
        // sdk_os_timer_disarm(&status->timer);
    printf(" 99999 %p \r\n", status);

        // MultiTimerStop(&pst->timer);
        led_status_write(pst, false);
        return;
    }
    printf(" 3333333333 %p \r\n", status);

    led_status_write(pst, p->delay[pst->n] > 0);
    // sdk_os_timer_arm(&status->timer, ABS(p->delay[status->n]), 0);
    printf(" 7777777 pst->n = %d \r\n", pst->n);
    pst->n = (pst->n + 1) % p->n;
    if (pst->signal_pattern && pst->n == 0) {
        pst->signal_pattern = NULL;
    }
    printf(" 666666 pst->n = %d \r\n", pst->n);

    
    printf(" 22222 p->delay[pst->n] = %d \r\n", ABS(p->delay[pst->n]));
    MultiTimerStart(&pst->timer, ABS(p->delay[pst->n])/10, led_status_tick, status);
    
}

led_status_t led_status_init(uint8_t gpio, uint8_t active_level) {
    led_status_t *status = malloc(sizeof(led_status_t));
    status->gpio = gpio;
    status->active = active_level;
    // sdk_os_timer_setfn(&status->timer, (void(*)(void*))led_status_tick, status);
    // status->timer = &leds_timer[index];
    // gpio_enable(status->gpio, GPIO_OUTPUT);
    // MultiTimerStart(&status->timer, ABS(p->delay[status->n]), (void(*)(void*))led_status_tick, "");
    printf(" 8888 \r\n");
    
    led_status_write(status, false);
    printf(" 1212122 \r\n");
    return *status;
}

void led_status_done(led_status_t *status) {
    // sdk_os_timer_disarm(&status->timer);
    // gpio_disable(status->gpio);
    MultiTimerStop(&status->timer);
    free(status);
}

void led_status_set(led_status_t *status, led_status_pattern_t *pattern) {
    status->pattern = pattern;

    if (!status->signal_pattern) {
        status->n = 0;
        led_status_tick(&status->timer, status);
    }
    printf(" led_status_set 00000 !!! \r\n");
}

void led_status_signal(led_status_t *status, led_status_pattern_t *pattern) {
    if (!status->signal_pattern && !pattern)
        return;

    status->signal_pattern = pattern;
    status->n = 0;  // whether signal pattern is NULL or not, just reset the state
    led_status_tick(&status->timer, status);
}
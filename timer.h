// timer.h
#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
extern volatile uint16_t timer_count;

void timer_init(void);
uint8_t timer_has_elapsed(void);
void timer_reset(void);
void timer_set_interval(uint16_t ms);

#endif
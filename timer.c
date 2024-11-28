// timer.c
#include "timer.h"
#include <avr/interrupt.h>

volatile uint16_t timer_count = 0;
volatile uint16_t timer_target = 0;
volatile uint8_t timer_flag = 0;

ISR(TIMER1_COMPA_vect) {
    timer_count++;
    if (timer_count >= timer_target) {
        timer_flag = 1;
        timer_count = 0;
    }
}

void timer_init(void) {
    // Benytter Clear Timer on Compare Match
    TCCR1B = (1 << WGM12) | (1 << CS11); 
    OCR1A = 1999; 
    TIMSK1 = (1 << OCIE1A); // Compare match interrupt
}

uint8_t timer_has_elapsed(void) {
    return timer_flag;
}

void timer_reset(void) {
    timer_flag = 0;
    timer_count = 0;
}

void timer_set_interval(uint16_t ms) {
    timer_target = ms;
}
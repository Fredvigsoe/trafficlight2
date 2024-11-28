// scenarios.c
#include "scenarios.h"

void scenario_ns_red_ew_red(void) {
    PORTD = NS_RED | EW_RED;
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void scenario_ns_red_yellow_ew_red(void) {
    PORTD = (NS_RED | NS_YELLOW | EW_RED);
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void scenario_ns_green_ew_red(void) {
    PORTD = (NS_GREEN | EW_RED);
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void scenario_ns_yellow_ew_red(void) {
    PORTD = (NS_YELLOW | EW_RED);
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void scenario_ns_red_ew_red_yellow(void) {
    PORTD = (NS_RED | EW_RED | EW_YELLOW);
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void scenario_ns_red_ew_green(void) {
    PORTD = (NS_RED | EW_GREEN);
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void scenario_ns_red_ew_yellow(void) {
    PORTD = (NS_RED | EW_YELLOW);
    PORTB = NS_RED_FOOT | EW_RED_FOOT;
}

void pedestrian_ns_green(void) {
    PORTB |= NS_GREEN_FOOT;
    PORTB &= ~NS_RED_FOOT;
}

void pedestrian_ns_red(void) {
    PORTB &= ~NS_GREEN_FOOT;
    PORTB |= NS_RED_FOOT;
}

void pedestrian_ew_green(void) {
    PORTB |= EW_GREEN_FOOT;
    PORTB &= ~EW_RED_FOOT;
}

void pedestrian_ew_red(void) {
    PORTB &= ~EW_GREEN_FOOT;
    PORTB |= EW_RED_FOOT;
}


void indicators_on(void) {
    PORTC |= (NS_BUTTON_INDICATOR | EW_BUTTON_INDICATOR);
}

void indicators_off(void) {
    PORTC &= ~(NS_BUTTON_INDICATOR | EW_BUTTON_INDICATOR);
}
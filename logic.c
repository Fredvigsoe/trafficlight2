// logic.c
#include "logic.h"
#include "scenarios.h"
#include "timer.h"
#include <avr/interrupt.h>

// States for the traffic light system
typedef enum {
    STATE_NS_RED_EW_RED,
    STATE_NS_RED_YELLOW,
    STATE_NS_GREEN,
    STATE_NS_YELLOW,
    STATE_EW_RED_YELLOW,
    STATE_EW_GREEN,
    STATE_EW_YELLOW
} State;
extern volatile uint16_t timer_count;
static volatile uint8_t ns_button_pressed = 0;
static volatile uint8_t ew_button_pressed = 0;
static State current_state = STATE_NS_RED_EW_RED;

// Button interrupt handlers
ISR(PCINT0_vect) {
    // Se hvilken knap der er trykket på (virker kun når der er rødt)
    if ((PINB & BUTTON_NS) && (PORTB & NS_RED_FOOT)) {
        ns_button_pressed = 1;
        PORTC |= NS_BUTTON_INDICATOR;
    }
    if ((PINB & BUTTON_EW) && (PORTB & EW_RED_FOOT)) {
        ew_button_pressed = 1;
        PORTC |= EW_BUTTON_INDICATOR;
    }
}

void logic_init(void) {
    // Configure pins
    DDRD = NS_GREEN | NS_YELLOW | NS_RED | EW_GREEN | EW_YELLOW | EW_RED;
    DDRB = NS_GREEN_FOOT | NS_RED_FOOT | EW_GREEN_FOOT | EW_RED_FOOT;
    DDRC = NS_BUTTON_INDICATOR | EW_BUTTON_INDICATOR;
    
    // Enable pull-up resistors for buttons
    PORTB |= (BUTTON_NS | BUTTON_EW);
    
    // Configure pin change interrupt for buttons
    PCICR |= (1 << PCIE0);  // Enable PCINT0
    PCMSK0 |= (BUTTON_NS | BUTTON_EW);  // Enable interrupt for both buttons
    
    // Initialize timer
    timer_init();
    
    // Start with all red
    scenario_ns_red_ew_red();
    
    // Enable global interrupts
    sei();
}

void logic_run(void) {
    static uint8_t ns_pedestrian_active = 0;
    static uint8_t ew_pedestrian_active = 0;

    switch (current_state) {
        case STATE_NS_RED_EW_RED:
            timer_set_interval(2000);  // 2 second red-red phase
            scenario_ns_red_ew_red();
            if (timer_has_elapsed()) {
                current_state = STATE_NS_RED_YELLOW;
                timer_reset();
            }
            break;
            
        case STATE_NS_RED_YELLOW:
            timer_set_interval(1000);  // 1 second red-yellow phase
            scenario_ns_red_yellow_ew_red();
            if (timer_has_elapsed()) {
                current_state = STATE_NS_GREEN;
                timer_reset();
                if (ns_button_pressed) {
                    ns_pedestrian_active = 1;
                    PORTC &= ~NS_BUTTON_INDICATOR;
                    ns_button_pressed = 0;
                }
                // Add EW button press handling for red-red phase
                if (ew_button_pressed) {
                    ew_pedestrian_active = 1;
                    PORTC &= ~EW_BUTTON_INDICATOR;
                    ew_button_pressed = 0;
                }
            }
            break;
            
        case STATE_NS_GREEN:
            timer_set_interval(10000);  // 10 second green phase
            scenario_ns_green_ew_red();
            if (ns_pedestrian_active && timer_count >= 2000) {  // After 2 seconds
                pedestrian_ns_green();
            }
            if (timer_has_elapsed()) {
                if (ns_pedestrian_active) {
                    pedestrian_ns_red();
                    ns_pedestrian_active = 0;
                }
                current_state = STATE_NS_YELLOW;
                timer_reset();
            }
            break;
            
        case STATE_NS_YELLOW:
            timer_set_interval(1000);  // 1 second yellow phase
            scenario_ns_yellow_ew_red();
            if (timer_has_elapsed()) {
                current_state = STATE_EW_RED_YELLOW;  // Transition to EW phase
                timer_reset();
            }
            break;
            
        case STATE_EW_RED_YELLOW:
            timer_set_interval(1000);  // 1 second red-yellow phase for EW
            scenario_ns_red_yellow_ew_red();
            if (timer_has_elapsed()) {
                current_state = STATE_EW_GREEN;
                timer_reset();
                if (ew_button_pressed) {
                    ew_pedestrian_active = 1;
                    PORTC &= ~EW_BUTTON_INDICATOR;
                    ew_button_pressed = 0;
                }
            }
            break;
            
        case STATE_EW_GREEN:
            timer_set_interval(10000);  // 10 second green phase for EW
            scenario_ns_red_ew_green();
            if (ew_pedestrian_active && timer_count >= 2000) {  // After 2 seconds
                pedestrian_ew_green();
            }
            if (timer_has_elapsed()) {
                if (ew_pedestrian_active) {
                    pedestrian_ew_red();
                    ew_pedestrian_active = 0;
                }
                current_state = STATE_EW_YELLOW;
                timer_reset();
            }
            break;
            
        case STATE_EW_YELLOW:
            timer_set_interval(1000);  // 1 second yellow phase for EW
            scenario_ns_red_ew_yellow();
            if (timer_has_elapsed()) {
                current_state = STATE_NS_RED_EW_RED;  // Back to red-red phase
                timer_reset();
            }
            break;
            
        default:
            current_state = STATE_NS_RED_EW_RED;
            break;
    }
}

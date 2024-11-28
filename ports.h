#ifndef PORTS_H
#define PORTS_H

#include <avr/io.h>
#include <stdint.h>

// Pins for traffic lights (NS and EW LEDs)
#define NS_GREEN   (1 << 2)  // PD2 - Green NS (D2)
#define NS_YELLOW  (1 << 3)  // PD3 - Yellow NS (D3)
#define NS_RED     (1 << 4)  // PD4 - Red NS (D4)

#define EW_GREEN   (1 << 5)  // PD5 - Green EW (D5)
#define EW_YELLOW  (1 << 6)  // PD6 - Yellow EW (D6)
#define EW_RED     (1 << 7)  // PD7 - Red EW (D7)

// Pins for pedestrians (NS and EW)
#define NS_GREEN_FOOT (1 << 0)  // PB0 - Green pedestrian NS (D8)
#define NS_RED_FOOT   (1 << 1)  // PB1 - Red pedestrian NS (D9)
#define EW_GREEN_FOOT (1 << 2)  // PB2 - Green pedestrian EW (D10)
#define EW_RED_FOOT   (1 << 3)  // PB3 - Red pedestrian EW (D11)

// Pedestrian buttons
#define BUTTON_NS (1 << 4)  // Button for NS (PB4 - D12)
#define BUTTON_EW (1 << 5)  // Button for EW (PB5 - D13)

// Button indicators
#define NS_BUTTON_INDICATOR (1 << 0)  // PC0 (A0)
#define EW_BUTTON_INDICATOR (1 << 1)  // PC1 (A1)

#endif

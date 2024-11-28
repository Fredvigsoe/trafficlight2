// main.c
#include <avr/io.h>
#include "logic.h"

int main(void) {
    logic_init();
    
    while (1) {
        logic_run();
    }
    
    return 0;
}
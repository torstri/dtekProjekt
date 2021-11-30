#include <pic32mx.h>
#include <stdint.h>

void timerInit(){
    T2CON = 0x0; // Reset clock incase
    T2CON |= 0x800; // Set timer on
    T2CON |= 0x70; // Set prescale to 256
}
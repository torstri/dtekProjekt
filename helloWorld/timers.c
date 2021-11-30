#include <pic32mx.h>
#include <stdint.h>

void timerInit(){

    // Initialize interrupts and set priority
    IPCSET(2) = 0x0000000C;
    IPCSET(2) = 0x00000001;
    IECSET(0) = 0x00000100;
    
    T2CON = 0x0; // Reset clock incase
    T2CON |= 0x800; // Set timer on
    T2CON |= 0x70; // Set prescale to 256
}
#include <pic32mx.h>
#include <stdint.h>

void timerInit(){

    // Initialize interrupts and set priority
    IPCSET(2) = 0x0000000C;
    IPCSET(2) = 0x00000001;
    IECSET(0) = 0x00000100;
    
    T2CON = 0x0; // Reset clock incase
    T2CON |= 0x8000; // Set timer on
    T2CON |= 0x70; // Set prescale to 256
    PR2 = 0x145A; // Set period to 5 210 which should lead to interrupts 60 times a second
    // Enable interrups and set priority
    IPCSET(2) = 0x0000000C;
    IPCSET(2) = 0x00000001;
    IECSET(0) = 0x00000100;
    // Add enable_interrups somewhere in assembly code?
}
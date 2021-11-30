#include <pic32mx.h>
#include <stdint.h>

// Btn1 = RF1 = Register F bit 1 in both TRIS and PORT
// Btn2-4 = RD5-7 = Register D bit 5-7 in both TRIS and PORT 

void btnsInit(void){
    TRISD |= 0xFE0; // Set btns 2-4 to input
    TRISF |= 0b10; // Set bit 1 to input
}

int getbtns(void)
{
    int buttons = PORTD & 0xE0;
    buttons >>= 5;
    return buttons;
}
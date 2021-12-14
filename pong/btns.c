#include <pic32mx.h>
#include <stdint.h>

// Btn1 = RF1 = Register F bit 1 in both TRIS and PORT
// Btn2-4 = RD5-7 = Register D bit 5-7 in both TRIS and PORT 

void btnsInit(void){
    TRISD |= 0xE0; // Set btns 2-4 to input
    TRISF |= 0x2; // Set bit 1 to input
}

/**
 * @brief Retuns an int with bits 0-4 as btn1,btn2,btn3,btn4
 * 
 * @return int 
 */
int getButtons(void)
{
    int buttons1 = PORTF & 0x2; // xxXx
    buttons1 >>= 1; // xxxX
    int buttons2to4 = PORTD & 0xE0; //ZZZz zzzz
    buttons2to4 >>= 4; // zzzz ZZZz
    buttons1 += buttons2to4;
    return buttons1;
}
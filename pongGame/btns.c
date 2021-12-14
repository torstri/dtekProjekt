#include <pic32mx.h>
#include <stdint.h>

// Btn1 = RF1 = Register F bit 1 in both TRIS and PORT
// Btn2-4 = RD5-7 = Register D bit 5-7 in both TRIS and PORT 

void btnsInit(void){
    TRISD |= 0xE0; // Set btns 2-4 to input
    TRISF |= 0x2; // Set btn 1 to input
}

/**
 * @brief Retuns an int with bits 0-3 as btn1,btn2,btn3,btn4
 * 
 * @return int 
 */
int getButtons(void)
{
    int buttons1 = PORTF & 0x2; // Retrieves input from btn 1
    buttons1 >>= 1; // Right shift by 1 so relevant bit is stored in int
    int buttons2to4 = PORTD & 0xE0; //Retrieves input from btn 2-4
    buttons2to4 >>= 4; // Right shift by 4 so relevant bit is stored in int
    buttons1 += buttons2to4; //Add input from btn 2-4 to int for btn1, so that input from all btns can be read from an int
    return buttons1;
}
#include <pic32mx.h>
#include <stdint.h>

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9

#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

void delay(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

uint8_t screen[512]; // Själva bilden, ett tal är 8-bitar, alltså 8 rader vertikalt, sen blir 
					 // index 0 - 127 
					 // Samma sak som [0,0] till [7,127], 
					 // index 128-255 blir samma som [8,0] - [15, 127], 
					 // index 256 - 383 blir [16, 0] - [23, 127]
					 // index 384 - 511 blir [24, 0] - [31, 127]

int main(void) {
	
	/* Set up peripheral bus clock */
	OSCCON &= ~0x180000;
	OSCCON |= 0x080000;
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	
	/* Clear SPIROV*/
	SPI2STATCLR &= ~0x40;
	/* Set CKP = 1, MSTEN = 1; */
    SPI2CON |= 0x60;
	
	/* Turn on SPI */
	SPI2CONSET = 0x8000;
	
	// Initialize timers
	timerInit();
	// Initialize btns
	btnsInit();
	//Initial setup for the display
	display_init();
	// Clear display just in case
	display_clear();
	//Set all pixels to off
	resetDisplay(screen);
	//Start the game;
	start_game(screen);
	displayString(3, "Hello");
	while(1){
		continueGame(screen);
	}
	//Update the display
	//updateDisplay(screen);
	//delay(100);
	
	return 0;
}


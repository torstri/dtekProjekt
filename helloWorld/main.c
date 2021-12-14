#include <pic32mx.h>
#include <stdint.h>


char textbuffer[4][16]; // Handles text and score for display

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
	while(1){
		continueGame(screen);
	}
	
	return 0;
}


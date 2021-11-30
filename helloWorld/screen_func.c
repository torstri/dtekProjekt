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



uint8_t screen[512]; // Själva bilden, ett tal är 8-bitar, alltså 8 rader vertikalt, sen blir 
					 // index 0 - 127 
					 // Samma sak som [0,0] till [7,127], 
					 // index 128-255 blir samma som [8,0] - [15, 127], 
					 // index 256 - 383 blir [16, 0] - [23, 127]
					 // index 384 - 511 blir [24, 0] - [31, 127]


char textbuffer[4][16]; // Egentligen onödig men kan vara najs för att hårdkoda grejer senare



uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 0x01));
	return SPI2BUF;
}

void display_image(int x, const uint8_t *data) {
	int i, j;
	
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; // Command mode
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(x & 0xF);
		spi_send_recv(0x10 | ((x >> 4) & 0xF));
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
		
		for(j = 0; j < 128; j++)
			spi_send_recv(~data[i*32 + j]);
	}
}
/**
 * @brief Updates the display based on an array containing
 * 512 unsigned 8-bit integers.
 * 
 * @param data The array
 */
void updateDisplay(const uint8_t *data){
	DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; // Set the display to command mode
	spi_send_recv(0x22); // Tell starting and last page
	spi_send_recv(0); // Starting page
	spi_send_recv(3); // Ending page
	spi_send_recv(0x21); // ??
	spi_send_recv(0x00); // ??
	spi_send_recv(127); // ??
	spi_send_recv(0x20); // Horizontal mode
	spi_send_recv(0x00); // ??


	// Iterate through the data array and turn on pixels
	int i;
	DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK; // Set to display mode (Read maybe)
	for(i = 0; i < 512; i ++){
		spi_send_recv(data[i]); // Turn on pixels
	}
}

void draw_image(int x, const uint8_t *data){
    DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; // Command mode
	spi_send_recv(0x22);
	spi_send_recv(0);
    spi_send_recv(3);
    spi_send_recv(0x21);
    spi_send_recv(0x00);
    spi_send_recv(127);

    spi_send_recv(0x20); // Ändra till horisontell istället för page-adressing mode
    spi_send_recv(0x00);

    int j;
	DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
    for(j = 0; j < 512; j++){
        
        spi_send_recv(data[j]);
    }
}

void set_on_all(){
    int i;
    for(i = 0; i < 512; i ++){
        screen[i] = 255;
    }
}

void display_update() {
	int i, j, k;
	int c;
	for(i = 0; i < 2; i++) { // "Fyra" rader, ett tal per rad, med varje rad innehåller ett 8-bitars tal
							 // Alltså täcker en iteration 8 rader på displayen
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; //Command mode
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10); // Offset
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK; // Display mode
		
			
		for(k = 0; k < 64; k++) // Förskjutning i x-led
			spi_send_recv(0x1); // Bestämmer värdet i varje tal
	}
}

void display_white(){ //Gör allt vitt
	int i, j;
	
	for(i = 0; i < 4; i ++){
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; //Command mode
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10); // Offset

		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK; // Display mode

		for( j = 0; j < 128; j ++){
			spi_send_recv(0xFF);
		}

	}

}

void set_pixel(int x, int y, int value){
	
	if(x > 127 || x < 0 || y > 31 || y < 0 ){
		return;
	}
	// First we need to find the right index group
	int ytemp = y/8; 
	int index = ytemp *128;
	index += x;
	// If 0 <= y >= 7 --> ytemp =  0 --> index = 0 * 128 + x = x (0 <= index >= 127) group 1
	// If 8 <= y >= 15 --> ytemp = 1 --> index = 1 * 128 + x = 128 + x (128 <= index >= 255) group 2
	// If 16 <= y >= 23 --> ytemp = 2 --> index = 2 * 128 + x = 256 + x (256 <= index >= 383) group 3
	// If 24 <= y >= 31 --> ytemp = 3 --> index = 3 * 128 + x = 384 + x (384 <= index >= 255) group 4

	//We now have the right main index group
	//Now we need to find the right index for the subgroup
	int ytemp2 = y % 8;  // Tells which pixel in the index to change since every index contains 8 pixels.
    int mask = 1;
    mask = mask << ytemp2; // If ytemp2 = 3 (fourth pixel), mask = 0000 1000

	if(!value){ // If we want to turn off
        screen[index] &= !mask; // xxxx xxxx && 1111 0111 = xxxx 0xxx
	}else{ // If we want to turn on
	    screen[index] |= mask; // xxxx xxxx || 0000 1000 = xxxx 1xxx
	}
}

void display_clear(){ // Gör allt svart
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK; //Command mode
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10); // Offset
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK; // Display mode
		
			
		for(k = 0; k < 128; k++)
			spi_send_recv(0x0);
	
	}
}
/**
 * @brief Resets all elements in the array
 * 
 * @param data 
 */
void resetDisplay(uint8_t *data){
	int i = 0;
	for(i= 0; i < 512; i ++){
		data[i] = 0;
	}
}

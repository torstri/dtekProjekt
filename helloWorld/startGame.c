#include <pic32mx.h>
#include <stdint.h>

void draw_start(uint8_t *data){

}

void draw_arena(uint8_t *data){

    // Left upper corner = (20, 5)
    // Right upper corner = (108, 5)
    // Left lower corner = (20, 27)
    // Right lower corner = (108, 27)

    // Draw floor and roof
    int x = 20;
    for(x = 20; x <= 108; x++){
        set_pixel(x, 5); // Draws roof
        set_pixel(x,27); // Draws floor
    }
    //Draw sides
    int y = 5;
    for(y = 5; y <= 27; y++){
        set_pixel(108,y); // Right side
        set_pixel(20, y); // Left side
    }
}
#include <pic32mx.h>
#include <stdint.h>

void draw_arena(uint8_t *data){

    // Roof left = (0, 0)
    // Roof right = (127, 0)
    // Floor left = (0, 31)
    // Floor right = (127, 31)

    // Draw floor and roof
    int x;
    for(x = 0; x < 128; x++){
        set_pixel(x, 0); // Draws roof
        set_pixel(x,31); // Draws floor
    }
    //Draw sides
    int y;
    for(y = 0; y < 32; y++){
        set_pixel(0, y); // Left side
        set_pixel(127,y); // Right side
    }
}

void draw_sliders(uint8_t *data){
    // Left slider
   setXPosLeft(16);
   setYPosLeft(9);
   setXPosRight(112);
   setYPosRight(9);
   drawSliders();
}

/**
 * @brief Draws the starting point for the game
 * arena and sliders
 * 
 * @param data 
 */
void draw_start(uint8_t *data){
    draw_arena(data);
    draw_sliders(data);

}
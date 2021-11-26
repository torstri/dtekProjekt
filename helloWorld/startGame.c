#include <pic32mx.h>
#include <stdint.h>



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
    draw_arena();
    draw_sliders(data);
    initBall();
}
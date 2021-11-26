#include <pic32mx.h>
#include <stdint.h>

struct ballElement{
    int xPos, yPos;
    int xSpeed, ySpeed;
    int width;
    int length;
};

struct sliderElement{
    int xPos, yPos;
    int length;
};

struct ballElement ball;
struct sliderElement leftSlider, rightSlider;

void ballInit(){
    ball.xPos = 16;
    ball.yPos = 9;
    ball.ySpeed = 0;
    ball.xSpeed = 1;
    ball.width = 1;
    ball.length = 1;

}

void sliderInit(){
    leftSlider.xPos = 64;
    leftSlider.yPos = 16;
    leftSlider.length = 13;

    rightSlider.xPos = 112;
    rightSlider.yPos = 9;
    rightSlider.length = 13;


}

void drawBall(){
    int i,j;
    int ytemp = ball.yPos;
    
    for(i = 2; i > 0; i --){

        int xtemp = ball.xPos;

        for(j = 2; j > 0; j --){
            set_pixel(xtemp, ytemp);
            xtemp++;
        }
        ytemp ++;
    }
}

void drawSliders(){

    int i = 0;

    while(i < leftSlider.length){
        set_pixel(leftSlider.xPos, leftSlider.yPos + i);
        set_pixel(rightSlider.xPos, rightSlider.yPos + i);
        i ++;
    }

}

void draw_arena(){

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

start_game(){
    sliderInit();
    ballInit();

    draw_arena();
    drawBall();
    drawSliders();
}
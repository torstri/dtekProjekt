#include <pic32mx.h>
#include <stdint.h>

int xPosLeft; // Left point
int yPosLeft; // Upper point of slider
int xPosRight;
int yPosRight;
const int height = 13;
const int width = 2;

int getXPosLeft(){
    return xPosLeft;
}

int getXPosRight(){
    return xPosRight;
}

void setXPosLeft(int x){
    xPosLeft = x;
}

void setXPosRight(int x){
    xPosRight = x;
}

int getYPosLeft(){
    return yPosLeft;
}

int getYPosRight(){
    return yPosRight;
}

void setYPosLeft(int y){
    yPosLeft = y;
}

void setYPosRight(int y){
    yPosRight = y;
}

/**
 * @brief Draws the sliders
 * 
 */
void drawSliders(){
    int yLeft = yPosLeft;
    int yRight = yPosRight;
    int i; // Length of slider
    for(i = height; i > 0; i --){
        set_pixel(xPosLeft,yLeft);
        set_pixel(xPosRight,yRight);
        yLeft ++;
        yRight ++;
    }
}


#include <pic32mx.h>
#include <stdint.h>

int xPos;
int yPos; // Middle of slider

int getXPos(){
    return xPos;
}

void setXPos(int x){
    xPos = x;
}

int getYPos(){
    return yPos;
}

void setYPos(int y){
    yPos = y;
}




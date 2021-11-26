#include <pic32mx.h>
#include <stdint.h>

int xPos;
int yPos;
int xSpeed;
int ySpeed;

void setXPos(int x){
    xPos = x;
}

void setYPos(int y){
    yPos = y;
}

int getXPos(){
    return xPos;
}

int getYPos(){
    return yPos;
}

void moveX(){
    if(xSpeed){
        xPos ++;
    }
    else if(xSpeed < 0){
        xPos --;
    }
}

void moveY(){
    if(ySpeed){
        yPos ++;
    }else if (ySpeed < 0){
        yPos --;
    }
}



void initBall(){
    xPos = 64;
    yPos = 16;
    ySpeed = 0;
    xSpeed = 1;
    drawBall();
}
#include <pic32mx.h>
#include <stdint.h>

/**
 * @brief Keeps track of ball x and y position,
 * length, width and speed in x and y direction
 * 
 */
struct ballElement{
    int xPos, yPos;
    int xSpeed, ySpeed;
    int width;
    int length;
};

/**
 * @brief Keeps track of slider length and 
 * x and y position
 * 
 */
struct sliderElement{
    int xPos, yPos;
    int length;
};

struct ballElement ball; // Create ball element
struct sliderElement leftSlider, rightSlider; // Create left and right sliders

/**
 * @brief Initialize the ball's x and y position, speed,
 * width and length
 * 
 */
void ballInit(){
    // Start at (64,16)
    ball.xPos = 64;
    ball.yPos = 16;
    //Travel horizontally
    ball.xSpeed = 1;
    ball.ySpeed = 0;
    // Set size to 2 by 2 pixels
    ball.width = 2;
    ball.length = 2;

}

/**
 * @brief Initialize sliders' x and y position,
 * and length
 * 
 */
void sliderInit(){
    //Start left slider at (10,9)
    leftSlider.xPos = 10;
    leftSlider.yPos = 9;
    leftSlider.length = 13;
    // Start right slider at (120,9)
    rightSlider.xPos = 120;
    rightSlider.yPos = 9;
    rightSlider.length = 13;


}

/**
 * @brief Draws the ball at current position
 * 
 */
void drawBall(int value){
    int i,j;
    int ytemp = ball.yPos;
    
    for(i = ball.length; i > 0; i --){

        int xtemp = ball.xPos;

        for(j = ball.width; j > 0; j --){
            set_pixel(xtemp, ytemp, value);
            xtemp ++;
        }
        ytemp ++;
    }
}

void drawSliders(int value){

    int i = 0;

    while(i < leftSlider.length){
        set_pixel(leftSlider.xPos, leftSlider.yPos + i, value);
        set_pixel(rightSlider.xPos, rightSlider.yPos + i, value);
        i ++;
    }

}

void drawArena(){

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

/**
 * @brief Moves the ball around the arena
 * 
 */
void moveBall(){
    //Checks if the ball has hit a slider
    if(samePosition(ball, leftSlider) || samePosition(ball, rightSlider)){
        ball.xSpeed = !ball.xSpeed;
        ball.ySpeed = !ball.ySpeed;
    }


    drawBall(0);
    ball.xPos += ball.xSpeed;
    ball.yPos += ball.ySpeed;
    drawBall(1);
}

/**
 * @brief Checks if ball has hit a slider
 * 
 * @param boll 
 * @param slider 
 * @return int 
 */
int samePosition(struct ballElement boll, struct sliderElement slider){
    int i, j, k;
    int xTempBall = boll.xPos;
    int yTempBall = boll.yPos;
    int xTempSlider = slider.xPos;
    int yTempSlider = slider.yPos;

    //Iterate through ball length
    for(j = boll.length; j >  0 ; j -- ){
        // Iterate through ball width
        for(k = boll.width; k > 0 ; k --){

            // Checks if the corner (xTempBall, yTempBall) of the ball has hit the slider
            for(i = slider.length; i > 0; i --){
                
                if(xTempBall == xTempSlider && yTempBall == yTempSlider){
                
                    return 1;
                }
                // Increment yPos of slider
                yTempSlider ++;
            }
            // Increment xPos of ball
            xTempBall ++;
        }
        // Increment yPos of ball
        yTempBall ++;
    }
    
    return 0;
}

start_game(){
    sliderInit();
    ballInit();

    drawArena();
    drawBall(1);
    drawSliders(1);

}
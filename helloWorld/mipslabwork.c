/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

int tickCounter = 0;
int timeoutCounter = 0;


/* Lab-specific initialization goes here */
void labinit( void )
{
  // 1 means input, 0 means output
  volatile int* trisE = (volatile int*) 0xbf886100;
  *trisE |= 0xFFFFFF00;
  TRISD |= 0xFE0;
  T2CON = T2CON | 0x8000; //Set the mode to on
  T2CON = T2CON | 0x70;  //Set prescale to 256, bits 4-6 = 111
  PR2 = 0x145A;  // Set the period to 31 250, so the timer timesout ten times per second

  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{

  volatile int* portE = (volatile int*) 0xbf886110;
  /**
   * The timer has a frequency of 80 MHz, this means by default 80 million timeouts per second.
   * To have 10 timeouts per second we need to set the PR2 register too 8 million which is not possible since
   * PR2 is a 16 bit register with max value 65 535. Hence we need to prescale. With a prescale of 256
   * we get that PR2 = 8 000 000 / 256 = 31 250, which is doable.
   * 31 250 = 0b 0111  1010 0001 0010
   * 256 = 111 in bits 6-4 in T2CON
   **/
  int flag = IFS(0)&0x100;
  flag >>= 8;

  if(flag){ // Check if the timer has timed out
    //delay( 1000 );

    timeoutCounter ++; // Increment timeout counter

      if(!(timeoutCounter % 10)){
        moveBall();
        updateDisplay();


        //*portE = tickCounter;
        tickCounter ++;

        timeoutCounter == 0;

      }
      IFS(0) &= 0xFEFF; // Set the intercept flag to zero
  }

}

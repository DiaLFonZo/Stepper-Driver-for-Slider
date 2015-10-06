// Needed Library
#include "UTFT.h"
#include "UTouch.h"
//#include "segment18_XXL.c"
#include <Stepper.h>

// Define my stepmotor 200 pulses per turn on pins 3 & 2
Stepper myStepper(200, 3, 2);

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];
//extern uint8_t segment18_XXL[];

// Define my LCD and Touch
UTFT    myGLCD(ITDB24, A5,A4,A3,A2);
UTouch  myTouch(A1,10,A0,8,9);

int x, y;       //Declaring X & Y positions
int Sint=1;     //declaring integer
char Schar[10]; //declaring character array
String str;     //declaring string

void drawButtons(){
//======Draw the first row of buttons======//
    myGLCD.setColor(255, 255, 255);
    myGLCD.fillRoundRect(5, 5, 55, 55);
    myGLCD.fillRoundRect(60, 5, 110, 55);    
    myGLCD.fillRoundRect(115, 5, 205, 55);
    myGLCD.fillRoundRect(210, 5, 260, 55);
    myGLCD.fillRoundRect(265, 5, 315, 55);

//======Draw the Jog buttons======//
    myGLCD.fillRoundRect(5, 180, 155, 235); //Jog Square Left
    myGLCD.fillRoundRect(165, 180, 315, 235); //Jog Square Right 
    
    myGLCD.setColor(0, 0, 0); 
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.setFont(SmallFont);
    refresh();
//    myGLCD.print("<<", 20, 150);
//    myGLCD.print(">>", 200, 190);
  
    myGLCD.setFont(BigFont);
    myGLCD.print("<1", 10, 23);
    myGLCD.print("<5", 70, 23);
    myGLCD.print("5>", 220, 23);
    myGLCD.print("1>", 280, 23);
}
// Draw a red frame while a button is touched
void waitForIt(int x1, int y1, int x2, int y2){
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}
void setup()
{  
  str=String(Sint); //converting integer into a string
  str.toCharArray(Schar,10); //passing the value of the string to the character array
  myGLCD.InitLCD(LANDSCAPE); 
  myGLCD.clrScr();
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);
  drawButtons();
}
void refresh()
{
    if (Sint>9){
      Sint=9;
    }
    if (Sint<1){
      Sint=1;
    }
    str=String(Sint); //converting integer into a string
    str.toCharArray(Schar,2); //passing the value of the string to the character array
    myGLCD.setColor(0, 0, 0); 
    myGLCD.setBackColor(255, 255, 255);
    myGLCD.setFont(SevenSegNumFont);
    myGLCD.print(Schar, CENTER, 6);
}

void loop(){
//    myStepper.setSpeed(1000);
//    myStepper.step(200);
  while (true){
   
    if (myTouch.dataAvailable()){
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
        if ((y>=180) && (y<=235)){ 
          if ((x>=5) && (x<=155)){  
            waitForIt(5, 180, 155, 235);
            refresh();
          }  
        }   
        if ((y>=5) && (y<=55)){ 
          if ((x>=5) && (x<=55)){  
            Sint=(Sint-1);
            waitForIt(5, 5, 55, 55);
            refresh();
          }  
          if ((x>=60) && (x<=110)){  
            Sint=(Sint-5);
            waitForIt(60, 5, 110, 55);
            refresh();
          } 
          if ((x>=210) && (x<=260)){  
            Sint=(Sint+5);
            waitForIt(210, 5, 260, 55);
            refresh();
          } 
          if ((x>=265) && (x<=315)){  
            Sint=(Sint+1);
            waitForIt(265, 5, 315, 55);
            refresh();
          }          
        }
    }
  }
}







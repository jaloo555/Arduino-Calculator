#include <Wire.h>
#include <LiquidCrystal.h>
#include "Adafruit_Trellis.h"

// Initialize lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// I have no idea
#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE LATCHING

// Instantiate the object Adafruit_Trellis() with variable matrix 0
Adafruit_Trellis matrix0 = Adafruit_Trellis();

// Create a variable "trellis" of type Adafruit_TrellisSet & set it to &matrix0 (Adafruit_Trellis();)
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);

// variable saying that i only have 1 trellis board
#define NUMTRELLIS 1

// variable saying how many keys i have in the trellis board
#define numKeys (NUMTRELLIS * 16)

// define all the keys
char keys[] = {'7', '8', '9', 'C', '4', '5', '6', '+', '1', '2', '3', '-', '0', ' ', '.', '='};

// Variables needed for the calc
long totalNumber = 0, oldTotal = 0;
char lastOperation, currentOperation;

void setup()
{
  Serial.begin(9600);

  /* Start up the trellis board, i guess .begin is a function in the library that allocates
     the trellis board to a certain address on the microcontroller, in this case, hex: 70
  */
  trellis.begin(0x70);

  // Same for the liquid crystal library
  lcd.begin(16, 2);

  // Clear display to prevent clogging
  lcd.clear();

  clearTrellis();

  initialGreeting();

  lcd.print("Calculator");

  delay(1000);

  lcd.clear();

}
void clearTrellis()
{
  for (int i = 0; i < numKeys; i++)
  {
    trellis.clrLED(i);
  }
  trellis.writeDisplay();
}
void loop()
{
  delay(30);

  // Set invisible cursor
  lcd.setCursor(0, 0);

  if (trellis.readSwitches())
  {
    for (uint8_t i = 0; i < numKeys; i++)
    {
      if (trellis.justPressed(i))
      {
        delay(30);
        valueForKey(i);
        trellis.setLED(i);
        trellis.writeDisplay();
        delay(200);
        trellis.clrLED(i);
        trellis.writeDisplay();
      }
    }
  }
}

void clearStuff() {
  totalNumber = 0;
  oldTotal = 0;
  lcd.clear();
}


// make another function that check which is pressed
// set lcd print & do operations here
void valueForKey(int i) {
  switch (keys[i]) {
    case '9':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 9);
      lcd.print(totalNumber);
      break;
    case '8':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 8);
      lcd.print(totalNumber);
      break;
    case '7':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 7);
      lcd.print(totalNumber);
      break;
    case '6':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 6);
      lcd.print(totalNumber);
      totalNumber = totalNumber;
      break;
    case '5':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 5);
      lcd.print(totalNumber);
      break;
    case '4':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 4);
      lcd.print(totalNumber);
      break;
    case '3':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 3);
      lcd.print(totalNumber);
      break;
    case '2':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 2);
      lcd.print(totalNumber);
      break;
    case '1':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 1);
      lcd.print(totalNumber);
      break;
    case '0':
      if (lastOperation == '=') {
        clearStuff();
        lastOperation ='n';
      }
      totalNumber = ((totalNumber * 10) + 0);
      lcd.print(totalNumber);

      break;
    case 'C':
      totalNumber = 0;
      oldTotal = 0;
      lcd.clear();
      lastOperation = 'C';
      break;
    
    
    case '+':
      if (lastOperation == '=')
      {
        lastOperation = '+';
        Serial.println(oldTotal);
        //clear number
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print(oldTotal);
        totalNumber = 0;
      }
      else if (lastOperation == '+') {
        lastOperation = '+';
        lcd.clear();
        oldTotal = totalNumber + oldTotal;
        Serial.println(oldTotal);
        lcd.clear();
        lcd.print(0);
        totalNumber = 0;
        lcd.setCursor(0, 1);
        lcd.print(oldTotal);
      }
      else if (lastOperation == '-') {
        lastOperation = '+';
        lcd.clear();
        oldTotal = totalNumber - oldTotal;
        Serial.println(oldTotal);
        lcd.clear();
        lcd.print(oldTotal);
        totalNumber = 0;
        lcd.setCursor(0, 1);
        lcd.print(oldTotal);
      }
      else
      {
        lastOperation = '+';
        oldTotal = totalNumber;
        //clear number
        lcd.clear();
        lcd.print("+");
        totalNumber = 0;
      }
      break;

      // Problem here
    
    
    case '-':
      if (lastOperation == '=')
      {
        lastOperation = '-';
        Serial.println(oldTotal);
        //clear number
        lcd.clear();
        lcd.setCursor(0, 1);
        totalNumber = 0;
      }
      else if (lastOperation == '-') {
        lastOperation = '-';
        lcd.clear();
        oldTotal  = oldTotal - totalNumber;
        lcd.clear();
        //lcd.print(oldTotal);
        totalNumber = 0;
        lcd.setCursor(0, 1);
        lcd.print(oldTotal);
      }
      else if (lastOperation == '+') {
        lastOperation = '-';
        lcd.clear();
        oldTotal = oldTotal + totalNumber;
        Serial.println(oldTotal);
        lcd.clear();
        //lcd.print(oldTotal);
        totalNumber = 0;
        lcd.setCursor(0, 1);
        lcd.print(oldTotal);
      }
      else
      {
        lastOperation = '-';
        oldTotal = totalNumber;
        //clear number
        lcd.clear();
        lcd.print("-");
        totalNumber = 0;
      }
      break;
      
    case '=':
      if (lastOperation == '+')
      {
        oldTotal = totalNumber + oldTotal;
        Serial.println(oldTotal);
        lcd.clear();
        lcd.print(oldTotal);
        totalNumber = 0;
        lcd.setCursor(0, 1);
      }
      else
      {
        oldTotal  = oldTotal - totalNumber;
        lcd.clear();
        lcd.print(oldTotal);
        totalNumber = 0;
        lcd.setCursor(0, 1);
      }
      

      lastOperation = '=';

      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}

void initialGreeting()
{
  // ADDITION
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 0 || i == 3 || i == 12 || i == 15)
    {
      //do nothing
    }
    else
    {
      trellis.setLED(i);
      trellis.writeDisplay();
      delay(50);
    }
  }
  delay(1000);
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 0 || i == 3 || i == 12 || i == 15)
    {
      //do nothing
    }
    else
    {
      trellis.clrLED(i);
      trellis.writeDisplay();
      delay(50);
    }
  }
  // SUBTRACTION
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 0 || i == 1 || i == 2 || i == 3 || i == 12 || i == 13 || i == 14 || i == 15)
    {
      //do nothing
    }
    else
    {
      trellis.setLED(i);
      trellis.writeDisplay();
      delay(50);
    }
  }
  delay(1000);
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 0 || i == 1 || i == 2 || i == 3 || i == 12 || i == 13 || i == 14 || i == 15)
    {
      //do nothing
    }
    else
    {
      trellis.clrLED(i);
      trellis.writeDisplay();
      delay(50);
    }
  }
  // MULTIPLICATION
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 0 || i == 5 || i == 10 || i == 15 || i == 3 || i == 6 || i == 9 || i == 12)
    {
      trellis.setLED(i);
      trellis.writeDisplay();
      delay(50);
    }
    else
    {
    }
  }
  delay(1000);
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 0 || i == 5 || i == 10 || i == 15 || i == 3 || i == 6 || i == 9 || i == 12)
    {
      trellis.clrLED(i);
      trellis.writeDisplay();
      delay(50);
    }
    else
    {
    }
  }
  // DIVISION
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 3 || i == 6 || i == 9 || i == 12)
    {
      trellis.setLED(i);
      trellis.writeDisplay();
      delay(50);
    }
    else
    {
    }
  }
  delay(1000);
  for (uint8_t i = 0; i < numKeys; i++) {
    if (i == 3 || i == 6 || i == 9 || i == 12)
    {
      trellis.clrLED(i);
      trellis.writeDisplay();
      delay(50);
    }
    else
    {
    }
  }

}


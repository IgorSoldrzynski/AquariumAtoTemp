/* AtoTempRelay v.0.1
   Aquarium Auto Top Off, Temperature Control and Relay with Light Sensor.
   Created: 19.12.2019 
   Author: Igor Sołdrzyński <igor.soldrzynski@gmail.com> */
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Ato.h"
#include "Relay.h"
#include "Button.h"
#include "TempControl.h"

// ATO settings:
#define atoPinLow 8
#define atoPinMid 9
#define atoPinHigh 10
#define atoMaxDur 3 //maximum work duration in minutes
#define atoMinBreak 3 //minimum break between cycles in minutes

// LCD settings:
#define lcdRs 12 //  * LCD RS pin to digital pin 12
#define lcdEn 11 //  * LCD Enable pin to digital pin 11
#define lcdD4 5 //  * LCD D4 pin to digital pin 5
#define lcdD5 4 //  * LCD D5 pin to digital pin 4
#define lcdD6 3 //  * LCD D6 pin to digital pin 3
#define lcdD7 2 //  * LCD D7 pin to digital pin 2
#define lcdRefTime 300 // LCD refresh rate (in miliseconds)
#define lcdClearTime 10000 // LCD refresh rate (in miliseconds)
 
// Temperature settings:
#define tempSensPin 6 //DS18B20 temperature sensor pin
#define tarTemp 25.0 // target temperature
#define flucTemp 0.5 // teperature fluctuation

//Relays pins:
#define relPumpPin A2
#define relHeatPin A1
#define relCoolPin A4
#define relSkimmPin A3

//Button pin:
#define butPin 7

//Objects initialization:
Relay relPump(relPumpPin); // Pump relay
Relay relHeat(relHeatPin); // Heater relay
Relay relCool(relCoolPin); // Fans relay
Relay relSkimm(relSkimmPin); // Protein skimmer relay
Button button(butPin); // button
Ato ato(atoPinLow, atoPinMid, atoPinHigh, atoMaxDur, atoMinBreak, &relPump, &relSkimm); // ato
LiquidCrystal lcd(lcdRs, lcdEn, lcdD4, lcdD5, lcdD6, lcdD7); // LCD 16x2
OneWire bus(tempSensPin); // DS18B20 temperature sensor bus for TempControl
TempControl temp(&bus, tarTemp, flucTemp, &relHeat, &relCool); // Temperature Control

//char arrays for printing on LCD:
char line0[17] = "QQQ.QQQC  ATO: Q";;
char line1[17] = "* ZZZZZ  PUMP: Z";
//unsigned long lcdUpTime; // last time when lcd was updated


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // start of DS18B20 temperature sensor:
  temp.begin();
  Serial.begin(9600);
  
  // start of ATO:
  ato.init();

  // button init:
  button.init(); 

  // LCD chars constant values on some positions:
  line0[6] = (char)222; // degree symbol


  //lcdUpTime = 0;
  //Serial.begin(9600);
}

void loop() {
  
  ato.update();

  line0[15] = ato.getState(); // H/L/W/O, errors, work or ok - information
  
  // 0/1 is pump working:
  if(relPump.getState()) { line1[15] = '1'; }
  else { line1[15] = '0'; }  

  // niech temp zwraca tablicę char[4] (5) z temperaturą
  // tmp:
  line0[0] = 'h'; // heating/cooling/@-64
  line0[1] = line0[2] = line0[4] = line0[5] = 'X';
  

  lcdUpdate();
}

// Prints buffored char arrays on LCD. Makes sure to not update to often.
void lcdUpdate() {
  static unsigned long lcdUpTime = 0;
  unsigned long now = millis();
  if(now-lcdUpTime > lcdRefTime) {
    if(now-lcdUpTime > lcdClearTime) {
      lcd.clear();
    }
    // blinking * :
    if(line1[0] == '*') {
      line1[0] = ' ';
    }
    else {
      line1[0] = '*';
    }
    
    lcd.setCursor(0, 0);
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print(line1);
    lcdUpTime = now;
  }
}

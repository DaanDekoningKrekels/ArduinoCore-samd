// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

/* Deze code kan gebruikt worden om de I2C verbinding van de SAMDaaNo21 te testen.
 * Sluit een oscilloscoop aan en zet het trigger type op I2C 
 * of gebruik een andere MCU om de berichten te ontvangen. 
 * Het signaal is aanwezig op de S4CDA en S4SCL pinnen. 
 * Een pull-up weerstand is aanwezig aan de onderkant van de pcb.
 */


#include <Wire.h>

#define RECEIVER 0x55

void setup() {
  SerialUSB.begin(9600);  // open the serial port at 9600 bps:
  SerialUSB.println("Niet opgestart");

  Wire.begin();  // join i2c bus (address optional for master)

  SerialUSB.println("Opgestart");
}

byte x = 0;

void loop() {
  Wire.beginTransmission(0x55);  // transmit to device
  Wire.write("x is ");           // sends five bytes
  Wire.write(x);                 // sends one byte
  Wire.endTransmission();        // stop transmitting

  SerialUSB.println("Verstuurd: " + (String)x);

  x++;
  delay(500);
}

/* SAMDaaNo21 UART test
 * Deze code kan gebruikt worden om alle toegankelijke UART interfaces
 * die de SAMDaaNo21 kan aanbeiden te testen.
 * Iedere kwart seconde zal er naat een andere UART een
 * bericht worden verzonden.
 * `SerialUSB` is een alias van `Serial`.
 * `SerialLoRa` is een alias van `Serial2`.
 *  Je kan in principe kiezen welke je gebruikt of ze door elkaar gebruiken.
 */


void setup() {
  SerialUSB.begin(9600);    // open the serial port at 9600 bps:
  Serial1.begin(9600);      // open the serial port at 9600 bps:
  SerialLoRa.begin(9600);   // open the serial port at 9600 bps:
  Serial3.begin(9600);      // open the serial port at 9600 bps:
  while (!SerialUSB) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  SerialUSB.println("opgestart");
}

void loop() {
  // Print iedere seconde naar de UART poorten, één voor één.
  // Let op dat de buffer niet vol geraakt, dan stop het uitvoeren.
  for (byte i = 0; i < 100; i++) {
    SerialUSB.println("SerialUSB: "+(String)i);
    delay(250);
    Serial1.println("Serial1: "+(String)i);
    delay(250);
    SerialLoRa.println("SerialLoRa: "+(String)i);
    delay(250);
    Serial3.println("Serial3: "+(String)i);
    delay(250);
  }
}
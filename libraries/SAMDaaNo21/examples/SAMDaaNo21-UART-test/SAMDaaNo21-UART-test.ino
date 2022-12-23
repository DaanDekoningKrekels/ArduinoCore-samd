
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
  // Print iedere seconde naar de UART poorten, een voor een.
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
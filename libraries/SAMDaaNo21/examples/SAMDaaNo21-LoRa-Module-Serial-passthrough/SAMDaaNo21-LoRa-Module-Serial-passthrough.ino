/* SAMDaaNo21 LoRa Module Serial Passthrough
 * Deze code kan gebruikt worden om via de computer
 * commando's te sturen naar de RN2483 LoRaWAN module.
 * Alles dat `SerialUSB` ontvangt wordt doorgestuurd naar `SerialLoRa`.
 * Alles dat `SerialLoRa` ontvangt wordt doorgestuurd naar `SerialUSB`.
 */ 


void setup() {
  pinMode(S2RX, INPUT);
  SerialUSB.begin(9600);    // open the serial port at 9600 bps:
  SerialLoRa.begin(57600);   // open the serial port at 57600 bps:
  while (!SerialUSB) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  SerialUSB.println("opgestart");
}
void loop() {
  if (SerialLoRa.available()) {
    SerialUSB.write(SerialLoRa.read());
  }
  if (SerialUSB.available()) {
    SerialLoRa.write(SerialUSB.read());
  }
}
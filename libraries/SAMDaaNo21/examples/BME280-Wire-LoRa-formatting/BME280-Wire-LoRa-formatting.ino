/* BME280 Wire LoRa formatting
 * Deze code toont de werking van een BME280 
 * en zet de temperatuur, luchtvochtigheid en luchtdruk om naar een array
 * om gemakkelijk door te sturen via LoRaWAN. 
 *
 * Bibliotheek https://github.com/adafruit/Adafruit_BME280_Library
 */


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;  // I2C

#define DELAY_TIME 2000 // om de 2 seconden sturen

/*
  Vraag temp, pressure en humidity op van BME 
  en format als 5 bytes in een array meegegeven als parameter.

  | Byte nr | Name            | Sensor range     | On Node MCU | Reformat |
  | ------- | --------------- | ---------------- | ----------- | -------- |
  | 0-1     | Temp            | -40 tot 85°C     | +40         | -40      | - BME280
  | 2-3     | Pressure        | 300 tot 1100 hPa | n/a         | n/a      | - BME280
  | 4       | Humidity        | 0 tot 100%       | n/a         | n/a      | - BME280
  | -       | -               | -                | -           | -        |
  | 4-5     | Wind Speed      | 0.0 tot 32.7 m/s | *10         | /10      | - niet nu
  | 6-7     | Ground Moisture | 0 tot 1023       | n/a         | n/a      | - niet nu
*/
void getDataFormattedBME(byte (&BMEdata)[5]) {

  // minimale temperatuur van -40 erbij tellen en komma compenseren
  int temperature = int((bme.readTemperature() + 40) * 100);  
  int pressure = int(round(bme.readPressure() / 100));
  byte humidity = round(bme.readHumidity());

  // Weergeven van deug informatie, 
  // de waarden decimaal en hexadecimaal naar SerialUSB
  SerialUSB.println("==Data in functie (HEX & DEC)==");
  
  SerialUSB.print("temperature: ");
  SerialUSB.println(temperature, HEX);
  SerialUSB.println(temperature, DEC);
  SerialUSB.print("pres1: ");
  SerialUSB.println(pressure, HEX);
  SerialUSB.println(pressure, DEC);
  SerialUSB.print("hum: ");
  SerialUSB.println(humidity, HEX);
  SerialUSB.println(humidity, DEC);

  // Temperatuur int opsplitsen in twee bytes
  BMEdata[0] = highByte(temperature);
  BMEdata[1] = lowByte(temperature);

  // Druk int opsplitsen in twee bytes
  BMEdata[2] = highByte(pressure);
  BMEdata[3] = lowByte(pressure);
  
  BMEdata[4] = humidity;
}

void setup() {
  SerialUSB.begin(9600); // Start SerialUSB op9600
  SerialUSB.println(F("BME280 test"));

  unsigned status;

  status = bme.begin(0x76, &Wire);  // Adres van BME en wire bibliotheek

  if (!status) {
    SerialUSB.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    SerialUSB.print("SensorID was: 0x");
    SerialUSB.println(bme.sensorID(), 16);
    while (1) delay(10);
  }

  SerialUSB.println("-- Default Test --");

  SerialUSB.println();
}

void loop() {
  byte BMEdata[5];               // Lege array om nog te laten vullen met metingen
  getDataFormattedBME(BMEdata);  // Array laten vullen

  SerialUSB.println("==Data in array (HEX)==");
  SerialUSB.print("0: ");
  SerialUSB.println(BMEdata[0], HEX);  // Temp 1
  SerialUSB.print("1: ");
  SerialUSB.println(BMEdata[1], HEX);  // Temp 2
  SerialUSB.print("2: ");
  SerialUSB.println(BMEdata[2], HEX);  // Press 1
  SerialUSB.print("3: ");
  SerialUSB.println(BMEdata[3], HEX);  // Press 2
  SerialUSB.print("4: ");
  SerialUSB.println(BMEdata[4], HEX);  // Hum
  delay(50);

  printValues();
  delay(DELAY_TIME);
}


void printValues() {
  SerialUSB.println("==Data via print (DEC)==");

  SerialUSB.print("Temperature = ");
  SerialUSB.print(bme.readTemperature());
  SerialUSB.println(" °C");

  SerialUSB.print("Pressure = ");

  SerialUSB.print(bme.readPressure() / 100.0F);
  SerialUSB.println(" hPa");

  SerialUSB.print("Approx. Altitude = ");
  SerialUSB.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  SerialUSB.println(" m");

  SerialUSB.print("Humidity = ");
  SerialUSB.print(bme.readHumidity());
  SerialUSB.println(" %");

  SerialUSB.println();
}

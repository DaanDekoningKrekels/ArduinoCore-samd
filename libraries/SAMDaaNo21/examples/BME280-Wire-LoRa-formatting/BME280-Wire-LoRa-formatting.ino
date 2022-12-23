/* Deze code toont de werking van een BME28 
 * en zet de temperatuur, luchtvochtigheid en luchtdruk om naar een array
 * om gemakkelijk door te sturen via LoRaWAN. 
 */


#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;  // I2C

unsigned long delayTime;


void getDataFormattedBME(byte (&BMEdata)[5]) {
  /*
    Vraag temp, pressure en humidity op van BME en format als 4 bytes in een array meegegeven als parameter.

    | Byte nr | Name            | Sensor range     | On Node MCU | Reformat |
    | ------- | --------------- | ---------------- | ----------- | -------- |
    | 0-1     | Temp            | -40 tot 85°C     | +40         | -40      | - BME280
    | 2-3     | Pressure        | 300 tot 1100 hPa | n/a         | n/a      | - BME280
    | 4       | Humidity        | 0 tot 100%       | n/a         | n/a      | - BME280
    | -       | -               | -                | -           | -        |
    | 4-5     | Wind Speed      | 0.0 tot 32.7 m/s | *10         | /10      | - niet nu
    | 6-7     | Ground Moisture | 0 tot 1023       | n/a         | n/a      | - niet nu
  */

  int temperature = int((bme.readTemperature() + 40) * 100);  // minimale temeratuur van -40 erbij tellen en komma compenseren
  int pressure = int(round(bme.readPressure() / 100));
  byte humidity = round(bme.readHumidity());

  Serial.println("==Data in functie (HEX & DEC)==");
  Serial.print("temperature: ");
  Serial.println(temperature, HEX);
  Serial.println(temperature, DEC);

  Serial.print("pres1: ");
  Serial.println(pressure, HEX);
  Serial.println(pressure, DEC);
  Serial.print("hum: ");
  Serial.println(humidity, HEX);
  Serial.println(humidity, DEC);

  // Temperatuur int opsplitsen in twee bytes
  BMEdata[0] = highByte(temperature);
  BMEdata[1] = lowByte(temperature);

  // Druk int opsplitsen in twee bytes
  BMEdata[2] = highByte(pressure);
  BMEdata[3] = lowByte(pressure);
  BMEdata[4] = humidity;
}

void setup() {
  Serial.println(F("BME280 test"));

  unsigned status;

  status = bme.begin(0x76, &Wire);  // Adres van BME en wire bibliotheek

  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x");
    Serial.println(bme.sensorID(), 16);
    while (1) delay(10);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();
}

void loop() {
  byte BMEdata[5];               // Lege array om nog te laten vullen met metingen
  getDataFormattedBME(BMEdata);  // Array laten vullen

  Serial.println("==Data in array (HEX)==");
  Serial.print("0: ");
  Serial.println(BMEdata[0], HEX);  // Temp 1
  Serial.print("1: ");
  Serial.println(BMEdata[1], HEX);  // Temp 2
  Serial.print("2: ");
  Serial.println(BMEdata[2], HEX);  // Press 1
  Serial.print("3: ");
  Serial.println(BMEdata[3], HEX);  // Press 2
  Serial.print("4: ");
  Serial.println(BMEdata[4], HEX);  // Hum
  delay(50);

  printValues();
  delay(delayTime);
}


void printValues() {
  Serial.println("==Data via print (DEC)==");

  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");

  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

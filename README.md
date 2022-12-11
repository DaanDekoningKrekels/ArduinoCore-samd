# FLWSB Arduino Core for SAMD21 CPU

This repository contains the source code and configuration files of the Arduino Core
for Atmel's SAMD21 processor (used on the Arduino/Genuino Zero, MKR1000 and MKRZero boards).


## SAMDaaNo21 toevoegen aan de Arduino IDE


Om de SAMDaaNo21 werkende te krijgen met een IDE zoals die van Arduino moeten we eerst een compatibele bootloader op de MCU hebben staan. Wij maken gebruik van de ATSAMD21G16B en spijtig genoeg zijn hier geen kant en klare bootloaders voor. Omdat we de printplaat zelf hebben ontworpen zijn er uiteraard ook geen volledig compatibele configuraties beschikbaar.

Het toevoegen voor ondersteuning verloopt in een aantal stappen:

- Bootloader aanpassen aan de [ATSAMD21G16B](https://www.microchip.com/en-us/product/ATSAMD21G16)
- Bootloader compileren
- Een Arduino variant toevoegen voor de SAMDaaNo21
  - Linker script aanpassen
  - OpenOCD script aanpassen
  - Pinout en functies definiëren

Bij deze stappen hebben we ons gebaseerd op de Arduino Zero. Deze heeft echter een ATSAMD21G18A, dat is een variant met meer geheugen.

Alle nodige broncode is te verkrijgen van de [ArduinoCore-samd](https://github.com/arduino/ArduinoCore-samd) GitHub repository. ([Onze fork](https://github.com/DaanDekoningKrekels/ArduinoCore-samd))

Belangrijke mappen en bestanden:

| Naam         | Beschrijving                                                 |
| ------------ | ------------------------------------------------------------ |
| bootloaders/ | Map met broncode voor alle type Arduino's.                   |
| variants/    | Map met broncode voor alle verschillende varianten van Arduino's om compatibel te zijn met de Arduino bibliotheken. |
| boards.txt   | Bestand met definities en instellingen voor Arduino borden weer te geven in de Arduino IDE onder `tools`-> `board: xxx` |


## Bronnen

Porting Arduino Zero to another samd21g variant: https://forum.arduino.cc/t/porting-arduino-zero-to-another-samd21g-variant/400138/3

https://www.instructables.com/Arduino-IDE-Creating-Custom-Boards/

https://hackaday.io/project/8007-hack/log/41354-docs-how-the-variant-system-works-on-arduino-zero-boards





## Installatie binnen de Arduino IDE

De onderstuning voor het FLWSB bord is nog niet op een toegankelijke manier te installeren. Je kan echter wel de stappen volgen onder [#Developing](#Developing) om het toe te voegen. 

## Bugs or Issues

If you find a bug you can submit an issue here on github:

https://github.com/DaanDekoningKrekels/ArduinoCore-samd/issues

Before posting a new issue, please check if the same problem has been already reported by someone else
to avoid duplicates.

## Contributions

Contributions are always welcome. The preferred way to receive code contribution is by submitting a 
Pull Request on github.

## Developing

1. Clone the [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API) repo to any convenient location:
   ```
   git clone https://github.com/arduino/ArduinoCore-API.git
   ```
1. Create an `<SKETCHBOOK>/hardware/arduino-git` folder, where `<SKETCHBOOK>` is the location of your
    Arduino sketchbook.
1. Change directories:
   ```
   cd <SKETCHBOOK>/hardware/arduino-git
   ```
1. Clone this repo:
   ```
   git clone https://github.com/DaanDekoningKrekels/ArduinoCore-samd.git samd
   ```
1. Change directories:
   ```
   cd samd/cores/arduino
   ```
1. Copy or symlink the `api` folder from the [ArduinoCore-API](https://github.com/arduino/ArduinoCore-API) repo:
   ```
   ln -s <ARDUINO_CORE_API>/api .
   ```
   where `<ARDUINO_CORE_API>` is the location where you've cloned the ArduinoCore-API repository to.
1. Restart the IDE.

## License and credits

This core has been developed by Arduino LLC in collaboration with Atmel.

```
  Copyright (c) 2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
```

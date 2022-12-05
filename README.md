# Arduino Core for SAMD21 CPU

This repository contains the source code and configuration files of the Arduino Core
for Atmel's SAMD21 processor (used on the Arduino/Genuino Zero, MKR1000 and MKRZero boards).



## SAMDaaNo21 Toevoegen



### Bootloader

Folder van de Arduino Zero `zero` gedupliceerd en hernoemd naar `samdaano21`.

#### Linker script

`bootloader_samd21x18.ld` -> `bootloader_samd21x16.ld `

Dit is het linker script. Daarin is enkel de memory mapping aangepast. De ATSAMD21x18 versie heeft 256kb flash en 32kb SRAM. De ATSAMD21x16 heeft 64kb flash en 8kb SRAM.

````
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x2000 /* First 8KB used by bootloader */
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00002000-0x0400 /* last 4 bytes used by bootloader to keep data between resets, but reserves 1024 bytes for sketches to have same possibility */
}
````

#### Makefile

`Makefile`

````
LD_SCRIPT=bootloader_samd21x16.ld
````

Naam naar nieuw bestand.

**Nog wat aanpasingen nodig.**

#### Board definitions

````cpp
#define STRING_PRODUCT "SAMDaaNo21"
[...]
#define BOOT_DOUBLE_TAP_ADDRESS           (0x20001FFCul) // 8kb ram - 4 bytes = 10x8188 0x1FFC
````

Belangrijk is hier dat het double tap adres anders is dan bij de Zero omdat we een keiner geheugen hebben in de G16.











### Arduino IDE ondersteuning















## Installation on Arduino IDE

This core is available as a package in the Arduino IDE cores manager.
Just open the "Boards Manager" and install the package called:

"Arduino SAMD Boards (32-bit ARM Cortex-M0+)"

## Support

There is a dedicated section of the Arduino Forum for general discussion and project assistance:

http://forum.arduino.cc/index.php?board=98.0

## Bugs or Issues

If you find a bug you can submit an issue here on github:

https://github.com/arduino/ArduinoCore-samd/issues

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
   git clone https://github.com/arduino/ArduinoCore-samd.git samd
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

## Hourly builds

This repository is under a Continuous Integration system that every hour checks if there are updates and
builds a release for testing (the so called "Hourly builds").

The hourly builds are available through Boards Manager. If you want to install them:
  1. Open the **Preferences** of the Arduino IDE.
  2. Add this URL `http://downloads.arduino.cc/Hourly/samd/package_samd-hourly-build_index.json` in the **Additional Boards Manager URLs** field, and click OK.
  3. Open the **Boards Manager** (menu Tools->Board->Board Manager...)
  4. Install **Arduino SAMD core - Hourly build**
  5. Select one of the boards under **SAMD Hourly build XX** in Tools->Board menu
  6. Compile/Upload as usual

If you already installed an hourly build and you want to update it with the latest:
  1. Open the **Boards Manager** (menu Tools->Board->Board Manager...)
  2. Remove **Arduino SAMD core - Hourly build**
  3. Install again **Arduino SAMD core - Hourly build**, the Board Manager will download the latest build replacing the old one.

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

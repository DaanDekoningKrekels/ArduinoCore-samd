# SAMDaaNo21 Bootloader

## Bootloader

### Adafruit UF-2

Eerst leek het ons interessant om de Adafruit bootloader aan te passen aan de SAMDaaNo21. Die maakt het gemakkelijk om met de Arduino IDE te werken maar ook om met CircuitPython.

https://github.com/DaanDekoningKrekels/uf2-samdx1

https://learn.adafruit.com/adafruit-feather-m4-express-atsamd51/uf2-bootloader-details

De UF2 bootloader van Adafruit is BOSSA compatible, wat wil zeggen dat deze ook werkt met de Arduino IDE. Spijtig genoeg is het ons niet gelukt om een werkende versie van deze bootloader te compileren.

### Arduino Core voor SAMD21 CPU

Hiervoor speelt alles zich af in de [./bootloaders/](https://github.com/DaanDekoningKrekels/ArduinoCore-samd/tree/master/bootloaders) folder van de GitHub repo.

Folder van de Arduino Zero `zero/` gedupliceerd en hernoemd naar `samdaano21/`.

Belangrijke bestanden:

| Naam                           | Beschrijving                                                 |
| ------------------------------ | ------------------------------------------------------------ |
| Makefile                       | Beschrijft alle instellingen voor de compiler.               |
| board_definitions.h            | Lijst de verschillende borden op.                            |
| board_definitions_samdaano21.h | Bestand gebaseerd op board_definitions_zero.h, specifiek voor de SAMDaaNo21. Bevat instellingen voor de bootloader zoals USB VID, PID en CPU frequentie. |
| bootloader_samd21x16.ld        | Bestand gebaseerd op bootloader_samd21x18.ld, is een linker script waar onder andere de geheugen regios in worden beschreven. |


#### Board definitions

We dupliceren `board_definitions_zero.h` en hernoemen de kopie naar `board_definitions_samdaano21.h`. 

In dit bestand passen we enkel de USB instellingen aan en het BOOT_DOUBLE_TAP_ADDRESS. Dat adres is afhankelijk van de hoeveelheid ram. Op het moment dat er dubbel gedrukt wordt op de RESET knop, zal de bootloader in de laatste 4 bytes van het geheugen uitvoeren. Het adres is dus de totale RAM - 4 bytes. $8\text{kb} - 4\text{b} = 0\text{x}2000 - 0\text{x}4 = 0\text{x}1FFC$

`board_definitions_samdaano21.h`

````c
[...]
/*
 * USB device definitions
 */
#define STRING_PRODUCT "SAMDaaNo21"
#define USB_VID_HIGH   0x03     // Atmel
#define USB_VID_LOW    0xEB
#define USB_PID_HIGH   0x24     // Generic HID device
#define USB_PID_LOW    0x02

/*
 * If BOOT_DOUBLE_TAP_ADDRESS is defined the bootloader is started by
 * quickly tapping two times on the reset button.
 * BOOT_DOUBLE_TAP_ADDRESS must point to a free SRAM cell that must not
 * be touched from the loaded application.
 */
//#define BOOT_DOUBLE_TAP_ADDRESS           (0x20007FFCul)
// https://forum.arduino.cc/t/how-to-upload-arduino-bootloader-to-a-custom-samd21-usig-jlink-mini/906434/13
#define BOOT_DOUBLE_TAP_ADDRESS           (0x20001FFCul) // 8kb ram - 4 bytes = 10x8188 0x1FFC
#define BOOT_DOUBLE_TAP_DATA              (*((volatile uint32_t *) BOOT_DOUBLE_TAP_ADDRESS))
[...]
````

 `board_definitions.h` moet nu aangepast worden om ons nieuwe bestand te kunnen includen.

Pas het volgende aan:

 `board_definitions.h`

````c
#if defined(BOARD_ID_samdaano21)
  #include "board_definitions_samdaano21.h"
#elif defined(BOARD_ID_arduino_zero)
  #include "board_definitions_arduino_zero.h"
[...]
````



#### Linker script

Referentie: https://forum.arduino.cc/t/how-to-upload-arduino-bootloader-to-a-custom-samd21-usig-jlink-mini/906434/11

Zeer goede documentatie: https://blog.thea.codes/the-most-thoroughly-commented-linker-script/

`bootloader_samd21x18.ld` -> `bootloader_samd21x16.ld `

Dit is het linker script. Daarin is enkel de memory mapping aangepast. De ATSAMD21x18 versie heeft 256kb flash en 32kb SRAM. De ATSAMD21x16 heeft 64kb flash en 8kb SRAM. Deze waardes zijn hexadecimaal in het linker script geplaatst.

`bootloader_samd21x16.ld`

````c
MEMORY
{
  FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 0x2000 /* First 8KB used by bootloader */
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x00002000-0x0400 /* last 4 bytes used by bootloader to keep data between resets, but reserves 1024 bytes for sketches to have same possibility */
}
````

#### Makefile

De makefile geeft de compiler de juiste instructies om de bootloader te kunnen samenstellen. Hier passen we het BOARD_ID aan, de verwijzing naar het LD_SCRIPT en veranderen bij compiler options de MCU van G18A naar G16A.

`Makefile`

````makefile
[...]
# Boards definitions
BOARD_ID?=samdaano21
[...]
CFLAGS_EXTRA=-D__SAMD21G16A__ -DBOARD_ID_$(BOARD_ID) -D$(SAM_BA_INTERFACES)
[...]
LD_SCRIPT=bootloader_samd21x16.ld
[...]
````

#### Compileren

Met het commando `make clean all` kan de gehele bootloader gecompileerd worden.

Er zal een `samd21_sam_ba.hex` en een `samd21_sam_ba.bin` bestand aangemaakt worden.


#### Problemen

Het had fijn geweest moest het werk geloond hebben, maar deze bootloader hebben we niet werkende gekregen. Het lukte niet om via de Arduino IDE code te uploaden naar de SAMDaaNo21.

Als alternatief zijn we terechtgekomen bij de standaard bootloader die Microchip aanbriedt voor hun SAMD lijn, de SAM-BA bootloader. 

SAM-BA maakt het mogleijk om via USB te communiceren met een AT SAM microcontroller. Op deze manier is er geen externe programmer nodig!

Wetende dat deze bootloader bestaat, is het enkel nog zoeken naar de download link... Alle verwijzingen in de volgende PDF's zien er als volgt uit:

>The user guide comes with the SAM-BA package available on www.atmel.com.

Enkele links over SAM-BA (SAM Boot Assist):

-  [AN_42438 - AT09423: SAM-BA Overview and Customization Process (PDF)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42438-SAM-BA-Overview-and-Customization-Process_ApplicationNote_AT09423.pdf) 
-  [AN_42366 - AT07175: SAM-BA Bootloader for SAM D21 (PDF)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42366-SAM-BA-Bootloader-for-SAM-D21_ApplicationNote_AT07175.pdf)
-  [AN_42728 - AT15004:Using SAM-BA for Linux on SAM Devices (PDF)](https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42728-Using-SAM-BA-for-Linux-on-SMART-ARM-based-Microcontrollers_ApplicationNotes_AT15004.pdf) 
-  [SAM-BA Monitor for ROMless Cortex M Devices - SAM-BA® Monitor for ROMless Cortex Devices Application Note (PDF)](https://ww1.microchip.com/downloads/en/DeviceDoc/00002565A.pdf) 
-  [How to Customize ASFv3 SAM-BA Bootloader on Cortex- (PDF)](https://ww1.microchip.com/downloads/en/DeviceDoc/How-to-Customize-ASFv3-SAM-BA-Bootloade-on-Cortex-M0-Microcontrollers-DS90003190A.pdf) 
-  [Where can I download the official ATSAM D21 bootloader and how to burn it??](https://www.avrfreaks.net/s/topic/a5C3l000000Uiu3EAC/t185718)
-  [SAM-BA Bootloader for SAMD21G15B](https://www.avrfreaks.net/s/topic/a5C3l000000Uf3qEAC/t170949)
-  [SAM-BA Bootloader! (ZIP)](http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-42366-SAM-BA-Bootloader-for-SAM-D21_ApplicationNote_AT07175.zip)

De laatste link gaat rechtstreeks naar de download van de bootloader. De inhoud zit er als volgt uit:

```
.
├── LED_Toggle_0x1000.bin
├── LED_Toggle_0x2000.bin
├── load sam-ba
│   ├── samd21e15a
│   ├── samd21e16a
│   ├── samd21e17a
│   ├── samd21e18a
│   ├── samd21g15a
│   ├── samd21g16a
│   │   ├── samd21_sam_ba_both_interfaces.hex
│   │   ├── samd21_sam_ba_uart.hex
│   │   └── samd21_sam_ba_usbcdc.hex
│   ├── samd21g17a
│   ├── samd21g18a
│   ├── samd21j15a
│   ├── samd21j16a
│   ├── samd21j17a
│   └── samd21j18a
└── sam-ba_monitor.zip

```

Enkel de bootloader `samd21_sam_ba_both_interfaces.hex` in de map `samd21g16a` is voor ons van toepassing. Met deze bootloader werkt uploaden vanaf de Arduino IDE!

Een belangrijke kanttekening: De Arduino IDE gebruikt de prigramming tool [BOSSA](https://github.com/shumatech/BOSSA) om binaries naar een SAM-BA apparaat te sturen. Deze tool onderstunt standaard de ATSAMD21G16 **niet**. Om die reden moet een [aangepaste versie van BOSSA](https://github.com/mattairtech/BOSSA) gebruikt worden, namelijk deze van Justin Mattair (mattairtech).

Nu we een bootloader hebben, moet deze naar de SAMDaaNo21 geschreven worden. Zie documentatie.





## 1- Prerequisites

The project build is based on Makefile system.
Makefile is present at project root and try to handle multi-platform cases.

Multi-plaform GCC is provided by ARM here: https://launchpad.net/gcc-arm-embedded/+download

Atmel Studio contains both make and ARM GCC toolchain. You don't need to install them in this specific use case.

For all builds and platforms you will need to have the Arduino IDE installed and the board support
package for "Arduino SAMD Boards (32-bits ARM Cortex-M0+)". You can install the latter
from the former's "Boards Manager" UI.

### Windows

* Native command line
Make binary can be obtained here: http://gnuwin32.sourceforge.net/packages/make.htm

* Cygwin/MSys/MSys2/Babun/etc...
It is available natively in all distributions.

* Atmel Studio
An Atmel Studio **7** Makefile-based project is present at project root, just open samd21_sam_ba.atsln file in AS7.

### Linux

Make is usually available by default.

### OS X

Make is available through XCode package.


## 2- Selecting available SAM-BA interfaces

By default both USB and UART are made available, but this parameter can be modified in sam_ba_monitor.h, line 31:

Set the define SAM_BA_INTERFACE to
* SAM_BA_UART_ONLY for only UART interface
* SAM_BA_USBCDC_ONLY for only USB CDC interface
* SAM_BA_BOTH_INTERFACES for enabling both the interfaces

## 3- Behaviour

This bootloader implements the double-tap on Reset button.
By quickly pressing this button two times, the board will reset and stay in bootloader, waiting for communication on either USB or USART.

The USB port in use is the USB Native port, close to the Reset button.
The USART in use is the one available on pins D0/D1, labelled respectively RX/TX. Communication parameters are a baudrate at 115200, 8bits of data, no parity and 1 stop bit (8N1).

## 4- Description

**Pinmap**

The following pins are used by the program :
PA25 : input/output (USB DP)
PA24 : input/output (USB DM)
PA11 : input (USART RX)
PA10 : output (USART TX)

The application board shall avoid driving the PA25, PA24, PB23 and PB22 signals while the boot program is running (after a POR for example).

**Clock system**

CPU runs at 48MHz from Generic Clock Generator 0 on DFLL48M.

Generic Clock Generator 1 is using external 32kHz oscillator and is the source of DFLL48M.

USB and USART are using Generic Clock Generator 0 also.

**Memory Mapping**

Bootloader code will be located at 0x0 and executed before any applicative code.

Applications compiled to be executed along with the bootloader will start at 0x2000 (see linker script bootloader_samd21x18.ld).

Before jumping to the application, the bootloader changes the VTOR register to use the interrupt vectors of the application @0x2000.<- not required as application code is taking care of this.

## 5- How to build

If not specified the makefile builds for **Arduino Zero**:

```
make
```

if you want to make a custom bootloader for a derivative board you must supply all the necessary information in a `board_definitions_xxx.h` file, and add the corresponding case in `board_definitions.h`.
For example for the **Arduino MKR1000** we use `board_definitions_arduino_mkr1000.h` and it is build with the following command:

```
BOARD_ID=arduino_mkr1000 NAME=samd21_sam_ba_arduino_mkr1000 make clean all
```


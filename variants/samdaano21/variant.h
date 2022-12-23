/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

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
*/

#ifndef _VARIANT_ARDUINO_SAMDAANO21_
#define _VARIANT_ARDUINO_SAMDAANO21_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK			  (48000000ul)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------
 * "ul" = unsigned long
 * "u" = unsigned
*/

// Number of pins defined in PinDescription array
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif
#define PINS_COUNT           (PINCOUNT_fn())
#define NUM_DIGITAL_PINS     (20u)
#define NUM_ANALOG_INPUTS    (6u)
#define NUM_ANALOG_OUTPUTS   (1u)
#define analogInputToDigitalPin(p)  ((p < 6u) ? (p) + 14u : -1)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)

#define PA02        (0ul)
#define PA03        (1ul)
#define PB08        (2ul)
#define PB09        (3ul)
#define PA04        (4ul)
#define PA05        (5ul)
#define S0TX        (4ul) // TX SERCOM0 UART
#define S0RX        (5ul) // RX
#define PA06        (6ul)
#define PA07        (7ul)
#define PA08        (8ul)
#define PA09        (9ul)
#define S2TX        (8ul) // TX SECOM 2 UART
#define S2RX        (9ul) // RX
#define PA10        (10ul)
#define PA11        (11ul)
#define PA12        (12ul)
#define PA13        (13ul)
#define S4SDA       (12ul) // SDA SERCOM 4 I2C
#define S4SCL       (13ul) // SCL

// Andere kant
#define PB03        (14ul)
#define PB22        (15ul)
#define PA23        (16ul)
#define PA22        (17ul)
#define S5RX        (16ul) // RX SERCOM 5 UART
#define S5TX        (17ul) // TX
#define PA21        (18ul)
#define PA20        (19ul)
#define PA19        (20ul)
#define PA18        (21ul)
#define PA17        (22ul)
#define PA16        (23ul)
#define S3SS        (20ul) // SS SERCOM 3 SPI
#define S3MISO      (21ul) // MISO
#define S3SCK       (22ul) // SCK
#define S3MOSI      (23ul) // MOSI
#define PA15        (24ul)
#define PA14        (25ul)

// LEDs
//#define PIN_LED_13           (13u)
//#define PIN_LED_RXL          (25u)
//#define PIN_LED_TXL          (26u)
//#define PIN_LED              PIN_LED_13
//#define PIN_LED2             PIN_LED_RXL
//#define PIN_LED3             PIN_LED_TXL
//#define LED_BUILTIN          PIN_LED_13

/*
 * Analog pins
 */
#define PIN_A0               (0ul)
#define PIN_A1               (1ul)
#define PIN_A2               (2ul)
#define PIN_A3               (3ul)
#define PIN_A4               (6ul)
#define PIN_A5               (14ul)
#define PIN_DAC0             (26ul)

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
static const uint8_t DAC0 = PIN_DAC0;
#define ADC_RESOLUTION		12

// Other pins
#define PIN_ATN              (38ul)
static const uint8_t ATN = PIN_ATN;

/*
 * Serial interfaces
 */
// Serial (EDBG)
#define PIN_SERIAL1_RX       (5ul)
#define PIN_SERIAL1_TX       (4ul)
#define PAD_SERIAL1_TX       (UART_TX_PAD_0)
#define PAD_SERIAL1_RX       (SERCOM_RX_PAD_1)

// Serial1
// Serial voor de LoRaWAN module
// PA9 kan niet meer gebruikt worden door fix voor vekeerd aangesloten RX en TX.
#define PIN_SERIAL2_RX       (8ul)
#define PIN_SERIAL2_TX       (10ul)
#define PAD_SERIAL2_TX       (UART_TX_PAD_2)
#define PAD_SERIAL2_RX       (SERCOM_RX_PAD_0)

// Serial2
#define PIN_SERIAL3_RX       (16ul)
#define PIN_SERIAL3_TX       (17ul)
#define PAD_SERIAL3_TX       (UART_TX_PAD_0)
#define PAD_SERIAL3_RX       (SERCOM_RX_PAD_1)



/*
 * SPI Interfaces
 * https://learn.sparkfun.com/tutorials/adding-more-sercom-ports-for-samd-boards/all#adding-an-spi
 */
#define SPI_INTERFACES_COUNT 1

#define PIN_SPI_MISO         (22u)
#define PIN_SPI_MOSI         (24u)
#define PIN_SPI_SCK          (23u)
#define PERIPH_SPI           sercom3
#define PAD_SPI_TX           SPI_PAD_0_SCK_1
#define PAD_SPI_RX           SERCOM_RX_PAD_2

static const uint8_t SS	  = PA19 ;	// SERCOM4 last PAD is present on A2 but HW SS isn't used. Set here only for reference.
static const uint8_t MOSI = PIN_SPI_MOSI ;
static const uint8_t MISO = PIN_SPI_MISO ;
static const uint8_t SCK  = PIN_SPI_SCK ;

/*
 * Wire Interfaces
 * https://learn.sparkfun.com/tutorials/adding-more-sercom-ports-for-samd-boards/all#adding-an-i2c
 */
#define WIRE_INTERFACES_COUNT 1

#define PIN_WIRE_SDA         (12u)
#define PIN_WIRE_SCL         (13u)
#define PERIPH_WIRE          sercom4
#define WIRE_IT_HANDLER      SERCOM4_Handler

static const uint8_t SDA = PIN_WIRE_SDA;
static const uint8_t SCL = PIN_WIRE_SCL;

/*
 * USB
 */
#define PIN_USB_HOST_ENABLE (27ul) // TODO: Wat is dit? 
#define PIN_USB_DM          (28ul)
#define PIN_USB_DP          (29ul)

/*
 * I2S Interfaces
 * Geen I2S
 */
// #define I2S_INTERFACES_COUNT 1

// #define I2S_DEVICE          0
// #define I2S_CLOCK_GENERATOR 3
// #define PIN_I2S_SD          (9u)
// #define PIN_I2S_SCK         (1u)
// #define PIN_I2S_FS          (0u)

#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;
extern SERCOM sercom4;
extern SERCOM sercom5;

extern Uart Serial;
extern Uart Serial1;
extern Uart Serial2;
extern Uart Serial3;

#endif

#ifdef __cplusplus
extern "C" {
#endif
unsigned int PINCOUNT_fn();
#ifdef __cplusplus
}
#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB
// Alias Serial to SerialUSB
#define Serial                      SerialUSB

// Serial has no physical pins broken out, so it's not listed as HARDWARE port
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial2
#define SERIAL_PORT_HARDWARE        Serial2
#define SERIAL_PORT_HARDWARE        Serial3
#define SERIAL_PORT_HARDWARE_OPEN   Serial3

// Alias Serial2 voor LoRa module
#define SerialLoRa                  Serial2

#endif /* _VARIANT_ARDUINO_SAMDAANO21_ */


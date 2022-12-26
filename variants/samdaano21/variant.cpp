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
/*

  | LABELS | DEFAULT | TYPE   | GROUP         | I/O Pin | Pin      | SERCOM           | SERCOM-ALT  | External Interrupt | ADC, DAC, AC, REF | Peripheral Touch Controller | TC/TCC    | TCC       | COM       | Generic Clock Generator |
  | ------ | ------- | ------ | ------------- | ------- | -------- | ---------------- | ----------- | ------------------ | ----------------- | --------------------------- | --------- | --------- | --------- | ----------------------- |
  |        | POWER   | OUTPUT | POWER         | GND     | PowerPin | Ground Reference |             |                    | ADC:0VOUT         |                             |           |           |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PA02    | 3        |                  |             | EXTINT:2           | ADC:1VREFA        | Y:0                         |           | TCC3/WO:0 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PA03    | 4        |                  |             | EXTINT:3           | ADC:2             | Y:1                         |           | TCC3/WO:1 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PB08    | 7        |                  | SCOM4/PAD:0 | EXTINT:8           | ADC:3             | Y:14                        | TC4/WO:0  | TCC3/WO:6 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PB09    | 8        |                  | SCOM4/PAD:1 | EXTINT:9           | ADC:4AC:0 VREFB   | Y:15                        | TC4/WO:1  | TCC3/WO:7 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PA04    | 9        |                  | SCOM0/PAD:0 | EXTINT:4           | ADC:5AC:1         | Y:2                         | TCC0/WO:0 | TCC3/WO:2 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PA05    | 10       |                  | SCOM0/PAD:1 | EXTINT:5           | ADC:6AC:2         | Y:3                         | TCC0/WO:1 | TCC3/WO:3 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PA06    | 11       |                  | SCOM0/PAD:2 | EXTINT:6           | ADC:7AC:3         | Y:4                         | TCC1/WO:0 | TCC3/WO:4 |           |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PA07    | 12       |                  | SCOM0/PAD:3 | EXTINT:7           | ADC:16            | Y:5                         | TCC1/WO:1 | TCC3/WO:5 | I2S/SD:0  |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA08    | 13       | SCOM0/PAD:0      | SCOM2/PAD:0 | NMI                | ADC:17            | X:0                         | TCC0/WO:0 | TCC1/WO:2 | I2S/SD:1  |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA09    | 14       | SCOM0/PAD:1      | SCOM2/PAD:1 | EXTINT:9           | ADC:18            | X:1                         | TCC0/WO:1 | TCC1/WO:3 | I2S/MCK:0 |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA10    | 15       | SCOM0/PAD:2      | SCOM2/PAD:2 | EXTINT:10          | ADC:19            | X:2                         | TCC1/WO:0 | TCC0/WO:2 | I2S/SCK:0 | GCLK:4                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA11    | 16       | SCOM0/PAD:3      | SCOM2/PAD:3 | EXTINT:11          | AC:0              | X:3                         | TCC1/WO:1 | TCC0/WO:3 | I2S/FS:0  | GCLK:5                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA12    | 21       | SCOM2/PAD:0      | SCOM4/PAD:0 | EXTINT:12          | AC:1              |                             | TCC2/WO:0 | TCC0/WO:6 |           |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA13    | 22       | SCOM2/PAD:1      | SCOM4/PAD:1 | EXTINT:13          |                   |                             | TCC2/WO:1 | TCC0/WO:7 |           |                         |



  | LABELS | DEFAULT | TYPE   | GROUP         | I/O Pin | Pin      | SERCOM                  | SERCOM-ALT  | External Interrupt | ADC, DAC, AC, REF | Peripheral Touch Controller | TC/TCC    | TCC       | COM          | Generic Clock Generator |
  | ------ | ------- | ------ | ------------- | ------- | -------- | ----------------------- | ----------- | ------------------ | ----------------- | --------------------------- | --------- | --------- | ------------ | ----------------------- |
  |        | POWER   | OUTPUT | POWER         | VIN     | PowerPin | LDL1117S33 4.3 V - 15 V |             |                    |                   |                             |           |           |              |                         |
  |        | POWER   | OUTPUT | POWER         | 3V3     | PowerPin | 3.3V LDO output         |             |                    |                   |                             |           |           |              |                         |
  |        | POWER   | OUTPUT | POWER         | GND     | PowerPin | Ground Reference        |             |                    |                   |                             |           |           |              |                         |
  | PIN    | ANALOG  | IO     | SAMD21 VDDANA | PB03    | 48       |                         | SCOM5/PAD:1 | EXTINT:3           | ADC:11            | Y:9                         | TC6/WO:1  | TCC3/WO:3 |              |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PB22    | 37       |                         | SCOM5/PAD:2 | EXTINT:6           |                   |                             | TC7/WO:0  | TCC3/WO:0 |              | GCLK:0                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA23    | 32       | SCOM3/PAD:1             | SCOM5/PAD:1 | EXTINT:7           |                   | X:11                        | TC4/WO:0  | TCC0/WO:5 | USB/SOF 1KhZ | GCLK:7                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA22    | 31       | SCOM3/PAD:0             | SCOM5/PAD:0 | EXTINT:6           |                   | X:10                        | TC4/WO:1  | TCC0/WO:4 |              | GCLK:6                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA21    | 30       | SCOM5/PAD:3             | SCOM3/PAD:3 | EXTINT:5           |                   | X:9                         | TC7/WO:1  | TCC0/WO:7 | I2S/FS:0     | GCLK:5                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA20    | 29       | SCOM5/PAD:2             | SCOM3/PAD:2 | EXTINT:4           |                   | X:8                         | TC7/WO:0  | TCC0/WO:6 | I2S/SCK:0    | GCLK:4                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA19    | 28       | SCOM1/PAD:3             | SCOM3/PAD:3 | EXTINT:3           | AC:1              | X:7                         | TC3/WO:1  | TCC0/WO:3 | I2S/SD:0     |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA18    | 27       | SCOM1/PAD:2             | SCOM3/PAD:2 | EXTINT:2           | AC:0              | X:6                         | TC3/WO:0  | TCC0/WO:2 |              |                         |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA17    | 26       | SCOM1/PAD:1             | SCOM3/PAD:1 | EXTINT:1           |                   | X:5                         | TCC2/WO:1 | TCC0/WO:7 |              | GCLK:3                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA16    | 25       | SCOM1/PAD:0             | SCOM3/PAD:0 | EXTINT:0           |                   | X:4                         | TCC2/WO:0 | TCC0/WO:6 |              | GCLK:2                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA15    | 24       | SCOM2/PAD:3             | SCOM4/PAD:3 | EXTINT:15          |                   |                             | TC3/WO:1  | TCC0/WO:5 |              | GCLK:1                  |
  | PIN    | PWM     | IO     | SAMD21 VDDIO  | PA14    | 23       | SCOM2/PAD:2             | SCOM4/PAD:2 | EXTINT:14          |                   |                             | TC3/WO:0  | TCC0/WO:4 |              | GCLK:0                  |

 */


#include "variant.h"

/*
 * Pins descriptions
 *
 * Dit is een array. Dat wil zeggen dat iedere pin definitie een array index heeft. Naar deze index refereren we in variant.h.
 * Zie WVariant.h in de core folder voor alle mogleijke opties (PIO_ANALOG, PIN_ATTR_ANALOG, ...).
 */
const PinDescription g_APinDescription[]=
{
  // 0
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // ADC/AIN[0]
  // 1
  { PORTA,  3, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel1, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_3 }, // DAC/VREFP
  // 2
  { PORTB,  8, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel2, PWM4_CH0, TC4_CH0, EXTERNAL_INT_8 }, // ADC/AIN[2]
  // 3
  { PORTB,  9, PIO_ANALOG, (PIN_ATTR_PWM|PIN_ATTR_TIMER), ADC_Channel3, PWM4_CH1, TC4_CH1, EXTERNAL_INT_9 }, // ADC/AIN[3]
  // 4, 5
  // SERCOM 0 - UART TX - RX
  { PORTA,  4, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_4 }, // TX: SERCOM0/PAD0
  { PORTA,  5, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_5 }, // RX: SERCOM0/PAD1
  // 6
  { PORTA,  6, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel6, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_6 }, // TCC1/WO[0]
  // 7
  { PORTA,  7, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM1_CH1, TCC1_CH1, EXTERNAL_INT_7 }, // TCC1/WO[1]
  // 8,9
  // SERCOM 2 - UART TX - RX
  { PORTA,  8, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH0, TCC0_CH0, EXTERNAL_INT_NMI },   // RX: SERCOM2/PAD0
  { PORTA,  9, PIO_DIGITAL, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM0_CH1, TCC0_CH1, EXTERNAL_INT_9 },        // Niet gebruiken
  // 10
  { PORTA, 10, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_10 },                          // TX: SERCOM2/PAD2
  // 11
  { PORTA, 11, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_11 }, 
  // 12, 13
  // SERCOM 4 I2C SDA - SCL
  { PORTA, 12, PIO_SERCOM_ALT, PIN_ATTR_DIGITAL, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_12 },       // SDA: SERCOM4/PAD0
  { PORTA, 13, PIO_SERCOM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH5, NOT_ON_TIMER, EXTERNAL_INT_13 }, // SCL: SERCOM4/PAD1

  // 14
  // Andere kant
  { PORTB,  3, PIO_ANALOG, PIN_ATTR_DIGITAL, ADC_Channel11, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 
  // 15
  { PORTB, 22, PIO_DIGITAL, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, 
  // 16, 17
  // SERCOM 5 UART RX - TX
  { PORTA, 23, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // RX: SERCOM5/PAD1
  { PORTA, 22, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // TX: SERCOM5/PAD0
  // 18
  { PORTA, 21, PIO_PWM_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM), No_ADC_Channel, PWM0_CH7, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // Pin 7
  // 19
  { PORTA, 20, PIO_TIMER_ALT, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER_ALT), No_ADC_Channel, PWM0_CH6, TCC0_CH6, EXTERNAL_INT_4 }, // TCC0/WO[6]
  // 20

  // 21, 22, 23, 24
  // SERCOM 3 SPI SS - MISO - SCK - MOSI
  { PORTA, 19, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SS: SERCOM1/PAD[3]
  { PORTA, 18, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MISO: SERCOM1/PAD[2]
  { PORTA, 17, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // SCK: SERCOM1/PAD[1]
  { PORTA, 16, PIO_SERCOM_ALT, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // MOSI: SERCOM1/PAD[0]

  // 24
  { PORTA, 15, PIO_TIMER, (PIN_ATTR_DIGITAL|PIN_ATTR_PWM|PIN_ATTR_TIMER), No_ADC_Channel, PWM3_CH1, TC3_CH1, EXTERNAL_INT_15 }, // TC3/WO[1]
  // 25
  { PORTA, 14, PIO_DIGITAL, (PIN_ATTR_DIGITAL), No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_14 },
  // 26 | Alternate use of A0 (DAC output)
  { PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, DAC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // DAC/VOUT
  // 27, 28, 29
  { PORTA, 28, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB Host enable
  { PORTA, 24, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DM
  { PORTA, 25, PIO_COM, PIN_ATTR_NONE, No_ADC_Channel, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_NONE }, // USB/DP

} ;

extern "C" {
    unsigned int PINCOUNT_fn() {
        return (sizeof(g_APinDescription) / sizeof(g_APinDescription[0]));
    }
}

const void* g_apTCInstances[TCC_INST_NUM+TC_INST_NUM]={ TCC0, TCC1, TCC2, TC3, TC4, TC5 } ;

// Multi-serial objects instantiation
SERCOM sercom0( SERCOM0 ) ;
SERCOM sercom1( SERCOM1 ) ;
SERCOM sercom2( SERCOM2 ) ;
SERCOM sercom3( SERCOM3 ) ;
SERCOM sercom4( SERCOM4 ) ;
SERCOM sercom5( SERCOM5 ) ;

Uart Serial1( &sercom0, PIN_SERIAL1_RX, PIN_SERIAL1_TX, PAD_SERIAL1_RX, PAD_SERIAL1_TX ) ;
Uart Serial2( &sercom2, PIN_SERIAL2_RX, PIN_SERIAL2_TX, PAD_SERIAL2_RX, PAD_SERIAL2_TX ) ;
Uart Serial3( &sercom5, PIN_SERIAL3_RX, PIN_SERIAL3_TX, PAD_SERIAL3_RX, PAD_SERIAL3_TX ) ;

void SERCOM0_Handler()
{
  Serial1.IrqHandler();
}

void SERCOM2_Handler()
{
  Serial2.IrqHandler();
}

void SERCOM5_Handler()
{
  Serial3.IrqHandler();
}


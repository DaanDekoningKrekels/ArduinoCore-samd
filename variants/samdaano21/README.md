## Arduino variant

Wanneer de bootloader op de SAMDaaNo21 straat en je sluit de USB poort aan, zal je onder `tools`-> `port` een apparaat zien staan!

We kunnen echter nog niets programmeren naar de SAMDaano21 omdat de Arduino IDE niet weet hoe het apparaat werkt. In de volgende stappen voegen we een Arduino variant toe aan de IDE.

Hiervoor speelt het meeste zich af in de ./variants/ folder van de GitHub repo, `boards.txt` passen we ook aan.

| Naam                                           | Beschrijving                                                 |
| ---------------------------------------------- | ------------------------------------------------------------ |
| boards.txt                                     | Bestand met definities en instellingen voor Arduino borden weer te geven in de Arduino IDE onder `tools`-> `board: xxx` |
| variants/samdaano21/                           |                                                              |
| variant.h                                      | Bestand waar alle pin-namen die via de Arduino IDE aanspreekbaar zijn worden gedefinieerd. |
| variant.cpp                                    | Bestand waar alle beschikbare pinnen en hun functies in één array worden samengebracht. |
| openocd_scripts/samdaano21.cfg                 | OpenOCD script om te communiceren met de MCU.                |
| linker_scripts/gcc/flash_with_bootloader.ld    | Linker script dat wederom de geheugen regio's weergeeft, ditmaal met een offset van 8kb om de bootloader niet te overschrijven. |
| linker_scripts/gcc/flash_without_bootloader.ld | Linker script dat wederom de geheugen regio's weergeeft.     |

### variant.cpp en variant.h

In het `variant.cpp` bestand zit een grote array waarin iedere bruikbare pin definitie wordt bijgehouden. De opties voor individuele pinnen zijn gedefinieerd in `WVariant.h`, dat bestand kan je vinden in de core folder.

Per pin op de SAMDaaNo21 zijn er functies die toegewezen worden. Om de juiste functies toe te wijzen aan de pinnen refereer je naar de [datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/SAM-D21DA1-Family-Data-Sheet-DS40001882G.pdf) hoofdstuk 7 I/O Multiplexing and Considerations. Mogelijke functies:

`WVariant.h`

````c++
/* Types used for the table below */
typedef struct _PinDescription
{
  EPortType       ulPort ;
  uint32_t        ulPin ;
  EPioType        ulPinType ;
  uint32_t        ulPinAttribute ;
  EAnalogChannel  ulADCChannelNumber ; /* ADC Channel number in the SAM device */
  EPWMChannel     ulPWMChannel ;
  ETCChannel      ulTCChannel ;
  EExt_Interrupts ulExtInt ;
} PinDescription ;
````

Deze functies worden in `variant.cpp` op volgende manier weergegeven:

````c++
{ PORTA,  2, PIO_ANALOG, PIN_ATTR_ANALOG, ADC_Channel0, NOT_ON_PWM, NOT_ON_TIMER, EXTERNAL_INT_2 }, // ADC/AIN[0]
````

PA02 is dus een analoge pin die gebruik maakt van ADC:0. Er is geen PWM mogleijkheid en geen timer, wel een externe interupt EXTINT:2.

Bovenstaande lijn code staat op index 0 van de `g_APinDescription` array. In `variant.h` moet de pin daar nog worden ingesteld als analoge pin.

`variant.h`

````c++
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
````

Op deze manier worden de pinnen gedefinieerd voor Arduino code. Nu kan er gebruik gemaakt worden van `A0` in de code om een analoge pin uit te lezen.

Om gebruik van de SAMDaaNo21 gemakkelijker te maken zijn alle pinnen die omschreven zijn op de slikscreen (PCB zelf) ook voorgedefinieerd.

**Let op dat `PA07` op de slikscreen staat aangegeven als `PA09`**

```c++
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
```

Ook de SERCOM poorten zijn in dit bestand gefomuleerd.

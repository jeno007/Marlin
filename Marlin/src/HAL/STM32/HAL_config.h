//
// SPI devices, buses and pins definition
//
#define NUM_SPI_BUSES 3   //number of SPI buses in the controller
#define SPI_HAS_HW_CRC    //board supports hardware CRC

const int SPI_BusConfig[NUM_SPI_BUSES][6] = {
// MOSI, MISO, SCK , Mode (def), Bit order (default)
  {PB5 , PA6 , PA5 , SPI_MODE_3, SPI_MSB, SPI_HALF_SPEED}, //BUS0: only connected to onboard SD
  {PB15, PB14, PB13, SPI_MODE_0, SPI_MSB, SPI_FULL_SPEED}, //BUS1: on EXT2 port
  {PC12, PC11, PC10, SPI_MODE_0, SPI_MSB, SPI_FULL_SPEED}  //BUS2: on SPI3 port (when not used by drivers)
};

#ifdef SD_DETECT_INVERTED
  #define ExtSDLV LOW
#else
  #define ExtSDLV HIGH
#endif

const int SPI_Devices[][9] = {
// Device type      BUS  Polarity Phase    Bit      MAX Supported  Selection Detect PIN Level when detected
//                  NR.                    Order    Speed          PIN        (SD only) (SD only)
  {DEVTYPE_SD     ,   0, SPI_PHI, SPI_STL, SPI_MSB, SPI_FULL_SPEED,     PA4,      PB11, LOW    },
  {DEVTYPE_SD     ,   1, SPI_PLO, SPI_LTS, SPI_MSB, SPI_FULL_SPEED,    PB12,      PF12, ExtSDLV},
  {DEVTYPE_SD     ,   2, SPI_PLO, SPI_LTS, SPI_MSB, SPI_FULL_SPEED,    PA15,        NC, NC     }, //optional external SD on SPI3
#if HAS_SPI_LCD
  {DEVTYPE_DISPLAY,   1, SPI_PLO, SPI_LTS, SPI_MSB, SPI_FULL_SPEED,    PD11,        NC, NC     },
#endif
//Drivers on this board are hard-wired.
//Users can't change the CS so we disallow the user-redefinition of the CS_PIN

// Device type      BUS  Polarity Phase    Bit      MAX Supported  Selection Type,            Index (for type)
//                  NR.                    Order    Speed          PIN       (Driver only)    (Driver only)
#if AXIS_HAS_SPI(X)         //NC = not change: use the default for the bus
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PA15, DRIVER_AXIS    , 0}, //Index 0 is X
#endif
#if AXIS_HAS_SPI(Y)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,     PB8, DRIVER_AXIS    , 1}, //Index 1 is Y
#endif
#if AXIS_HAS_SPI(Z)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,     PB9, DRIVER_AXIS    , 2}, //Index 2 is Z
#endif
#if AXIS_HAS_SPI(E0)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,     PB3, DRIVER_EXTRUDER, 0}, //E0
#endif
#if AXIS_HAS_SPI(E1)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PG15, DRIVER_EXTRUDER, 1}, //E1
#endif
#if AXIS_HAS_SPI(E2)
  {DEVTYPE_DRIVER ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PG12, DRIVER_EXTRUDER, 2}, //E2
#endif
  {DEVTYPE_EEPROM ,   2,      NC,      NC,      NC, SPI_FULL_SPEED,    PA15,              NC, NC} //optional external EEPROM on SPI3
};

#define NUM_SPI_DEVICES COUNT(SPI_Devices)

#ifndef SD_SEARCH_ORDER
  #define SD_SEARCH_ORDER { 0, 1, 2 }
#endif
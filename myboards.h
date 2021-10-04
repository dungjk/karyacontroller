#pragma once

#include "platform.h"
#include "config_pins.h"

/*

  ============================================================================================
     NAMEBOARD
  ============================================================================================
  #ifdef BOARD_NAMEBOARD

  // motors PIN
  #define xenable 2
  #define xdirection 6
  #define xstep 4

  #define yenable 7
  #define ydirection 9
  #define ystep 8

  #define zenable 10
  #define zdirection A5
  #define zstep A4

  #define e0enable 11
  #define e0direction A2
  #define e0step A3


  // ENDSTOPS PIN, can be using just 1 pin
  #define limit_pin 0

  #define temp_pin 6
  #define temp2_pin 6
  #define heater_pin 3
  #define heater2_pin 3

  #define DRIVE_XYYZ
  #define DRIVE_COREXY
  #define DRIVE_COREXZ
  #define DRIVE_DELTA
  #define DRIVE_DELTASIAN

  #define ISRTEMP    // avr reading using interrupt
  #define USETIMER1  // using timer1 or other timer (implemented timer1 on avr)
  #define CORESERIAL // reduce code on AVR
  #define OLEDDISPLAY // still WIP
  #define SDCARD_CS // pin for SDCARD
  #define KBOX_PIN // 4 key Kontrolbox using analog pin and serial resistors


  #define USE_EEPROM
*/


/*

  ============================================================================================
     TARANTHOLE
  ============================================================================================
*/
#ifdef BOARD_TARANTHOLE

#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 7
#define ydirection 9
#define ystep 8

#define zenable 10
#define zdirection A5
#define zstep A4

#define e0enable 11
#define e0direction A2
#define e0step A3



#define limit_pin 13

#define temp_pin 6
#define heater_pin 3


/*
  ============================================================================================
     BOARD_NANONANO
  ============================================================================================
*/
#elif defined(BOARD_NANONANO)

#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 7
#define ydirection 9
#define ystep 8

#define zenable 10
#define zdirection A5
#define zstep A4

#define e0enable 5
#define e0direction A2
#define e0step A3


// this not work anymore, must link all limit to 1 pin
//#define xmin_pin A1
//#define ymin_pin A0
//#define zmax_pin 13
#define limit_pin A1
#define INVERTENDSTOP // uncomment for normally open


#define temp_pin 6 //analog 6 because we use ISR
#define heater_pin 3

#define ISRTEMP
#define NUMBUFFER 8

/*
  ============================================================================================
     BOARD_NANONANO
  ============================================================================================
*/
#elif defined(BOARD_NANONANO_DELTA_NOSD)

#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 7
#define ydirection 9
#define ystep 8

#define zenable 10
#define zdirection A5
#define zstep A4

#define e0enable 5
#define e0direction A2
#define e0step A3



// this not work anymore, must link all limit to 1 pin
//#define xmin_pin A1
//#define ymin_pin A0
//#define zmax_pin 13
#define limit_pin A1

#define temp_pin 6 //analog 6 because we use ISR
#define heater_pin 3

#define ISRTEMP
#define NUMBUFFER 8
/*
  ============================================================================================
     BOARD_NANONANO_DELTA
  ============================================================================================
*/
#elif defined(BOARD_NANONANO_DELTA)


#define DRIVE_DELTA


#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 2
#define ydirection 9
#define ystep 8

#define zenable 2
#define zdirection A5
#define zstep A4

#define e0enable 2
#define e0direction A2
#define e0step A3


// this not work anymore, must link all limit to 1 pin
//#define xmin_pin A1
//#define ymin_pin A0
//#define zmax_pin 13
#define limit_pin A0

#define temp_pin 6 //analog 6 because we use ISR
#define heater_pin 3
#define NUMBUFFER 6
#define SDCARD_CS 10
//#define INVERTENDSTOP // uncomment for normally open
#define KBOX_PIN 7

#define ISRTEMP
/*
  ============================================================================================
     BOARD_NANONANO_SDCARD
  ============================================================================================
*/
#elif defined(BOARD_NANONANO_SDCARD)

#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 2
#define ydirection 9
#define ystep 8

#define zenable 2
#define zdirection A5
#define zstep A4

#define e0enable 2
#define e0direction A2
#define e0step A3


#define limit_pin A0

#define temp_pin 6 //analog 6 because we use ISR
#define heater_pin 5
//#define fan_pin 5

#define ISRTEMP

#define SDCARD_CS 10
#define INVERTENDSTOP // uncomment for normally open
#define KBOX_PIN 7
//#define USETIMER1

#define NUMBUFFER 8

/*
  ============================================================================================
     BOARD_NANO_3DPLEX
  ============================================================================================
*/
#elif defined(BOARD_NANO_3DPLEX)
// 2 3 4 6 7 8 9 10 a0 a2 a3 a4 a5 a6
// free  5 a1 a7
// for i2c work, free a4 a5
// so move a4 to 5 and a5 to a1

#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 2
#define ydirection 9
#define ystep 8

#define zenable 2
#define zdirection A5
#define zstep A4

#define e0enable 2
#define e0direction A2
#define e0step A3



//#define xmin_pin A0
//#define ymin_pin A0
#define limit_pin A0

#define temp_pin 6 //analog 6 because we use ISR
#define heater_pin 3
//#define fan_pin 5

#define ISRTEMP
//#define INVERTENDSTOP // uncomment for normally open

//#define SDCARD_CS 10
//#define KBOX_PIN 7
//#define OLED_CONTROL_PIN 7
#define USETIMER1

#define NUMBUFFER 9

/*
  ============================================================================================
     BOARD_NANO_3DPLEX
  ============================================================================================
*/

#elif defined(BOARD_NANO_3DPLEX2)
// 2 3 4 6 7 8 9 10 a0 a2 a3 a4 a5 a6
// free  5 a1 a7
// for i2c work, free a4 a5
// so move a4 to 5 and a5 to a1

#define xenable 2
#define xdirection 6
#define xstep 4

#define yenable 2
#define ydirection 9
#define ystep 8

#define zenable 2
#define zdirection A1 //A5
#define zstep 5 //A4

#define e0enable 2
#define e0direction A2
#define e0step A3


//#define xmin_pin A0
//#define ymin_pin A0
#define limit_pin A0

#define temp_pin 6 //analog 6 because we use ISR
#define heater_pin 3
//#define fan_pin 5

#define ISRTEMP
//#define INVERTENDSTOP // uncomment for normally open

#define SDCARD_CS 10
#define KBOX_PIN 7
//#define OLED_CONTROL_PIN 7
#define USETIMER1

#define NUMBUFFER 7


/*
  ============================================================================================
     BOARD_DIY_4XI
  ============================================================================================
*/
#elif defined(BOARD_DIY_4XI)
#define DRIVE_COREXY

#define xenable 2
#define xdirection 7
#define xstep 6

#define yenable 2
#define ydirection 4
#define ystep 5
/*
  #define zenable 2
  #define zdirection A1 //A5
  #define zstep 5 //A4

  #define e0enable 2
  #define e0direction A2
  #define e0step A3

*/

// no limit switch ?
//#define limit_pin A0

//#define temp_pin 6 //analog 6 because we use ISR
//#define heater_pin 3
#define fan_pin 3
#define servo_pin 11

//#define ISRTEMP
//#define INVERTENDSTOP // uncomment for normally open

//#define SDCARD_CS 10
//#define KBOX_PIN 7
//#define OLED_CONTROL_PIN 7
#define USETIMER1

#define NUMBUFFER 15

/*
  ============================================================================================
     BOARD_DIY_4XI
  ============================================================================================
*/
#elif defined(BOARD_DIY_CNC1)
#define DRIVE_COREXY

#define xenable 6
#define xdirection 5
#define xstep 4

#define yenable 6
#define ydirection 3
#define ystep 2
/*
  #define zenable 2
  #define zdirection A1 //A5
  #define zstep 5 //A4

  #define e0enable 2
  #define e0direction A2
  #define e0step A3

*/

#define limit_pin 7
#define laser_pin 8

//#define temp_pin 6 //analog 6 because we use ISR
//#define heater_pin 3
//#define servo_pin 11

//#define ISRTEMP
#define INVERTENDSTOP // uncomment for normally open

//#define SDCARD_CS 10
//#define KBOX_PIN 7
//#define OLED_CONTROL_PIN 7
#define USETIMER1

#define NUMBUFFER 12


/*
  ============================================================================================
     BOARD_NANONANO_STM32
  ============================================================================================
*/
#elif defined(BOARD_NANONANO_STM32)

#define xenable PB9
#define xdirection PB7
#define xstep PB8

#define yenable PB9
#define ydirection PB5
#define ystep PB6

#define zenable PB9
#define zdirection PB3
#define zstep PB4

#define e0enable PB9
#define e0direction PB14
#define e0step PB15



#define limit_pin PB12

#define INVERTENDSTOP
#define temp_pin PB1
#define heater_pin PA0
#define fan_pin PA2

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3
#define NUMBUFFER 20
/*
  ============================================================================================
     BOARD_ST3DV1
  ============================================================================================
*/
#elif defined(BOARD_ST33DV1_STM32_3DPLEX)

#define xenable PB9
#define xdirection PB7
#define xstep PB8

#define yenable PB9
#define ydirection PB5
#define ystep PB6

#define zenable PB9
#define zdirection PB3
#define zstep PB4

#define e0enable PB9
#define e0direction PB14
#define e0step PB15


#define limit_pin PB12

#define INVERTENDSTOP

#define temp_pin PB1
//#define temp2_pin PB0
#define heater_pin PA0
#define laser_pin PA0
//#define heater2_pin PA1
//#define fan_pin PA2

#define SDCARD_CS SS
#define KBOX_PIN PA3
#define NUMBUFFER 20

//#define powerpin PC15
/*
  ============================================================================================
     BOARD_ST3DV1
  ============================================================================================
*/
#elif defined(BOARD_ST33DV11_STM32)

#define xenable PB9
#define xdirection PB7
#define xstep PB8

#define yenable PB9
#define ydirection PB5
#define ystep PB6

//#define SWAPEZ

#ifdef SWAPEZ
#define zenable PB9
#define zdirection PB14
#define zstep PB15

#define e0enable PB9
#define e0direction PB3
#define e0step PB4
#else
#define zenable PB9
#define zdirection PB3
#define zstep PB4

#define e0enable PB9
#define e0direction PB14
#define e0step PB15
#endif

#define limit_pin PB12

#define INVERTENDSTOP

#define temp_pin PB1
#define temp2_pin PB0
#define heater_pin PA0
#define heater2_pin PA1
#define fan_pin PA3

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3
#define NUMBUFFER 20
/*
  ============================================================================================
     BOARD_ST3DV1
  ============================================================================================
*/
#elif defined(BOARD_ST33DV1_STM32)

#define xenable PB9
#define xdirection PB7
#define xstep PB8

#define yenable PB9
#define ydirection PB5
#define ystep PB6

#define zenable PB9
#define zdirection PB3
#define zstep PB4

#define e0enable PB9
#define e0direction PB14
#define e0step PB15


#define limit_pin PB12

#define INVERTENDSTOP

#define temp_pin PB1
//#define temp2_pin PB0
#define heater_pin PA0
//#define heater2_pin PA1
//#define fan_pin PA3

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3
#define NUMBUFFER 40
/*
  ============================================================================================
     BOARD_ST3DV1 XYYZ
  ============================================================================================
*/
#elif defined(BOARD_ST33DV1_XYYZ_STM32)

#define xenable PB9
#define xdirection PB7
#define xstep PB8

#define yenable PB9
#define ydirection PB5
#define ystep PB6

#define zenable PB9
#define zdirection PB3
#define zstep PB4

#define e0enable PB13
#define e0direction PB14
#define e0step PB15



#define limit_pin PB12


#define INVERTENDSTOP // uncomment for normally open

/*
  #define temp_pin PB1
  #define temp2_pin PB0
  #define fan_pin PA3
  #define heater2_pin PA1
*/
//#define heater_pin PA0
#define laser_pin PA0

//#define fan_pin PA0 // laser PIN

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3

#define NUMBUFFER 20
#define DRIVE_XYYZ
/*
  ============================================================================================
     BOARD_STM32 CNC ONLY
  ============================================================================================
*/
#elif defined(BOARD_STM32_CNC)

//#define xenable PB9
//#define xenable PA11
#define xdirection PB7
#define xstep PB8

//#define yenable PB9
#define ydirection PB5
#define ystep PB6

//#define zenable PB9
#define zdirection PB3
#define zstep PB4

//#define e0enable PB13
//#define e0direction PB14
//#define e0step PB15



#define limit_pin PB12
#define spindle_pin D8


//#define INVERTENDSTOP // uncomment for normally open

/*
  #define temp_pin PB1
  #define temp2_pin PB0
  #define fan_pin PA3
  #define heater2_pin PA1
*/
//#define heater_pin PA0
//#define laser_pin PA0

//#define fan_pin PA0 // laser PIN

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3

#define NUMBUFFER 20

/*
  ============================================================================================
     BOARD_ST33DV1_CNC_STM32
  ============================================================================================
*/
#elif defined(BOARD_ST33DV1_CNC_STM32)

//#define xenable PB9
#define xenable PA11
#define xdirection PB7
#define xstep PB8

#define yenable PB9
#define ydirection PB5
#define ystep PB6

#define zenable PB9
#define zdirection PB3
#define zstep PB4

#define e0enable PB13
#define e0direction PB14
#define e0step PB15



#define limit_pin PB12


#define INVERTENDSTOP // uncomment for normally open

/*
  #define temp_pin PB1
  #define temp2_pin PB0
  #define fan_pin PA3
  #define heater2_pin PA1
*/
#define heater_pin PA0
#define laser_pin PA0

//#define fan_pin PA0 // laser PIN

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3

#define NUMBUFFER 20

/*
  ============================================================================================
     BOARD_ST3DV1
  ============================================================================================
*/
#elif defined(BOARD_STM32F0)

//#define xenable PA4
#define xdirection PA4
#define xstep PA5

//#define yenable PA6
#define ydirection PA6
#define ystep PA7

//#define zenable PB9
#define zdirection PA9
#define zstep PA10

//#define e0enable PB9
#define e0direction PA9
#define e0step PA13
#define SHARE_EZ

#define limit_pin PA1

#define INVERTENDSTOP

//#define temp_pin PA0
//#define temp2_pin PB0
#define heater_pin PA0
//#define heater2_pin PA1
//#define fan_pin PA3

//#define SDCARD_CS PA4
//#define KBOX_PIN PA3
#define NUMBUFFER 20

/*
  ============================================================================================
     BOARD_GEN7
  ============================================================================================
*/
#elif defined(BOARD_GEN7)

#define xenable 25
#define xdirection 28
#define xstep 29

#define yenable 25
#define ydirection 26
#define ystep 27

#define zenable 25
#define zdirection 22
#define zstep 23

#define e0enable 25
#define e0direction 18
#define e0step 19

// this doesnot work anymore, please link all pin to xmin_pin
//#define xmin_pin 0
//#define ymin_pin 1
//#define zmin_pin 2
#define limit_pin 0

#define temp_pin A1 //analog 1
#define heater_pin 4
/*
  ============================================================================================
     BOARD_CHCSHIELDV3
  ============================================================================================
*/
#elif defined(BOARD_CHCSHIELDV3)

#define xenable 8
#define xdirection 5
#define xstep 2

#define yenable 8
#define ydirection 6
#define ystep 3

#define zenable 8
#define zdirection 7
#define zstep 4

//#define e0enable 8  // set the jumper for 4th motor https://blog.protoneer.co.nz/arduino-cnc-shield-v3-00-assembly-guide/#4THAXIS
//#define e0direction 13
//#define e0step 12

#define limit_pin 9


//#define temp_pin 0 //analog 0, on pin ABORT
//#define heater_pin A3 // on pin SPINDLE
#define laser_pin 12 // on pin SPINDLE
#define NUMBUFFER 12

/*
  ============================================================================================
     BOARD_RAMP1.3 MEGA ramps 1.4 is same ??
  ============================================================================================
*/
#elif defined(BOARD_RAMP13_DELTA)

#define xenable 38
#define xdirection 55
#define xstep 54

#define yenable 56
#define ydirection 61
#define ystep 60

#define zenable 62
#define zdirection 48
#define zstep 46

#define e0enable 24
#define e0direction 28
#define e0step 26



//#define xmin_pin 3
//#define ymin_pin 14
//#define zmin_pin 18

// this doesnot work anymore, please link all pin to xmax_pin
#define limit_pin 2

#define temp_pin A13
#define heater_pin 10

#define fan_pin 9
#define DRIVE_DELTA
#undef ISRTEMP // 120bytes check board.h
//#define INVERTENDSTOP // uncomment for normally open
#define NUMBUFFER 10
#define USETIMER1

/*
  ============================================================================================
     BOARD_RAMP1.3 MEGA ramps 1.4 is same ??
  ============================================================================================
*/
#elif defined(BOARD_RAMP13)

#define xenable 38
#define xdirection 55
#define xstep 54

#define yenable 56
#define ydirection 61
#define ystep 60

#define zenable 62
#define zdirection 48
#define zstep 46

#define e0enable 24
#define e0direction 28
#define e0step 26



//#define xmin_pin 3
//#define ymin_pin 14
//#define zmin_pin 18

#define limit_pin 2

#define temp_pin 13
#define heater_pin 10

#define fan_pin 9
#define NUMBUFFER 16
/*
  ============================================================================================
     BOARD_RAMP1.3 MEGA ramps 1.4 is same ??
  ============================================================================================
*/
#elif defined(BOARD_RAMP13_3DPLEX)

#define xenable 38
#define xdirection 55
#define xstep 54

#define yenable 56
#define ydirection 61
#define ystep 60

#define zenable 62
#define zdirection 48
#define zstep 46

#define e0enable 24
#define e0direction 28
#define e0step 26

#define limit_pin 2

#define temp_pin A13
#define heater_pin 10

#define fan_pin 9

/*
  ============================================================================================
     BOARD_SEMEDIY128AU
  ============================================================================================
*/
#elif defined(BOARD_SEMEDIY128AU)

#define xenable 43//50
#define xstep 42//49
#define xdirection 44 // 51

#define yenable 40//47
#define ystep 39//46
#define ydirection 38//44

#define zenable 33//40
#define zstep 31//38
#define zdirection 29//36

#define e0enable 28//35
#define e0step 30//37
#define e0direction 24//31


#define limit_pin 13
//#define temp_pin A6
//#define heater_pin 3

/*
   /
  ============================================================================================
     BOARD_SEMEDIY128AU
  ============================================================================================
*/
#elif defined(BOARD_SEMEDIYNANO)

#define xenable 13
#define xdirection 11
#define xstep 12

#define yenable 4
#define ydirection 2
#define ystep 3

#define zenable A2
#define zdirection A0
#define zstep A1

#define e0enable A5
#define e0direction A3
#define e0step A4


#define limit_pin 7

#define temp_pin 6
#define heater_pin 10
/*
  ============================================================================================
     ESP01CNC_V1
  ============================================================================================
*/
#elif defined(BOARD_ESP01CNC_V1)

#define xenable D1
#define xdirection D2
#define xstep D3
#define yenable D1
#define ydirection D2
#define ystep D3
#define zenable D1
#define zdirection D2
#define zstep D3

#define limit_pin D5

#define temp_pin A0
#define heater_pin D6
/*
  ============================================================================================
     NANONANO_WEMOS
  ============================================================================================
*/
#elif defined(BOARD_NANONANO_WEMOS)

// shift register for all motor step and direction (8 pin)
#define USE_SHIFTREG
#define pinclock D5
#define pinlatch D0
#define pindata D2

// Implemented shift register pin for motors
#define xdirection 6
#define xstep 7
#define ydirection 4
#define ystep 5
#define zdirection 3
#define zstep 2
#define e0direction 0
#define e0step 1


#define xenable D3
#define yenable D3
#define zenable D3
#define e0enable D3

#define limit_pin D1

#define temp_pin A0
#define heater_pin D4
#define fan_pin D4

#define INVERTENDSTOP
//#define SDCARD_CS D8
#define NUMBUFFER 20
/*
  ============================================================================================
     _WEMOS3D
  ============================================================================================
*/
#elif defined(BOARD_WEMOS3D)

#define xdirection D5
#define xstep D4
#define ydirection D7
#define ystep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection D6
#define zstep D0
#define e0direction D6
#define e0step D2

#define limit_pin D8

#define temp_pin A0
#define heater_pin D1

//#define INVERTENDSTOP
#define NUMBUFFER 30
#define SHARE_EZ

/*
  ============================================================================================
     _WEMOS3D
  ============================================================================================
*/
#elif defined(BOARD_WEMOS_CNC_XZYY)
#define INDEX "index.html"

// motor will be X->X board  Z->Y board Y1->Zboard Y2->EBoard

#define xdirection D5
#define xstep D4
#define zdirection D7
#define zstep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define ydirection D6
#define ystep D0

#define e0direction D6
#define e0step D2

#define limit_pin D8

#define temp_pin A0
#define heater_pin D1

//#define INVERTENDSTOP
#define NUMBUFFER 20
#define DRIVE_XZY2
/*
  ============================================================================================
     _WEMOS3D
  ============================================================================================
*/
#elif defined(BOARD_WEMOS3D_COREXY)

#define xdirection D5
#define xstep D4
#define ydirection D7
#define ystep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection D6
#define zstep D0
#define e0direction D6
#define e0step D2

#define limit_pin D8

//#define temp_pin A0
#define heater_pin D1

//#define INVERTENDSTOP
#define NUMBUFFER 20
#define DRIVE_COREXY
#define SHARE_EZ

/*
  ============================================================================================
     _WEMOS3D
  ============================================================================================
*/
#elif defined(BOARD_ESPUNO_COREXY)

#define xdirection D5
#define xstep D2
#define ydirection D6
#define ystep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection D7
#define zstep D4
//#define e0direction D6
//#define e0step D2

#define limit_pin D8

//#define temp_pin A0
#define heater_pin D1

//#define INVERTENDSTOP
#define NUMBUFFER 50
#define DRIVE_COREXY
//#define SHARE_EZ

/*
  ============================================================================================
     _WEMOS3D
  ============================================================================================
*/
#elif defined(BOARD_WEMOSCNC)

#define xdirection D5
#define xstep D4
#define ydirection D7
#define ystep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection D6
#define zstep D0
//#define e0direction D6
//#define e0step D2

#define limit_pin D8

//#define temp_pin A0
//#define heater_pin D1
//#define heater_pin D1
#define laser_pin D1
#define spindle_pin D8
//#define INVERTENDSTOP
#define NUMBUFFER 20

//#define IR_KEY D2
//#define IR_OLED_MENU 0x3c, RX, TX
/*
  ============================================================================================
     _WEMOS_CNC_ONLY
  ============================================================================================
*/
#elif defined(BOARD_WEMOSCNC_ONLY)
#define INDEX "/cnc.html"
#define xdirection D6
#define xstep D0
#define ydirection D7
#define ystep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection D5
#define zstep D4
//#define e0direction D6
//#define e0step D2

#define limit_pin D8

//#define temp_pin A0
//#define heater_pin D1
//#define heater_pin D1
//#define laser_pin D1
#define spindle_pin D8
#define AC_SPINDLE // 
//#define INVERTENDSTOP
#define NUMBUFFER 20

//#define IR_KEY D2
#define LCD_OLED
#define IR_OLED_MENU 0x3c, RX, TX
//#define IR_OLED_MENU 0x3c, RX, D1

#define XSTEPPERMM 229.335//50//105.090//50//131//178
#define YSTEPPERMM 194.053////105.090//50//175//125
#define ZSTEPPERMM 3072//2300//80//1020//1020 //420
#define E0STEPPERMM 100//92//340//380
#define XYJERK 0
#define XYCORNER 15
#define XACCELL 150
#define XMAXFEEDRATE 30
#define YMAXFEEDRATE 30
#define ZMAXFEEDRATE 4
#define E0MAXFEEDRATE 4
#define MOTOR_X_BACKLASH 0200  // 0.2 // MOTOR 0 = X, 1= Y 2=Z 3=E
#define MOTOR_Y_BACKLASH 0200
#define MOTOR_Z_BACKLASH 0
#define MOTOR_E_BACKLASH 0
#define LSCALE 1 // Spindle power calibration
/*
  ============================================================================================
     _WEMOS_CNC_ONLY
  ============================================================================================
*/
#elif defined(BOARD_WEMOSCNC_ONLY_V2)
#define INDEX "/cnc.html"
#define xdirection D5
#define xstep D6

#define zdirection D0
#define zstep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define ydirection D7
#define ystep D4
//#define e0direction D6
//#define e0step D2

#define limit_pin D8

//#define temp_pin A0
//#define heater_pin D1
//#define heater_pin D1
#define LASERON HIGH
#define laser_pin D1
#define spindle_pin D8
#define AC_SPINDLE // 
//#define INVERTENDSTOP
#define NUMBUFFER 20

//#define IR_KEY D2
#define LCD_OLED
#define IR_OLED_MENU 0x3c, RX, TX
//#define IR_OLED_MENU 0x3c, RX, D1

#define XSTEPPERMM 229.335//50//105.090//50//131//178
#define YSTEPPERMM 194.053////105.090//50//175//125
#define ZSTEPPERMM 3072//2300//80//1020//1020 //420
#define E0STEPPERMM 100//92//340//380
#define XYJERK 0
#define XYCORNER 15
#define XACCELL 150
#define XMAXFEEDRATE 30
#define YMAXFEEDRATE 30
#define ZMAXFEEDRATE 4
#define E0MAXFEEDRATE 4
#define MOTOR_X_BACKLASH 0200  // 0.2 // MOTOR 0 = X, 1= Y 2=Z 3=E
#define MOTOR_Y_BACKLASH 0200
#define MOTOR_Z_BACKLASH 0
#define MOTOR_E_BACKLASH 0
#define LSCALE 1 // Spindle power calibration
/*
  ============================================================================================
     _WEMOSLASER
  ============================================================================================
*/
#elif defined(BOARD_WEMOS_XYY_LASER)

#define xdirection D5
#define xstep D4
#define ydirection D7
#define ystep D3

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection D6
#define zstep D0
#define e0direction D6
#define e0step D2

#define limit_pin D8

//#define temp_pin A0
//#define heater_pin D1
#define laser_pin D1

//#define INVERTENDSTOP
#define DRIVE_XYYZ
#define NUMBUFFER 20
/*
  ============================================================================================
     _ESP32VN3D
  ============================================================================================
*/
#elif defined(BOARD_ESP32VN3D)

#define xdirection 36
#define xstep 39
#define ydirection 34
#define ystep 35

// z and e have same direction pin, we think that normally slicer never move z and e together.. we hope we right :D
#define zdirection 32
#define zstep 33
#define e0direction 25
#define e0step 26

#define limit_pin 27

//#define temp_pin 0
#define heater_pin 14
#define laser_pin 14

#define INVERTENDSTOP
#define NUMBUFFER 50
/*
  ============================================================================================
     NANONANO_WEMOS
  ============================================================================================
*/
#elif defined(BOARD_MINICNC_ESP01)

// shift register for all motor step and direction (8 pin)
#define USE_SHIFTREG
#define RX 3
#define TX 1
#define D0 16
#define D1 5

#define pinclock TX
#define pinlatch D0
#define pindata D1
#define limit_pin RX


// Implemented shift register pin for motors
#define xdirection 1
#define xstep 2
#define ydirection 6
#define ystep 5
#define zdirection 4
#define zstep 7
//#define e0direction 0
//#define e0step 1
#define laser_pin 0
//#define heater_pin 0

#define xenable 3
#define yenable 3
#define zenable 3
#define e0enable 3


#define ENABLEWIFI 10
#define DISABLESERIAL
#define INVERTENDSTOP
#define NUMBUFFER 20
#else
#warning No BOARD Defined !
#endif

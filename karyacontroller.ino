
//#define timing
//#define timingG
#define echoserial

#include "config_pins.h"
#include "common.h"
#include "gcode.h"
#include "temp.h"
#include "timer.h"
#include "eprom.h"
#include "motion.h"

#include<stdint.h>

int line_done, ack_waiting = 0;
int ct = 0;
uint32_t gt = 0;
int n = 0;

int sdcardok = 0;
#if defined(USE_SDCARD) && defined(SDCARD_CS)
// generic sdcard add about 800uint8_t ram and 8kb code
#include <SPI.h>
#include "SdFat.h"
SdFat sd;
// SD card chip select pin.
const uint8_t SD_CS_PIN = SDCARD_CS;

File myFile;
void demoSD() {
  if (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
    zprintf(PSTR("SDFAIL\n"));
    sdcardok = 0;
    return;
  }
  zprintf(PSTR("SDOK\n"));

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  // re-open the file for reading:
  myFile = sd.open("print.gcode");
  if (myFile) {
    zprintf(PSTR("gcode ok\n"));
    sdcardok = 1;
  } else {
    zprintf(PSTR("no gcode\n"));
  }
}
#endif

void gcode_loop() {
  //float x=12.345;
  //xprintf(PSTR("Motion demo %d %f\n"),10,x);
  //delay(500);
  //demo();
#ifndef ISPC
#ifdef timing
  uint32_t t1 = micros();
#endif
  if (motionloop())
  {
#ifdef timing
    uint32_t t2 = micros();
    if (ct++ > 1000) {
      ct = 0;
      zprintf(PSTR("%dus\n"), t2 - t1);
    }
#endif
  }
  if (ack_waiting) {
    zprintf(PSTR("ok\n"));
    ack_waiting = 0;
    n = 1;
  }
  char c = 0;
  if (Serial.available() > 0)
  {
    if (n) {
      gt = micros();
      n = 0;
    }
    c = Serial.read();
  }
#ifdef USE_SDCARD
  if (sdcardok) {
    // read from the file until there's nothing else in it:
    if (myFile.available()) {
      c = myFile.read();
    } else {
      // close the file:
      myFile.close();
      sdcardok = 0;
      zprintf(PSTR("Done\n"));
      c=0;
    }
  }
#endif

  if (c) {
#ifdef echoserial
    Serial.write(c);
#endif
    line_done = gcode_parse_char(c);
    if (line_done) {
      ack_waiting = line_done - 1;
#ifdef timingG
      zprintf(PSTR("Gcode:%dus\n"), fi(micros() - gt));
#endif
    }
  }
#else
#endif

}

void setup() {
  // put your setup code here, to run once:
  //  Serial.setDebugOutput(true);
  Serial.begin(115200);//115200);
  //while (!Serial.available())continue;
#ifdef USE_SDCARD
  demoSD();
#endif
  initmotion();
  init_gcode();
  init_temp();
  reload_eeprom();
  zprintf(PSTR("start\nok\n"));

  //zprintf(PSTR("Motion demo\nok\n"));

}

void loop() {
  //demo();
  gcode_loop();
  /*  if (feedthedog()){
      float f=123.456;
      int32_t i=1234;
      xprintf("%f",ff(f),i);
    }
  */
}

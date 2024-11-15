
// please do not use D8 on esp8266 / wemos. IR not work there.

#include "common.h"

#ifdef IR_KEY

#include <math.h>
#include "timer.h"
#include "temp.h"

#include <stdint.h>

#include "gcodesave.h"
#include "IRremote.h"
#include "ir_remote.h"
#include "ir_oled.h"
CNec IRLremote;
bool IR_ok;
int thc_ofs0=0;
int wait_job = 0;
int wait_spindle = 0;
String jobnum;
void IR_setup() {
  IR_ok = IRLremote.begin(IR_KEY);
  //if (IR_ok) zprintf(PSTR("IR Key OK.\n"));
}
void IR_end() {
  IRLremote.end(IR_KEY);
  IR_ok = 0;
}
bool canrepeat(int n){
	return (n == IRK4_OK ||
	    n == IRK4_UP ||
	    n == IRK4_DN ||
	    n == IRK4_LF ||
	    n == IRK4_RG ||
	    n == IRK4_DN ||
	    n == IRK4_1 ||
	    n == IRK4_7 ||
	    n == IRK4_3 ||
	    n == IRK4_9 
	    /* || 
	    (menu_index==99 && (
			n == IRK4_4 ||
			n == IRK4_6 ||
			n == IRK4_8 ||
			n == IRK4_2 	    
			)
	    )*/
	    );
}

extern void wifi_push(char c); // we use WIFI GCODE Command buffer to inject gcode
const char *gc92 = "G92\n";
int test1 = 0;
extern int tmul;

int lok, lad, rep;
uint32_t lastIR;
THEISR int getRemoteKey() {
  // put your main code here, to run repeatedly:
  extern uint32_t cm;
  if (IRLremote.available())
  {
    auto data = IRLremote.read();
    int ok = data.command & 255;
    int ad = data.address & 255;
    if (ok == 0 && ad == 255)
    {
	  if (!canrepeat((lad * 256) + lok))return 0;
      if (cm - lastIR < 200000)return 0;
      rep++;
    } else {
      lastIR = cm;
      rep = 1;
      lok = ok;
      lad = ad;
    }
    return (lad * 256) + lok;
  }
  return 0;
}

uint32_t lastirok = 0;
int tmul = 100;
int rmkey;
extern uint32_t cm; // check micros
void IR_loop(int mode = 0) {
  if (cm - lastirok > 10000000) {
    lastirok = cm;
    IR_end();
    IR_setup();
    return;
  }
  if (!IR_ok)return;
  int xcmd = getRemoteKey();

  if (xcmd)
  {
    lastirok = cm;
    rmkey = xcmd;
    int ok = ir_oled_loop(xcmd);
    if (ok)return; // the key is consumed by the display
    //zprintf(PSTR("Key:%d \n"),fi(data.command));
    extern int8_t RUNNING;
    extern int uncompress;
    // if not uncompress/running internal Gcode, we can JOG
    if (!uncompress) {
      // JOG

      float x, y, z;
      x = 0;
      y = 0;
      z = 0;

      // jog on arrow key = small incremental
      switch (xcmd) {
        case IRK_UP: case IRK4_UP: // UP key
          y = -1; break;
        case IRK_LF: case IRK4_LF: // LEFT key
          x = -1; break;
        case IRK_RG: case IRK4_RG: // RIGHT key
          x = 1;  break;
        case IRK_DN: case IRK4_DN: // DOWN key
          y = 1;  break;
      }
      // if not waiting job id (* followed by number), we can use number as fast jog and Z jog
      if (!(wait_job || wait_spindle))
        switch (xcmd) {
          case IRK_1: case IRK4_1: z = 1; break;
          case IRK_7: case IRK4_7: z = -1; break;
          case IRK_3: case IRK4_3: z = 0.5; break;
          case IRK_9: case IRK4_9: z = -0.5; break;
          case IRK4_ZUP: z = 0.25; break;
          case IRK4_ZDN: z = -0.25; break;
          case IRK_5: case IRK4_5: tmul = tmul == 100 ? 500 : 100; break;


          case IRK_2: case IRK4_2: y = -10; break;
          case IRK_4: case IRK4_4: x = -10; break;
          case IRK_6: case IRK4_6: x = 10; break;
          case IRK_8: case IRK4_8: y = 10; break;
          case IRK_OK: case IRK4_OK: // sethome pos
            for (int i = 0; i < strlen(gc92); i++) wifi_push(gc92[i]);
            break;
          case IRK_0: case IRK4_0: // 0 = home return
            /*addmove(100, 0, 0, 10, 0, 1, 1);
              addmove(100, 0, 0, 10, 0, 1, 0);
              addmove(100, 0, 0, 0, 0, 1, 0);
            */
            return;
        }

      addmove(100, x * tmul * 0.01, y * tmul * 0.01, z, 0, 1, 1);
      switch (xcmd) {
        case IRK_H: case IRK4_H: //#
            wait_spindle = 1;

          break;
      }

    } else {
      // special when uncompress/runnning

      switch (xcmd) {

        case IRK4_STOP: //* stop
          extern int ispause;
          ispause = ispause ? 0 : 1;
          return;
        case IRK_H: case IRK4_H:
          wait_spindle = 1;	break;
        // baby step is change the XYZ small value while its running job
        #ifdef PLASMA_MODE
        case IRK_1: case IRK4_1: thc_ofs0 += 20; break;
        case IRK_7: case IRK4_7: thc_ofs0 -= 20; break;
        case IRK_3: case IRK4_3: thc_ofs0 += 10; break;
        case IRK_9: case IRK4_9: thc_ofs0 += -10; break;
        #else
        case IRK_1: case IRK4_1: babystep[2] += 250; break;
        case IRK_7: case IRK4_7: babystep[2] -= 250; break;
        case IRK_3: case IRK4_3: babystep[2] += 100; break;
        case IRK_9: case IRK4_9: babystep[2] += -100; break;
		#endif
        case IRK_2: case IRK4_2: babystep[1] -= 250; break;
        case IRK_8: case IRK4_8: babystep[1] += 250; break;
        case IRK_4: case IRK4_4: babystep[0] -= 250; break;
        case IRK_6: case IRK4_6: babystep[0] += 250; break;

        case IRK_UP: case IRK4_UP: babystep[1] -= 100; break;
        case IRK_DN: case IRK4_DN: babystep[1] += 100; break;
        case IRK_LF: case IRK4_LF: babystep[0] -= 100; break;
        case IRK_RG: case IRK4_RG: babystep[0] += 100; break;
      }

    }
    int num = -1;
    if (wait_job || wait_spindle  ) {
      switch (xcmd) {
        case IRK_1: case IRK4_1: num = 1; break;
        case IRK_2: case IRK4_2: num = 2; break;
        case IRK_3: case IRK4_3: num = 3; break;
        case IRK_4: case IRK4_4: num = 4; break;
        case IRK_5: case IRK4_5: num = 5; break;
        case IRK_6: case IRK4_6: num = 6; break;
        case IRK_7: case IRK4_7: num = 7; break;
        case IRK_8: case IRK4_8: num = 8; break;
        case IRK_9: case IRK4_9: num = 9; break;
        case IRK_0: case IRK4_0: num = 0; break;
      }
    }
    if (num >= 0) {
      if (wait_spindle) {
        set_pwm(num * 28.3);
        wait_spindle = 0;
        return;
      }
      else if (wait_job) {
        jobnum += num;
        wait_job++;
      }
    }

  } else {
    if (mode == 0)ir_oled_loop(0);
  }
}

#else
void IR_setup() {}
void IR_end() {}
void  IR_loop(int mode = 0) {}
#endif

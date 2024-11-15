#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include "common.h"
#include "timer.h"

long spindle_pwm = 0;
extern int lastS;
bool RPM_PID_MODE = false;


#ifdef RPM_COUNTER

	#include "pid.h"
	double rSetpoint, rInput, rOutput;

	//Specify the links and initial tuning parameters

	PID RPM_PID(&rInput, &rOutput, &rSetpoint, 8, 2, 12, DIRECT); //2, 5, 1, DIRECT);

	uint32_t rev = 0;
	uint32_t lastMillis = 0;
	uint32_t RPM = 0;
	int avgpw = 0;
	int avgcnt = 0;
	void THEISR isr_RPM() {
	  rev++;
	}

	uint32_t get_RPM() {
	  uint32_t milli = millis();
	  uint32_t delta = milli - lastMillis;
	  if (delta > 100) {
		lastMillis = milli;
		RPM = (rev * 60 * 1000 / delta);
		rev = 0;
		if (RPM_PID_MODE) {
		  rSetpoint = lastS * 100;
		  rInput = RPM;
		  RPM_PID.Compute();
		  if (lastS == 0)rOutput = 0;
		  avgpw = (avgpw + rOutput * 0.01);
		  avgcnt++;
	#ifdef AC_SPINDLE
		  spindle_pwm = 10000 - pow(rOutput * 0.0001, 2) * 10000;
	#else
		  spindle_pwm = rOutput;
	#endif
		}
	  }
	  return RPM;
	}
	void setup_RPM() {
	  attachInterrupt(digitalPinToInterrupt (RPM_COUNTER), isr_RPM, RISING);
	  lastMillis = millis();
	  RPM_PID.SetMode(AUTOMATIC);
	  RPM_PID.SetOutputLimits(0, 10000);
	}

	#endif



	uint32_t next_l = 0;
	bool spindle_state = LOW;
	int spindle_pct;

	//PWM Freq is 1000000/20000 = 50Hz , 20mms pulse
	// for servo, the LSCALE at least 10%



	#ifdef PCA9685
	#ifndef spindle_servo_pin
	#define spindle_servo_pin 2
	#endif
	// dont use classic PWM
	#undef spindle_pin
	#include "Wire.h"
	#include "Adafruit_PWMServoDriver.h"
	Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
	#define MIN_PULSE_WIDTH 600
	#define MAX_PULSE_WIDTH 2600
	#define FREQUENCY 50
	#define EQ_S (FREQUENCY*4096.0/1000000)
	#define EQ_A (EQ_S*MIN_PULSE_WIDTH)
	#define EQ_B (EQ_S*(MAX_PULSE_WIDTH-MIN_PULSE_WIDTH)/180.0)
	void setupPwm()
	{
	  Wire.begin(D2, D1);
	  Wire.setClock(700000);
	  pwm.begin();
	  pwm.setPWMFreq(FREQUENCY);
	  pwm.setPWM(8, 0, MIN_PULSE_WIDTH);
	}
	int pulseWidth(int angle)
	{
	  //int pulse_wide, analog_value;
	  //pulse_wide = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
	  //analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
	  return EQ_A + EQ_B * angle;
	}
	long lzc = 0;
	void setXYZservo(float x, float y, float z) {
	  //long m=millis();
	  //if (m-lzc>20){
	  //    lzc=m;
	  //pwm.setPWM(0, 0,pulseWidth(x)); // set 180 = 40mm then
	  //pwm.setPWM(1, 0,pulseWidth(y)); // set 180 = 40mm then
	  //pwm.setPWM(2, 0,pulseWidth((25+z)*4.5)); // set 180 = 40mm then
	  //}
	}
	#else

	#ifdef  ZERO_CROSS_PIN
	void THEISR zero_cross() {
	  in_pwm_loop = false;
	  next_l = micros();
	  spindle_state = LOW;
	  xdigitalWrite(spindle_pin, LOW);

	}
	#endif

	void setupPwm() {
	#ifdef  ZERO_CROSS_PIN
	  attachInterrupt(ZERO_CROSS_PIN, zero_cross, RAISING);
	#endif
	}
	int pulseWidth(int angle) {
	  return 0;
	}
	void setXYZservo(float x, float y, float z) {}
	// cannot use servo
	#undef servo_pin
#endif



bool in_pwm_loop = false;
void set_pwm(int v) { // 0-255
  if (v > 255)v = 255;
  if (v < 0)v = 0;
#ifdef PLASMA_MODE
	xdigitalWrite(spindle_pin,v>10);
#else  
	  next_l = micros();
	  {
		spindle_pct = v * 0.39; // 0 - 100
		//if (! RPM_PID_MODE)
		lastS = v;
		extern float Lscale;
		float vf;
		if (int(100 * Lscale) == 0) {
		  vf = v > 5 ? 0 : 255;
		} else {
		  vf = fabs(v * Lscale);
		}
		spindle_pwm = fmin(20000, vf * 39.216 * 2);
		if (Lscale >= 0)spindle_pwm = 20000 - spindle_pwm; // flip if inverse
	#ifdef spindle_pin
		xdigitalWrite(spindle_pin, LOW);
	#endif
	#ifdef PCA9685
		pwm.setPWM(spindle_servo_pin, 0, pulseWidth(0.009 * spindle_pwm)); // set 0 - 4095
		return;
	#endif
	  }
	  if (in_pwm_loop)return;
	#ifdef spindle_pin
	  pinMode(spindle_pin, OUTPUT);
	  //xdigitalWrite(spindle_pin, HIGH);
	#endif
#endif
}
void pause_pwm(bool v) {
  in_pwm_loop = v;
}

void THEISR pwm_loop() {
#ifndef PLASMA_MODE
	#ifdef RPM_COUNTER
	  get_RPM();
	#endif



	#ifdef spindle_pin
	  if (in_pwm_loop)return;
	  in_pwm_loop = true;
	  uint32_t pwmc = micros(); // next_l contain last time target for 50Hz
	  if ((pwmc - next_l > spindle_pwm)  && (spindle_pwm < 20000)) { // if  current time - next time > delta time pwm, then turn it on
		if (!spindle_state) {
		  spindle_state = HIGH;
		  xdigitalWrite(spindle_pin, HIGH);
		}
	  }

	  // if use zero_cross then in_pwm_loop will be true until a trigger happened
	  // basically replace all below using interrupt trigger
	#ifndef ZERO_CROSS_PIN
	  if (pwmc - next_l > 19999) { // 50hz on wemos then turn off
		next_l = pwmc;
		spindle_state = LOW;
		xdigitalWrite(spindle_pin, LOW);
	  }
	  in_pwm_loop = false;
	#endif
	#endif
#endif
}


void servo_set(int angle) {
#ifdef servo_pin
  pwm.setPWM(servo_pin, 0, spindle_pwm * 0.205); // set 0 - 4095
  return;
#endif
}
void servo_loop() {
  pwm_loop();
}

int somedelay(int32_t n)
{
  float f = 0;
  int m = 10;

  while (m--) {
    int nn = n;
    while (nn--) {
      f += n;
      asm("");
    }
  }
  return f + n;
}

//#define somedelay(n) delayMicroseconds(n);
int dogfeed = 0;

#include<Arduino.h>
#define dogfeedevery 2200 // loop
// ESP8266 specific code here


int feedthedog()
{
  if (dogfeed++ > dogfeedevery) {
    dogfeed = 0;
#if defined(ESP8266)
    // ESP8266 specific code here
    ESP.wdtFeed();
#elif defined(ESP32)
    //  esp_task_wdt_reset();
#else
#endif
    //zprintf(PSTR("Feed the dog\n"));
    return 1;
  }
  return 0;
}


// ======================== TIMER for motionloop =============================
#define timerPause()
#define timerResume()

int busy1 = 0;
volatile uint32_t ndelay = 0;
uint32_t next_step_time;

inline int THEISR timercode();
// -------------------------------------   ESP8266  ----------------------------------------------------------
#ifdef ESP8266
#define USETIMEROK
#define MINDELAY 100
#define usetmr1


void THEISR tm()
{
  noInterrupts();
  int d = timercode();

#ifdef usetmr1
  timer1_write(d < 6 ? 6 : d);
#else
  timer0_write(ESP.getCycleCount() + 16 * (d < 6 ? 6 : d));
#endif
  interrupts();
}

void timer_init()
{
  //Initialize Ticker every 0.5s
  noInterrupts();
#ifdef usetmr1
  timer1_isr_init();
  timer1_attachInterrupt(tm);
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  timer1_write(1000); //200 us
#else
  timer0_isr_init();
  timer0_attachInterrupt(tm);
  timer0_write(ESP.getCycleCount() + 16 * 1000); //120000 us
#endif
#ifdef RPM_COUNTER
  setup_RPM();
#endif
  setupPwm();
  set_pwm(0);
  interrupts();
}

#endif // esp8266
#ifdef ESP32
#define USETIMEROK
typedef struct {
  union {
    struct {
      uint32_t reserved0:   10;
      uint32_t alarm_en:     1;             /*When set  alarm is enabled*/
      uint32_t level_int_en: 1;             /*When set  level type interrupt will be generated during alarm*/
      uint32_t edge_int_en:  1;             /*When set  edge type interrupt will be generated during alarm*/
      uint32_t divider:     16;             /*Timer clock (T0/1_clk) pre-scale value.*/
      uint32_t autoreload:   1;             /*When set  timer 0/1 auto-reload at alarming is enabled*/
      uint32_t increase:     1;             /*When set  timer 0/1 time-base counter increment. When cleared timer 0 time-base counter decrement.*/
      uint32_t enable:       1;             /*When set  timer 0/1 time-base counter is enabled*/
    };
    uint32_t val;
  } config;
  uint32_t cnt_low;                             /*Register to store timer 0/1 time-base counter current value lower 32 bits.*/
  uint32_t cnt_high;                            /*Register to store timer 0 time-base counter current value higher 32 bits.*/
  uint32_t update;                              /*Write any value will trigger a timer 0 time-base counter value update (timer 0 current value will be stored in registers above)*/
  uint32_t alarm_low;                           /*Timer 0 time-base counter value lower 32 bits that will trigger the alarm*/
  uint32_t alarm_high;                          /*Timer 0 time-base counter value higher 32 bits that will trigger the alarm*/
  uint32_t load_low;                            /*Lower 32 bits of the value that will load into timer 0 time-base counter*/
  uint32_t load_high;                           /*higher 32 bits of the value that will load into timer 0 time-base counter*/
  uint32_t reload;                              /*Write any value will trigger timer 0 time-base counter reload*/
} xhw_timer_reg_t;

typedef struct xhw_timer_s {
  xhw_timer_reg_t * dev;
  uint8_t num;
  uint8_t group;
  uint8_t timer;
  portMUX_TYPE lock;
} xhw_timer_t;


hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;


void THEISR xtimerAlarmWrite(xhw_timer_s *timer, uint64_t alarm_value) {
  timer->dev->alarm_high = (uint32_t) (alarm_value >> 32);
  timer->dev->alarm_low = (uint32_t) alarm_value;
  timer->dev->config.autoreload = true;
  timer->dev->config.alarm_en = 1;
}

void THEISR tm() {
  portENTER_CRITICAL_ISR(&timerMux);
  int d = timercode();

  xtimerAlarmWrite((xhw_timer_s*)timer, d < 6 ? 6 : d);

  portEXIT_CRITICAL_ISR(&timerMux);
}

void timer_init()
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &tm, true);
  xtimerAlarmWrite((xhw_timer_s*)timer, 12000);
  //zprintf(PSTR("Time init\n"));
}

/*
  #undef timerPause()
  #undef timerResume()
  int tmrstack=0;
  void THEISR timerPause(){
  tmrstack++;
  if (tmrstack==1)((xhw_timer_s*) timer)->dev->config.alarm_en = 0;
  }
  void THEISR timerResume(){
  tmrstack--;
  if (tmrstack==0)((xhw_timer_s*) timer)->dev->config.alarm_en = 1;
  }
*/

#endif //esp32

// ======= the same code for all cpu ======


inline int THEISR timercode() {
  if (ndelay < 30000) {
    ndelay = MINDELAY;
    coreloopm();
  } else {
    ndelay -= 30000;
  }
  //pwm_loop();
  return ndelay >= 30000 ? 30000 : ndelay;
}

// ==============================================


// Laser constant burn timer
void THEISR timer_set(int32_t delay)
{
  ndelay = delay;
}




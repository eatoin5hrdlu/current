
#ifndef CURRENT_v1_h
#define CURRENT_v1_h
#define LIBRARY_VERSION	1.0.0
//
//  void setup_current(int c, int pin, int mA, int resistance, int deviceVoltage)
//  int get_current(int c);
//  void checkCurrent();
//

#include "Arduino.h"

class CURRENT
{
 public:
  CURRENT(int n) {
    int i;
    size = n;
    disabled = false;
    cycleCount = 0L;
    cycletime = DEFAULT_CYCLETIME*1000; // Cycle in seconds, store as ms
    lastcycle = millis();
  }

  // Current "c" uses PWM "pin" to produce mA into the "resistance" of "deviceVoltage"
  // The laser at position 0, (pin #) 3, 10 (mA), 75 (ohms), 3.9 (volts)
  // The OD600 LED at position 2, (pin #) 5, ~5(mA), 150 (ohms), 2.1 (volts)
  // The Meniscus green LED at 3, (pin #) 6, ~8(mA), 150 (ohms), 1.8 (volts)

  void setup_current(int c, int pin, int mA, int resistance, int deviceVoltage) {
    current_pin[c] = pin;
    current_value[c] = mA;
    current_r[c] = resistance;   // What is the current limiting resistor
    voltage[c] = deviceVoltage;   // What is the drop voltage of the device
  }

  int get_current(int c)
  {
    return (int) ((1100.0*(double) analogRead(analogPin[c]))/(1023.0*current_r[c]));
  }

  boolean checkCurrent(void) { /* Adjust PWM current sources as needed */
    int i, current;
    unsigned long now = millis();
    for ( i=0; i<CURRENT_NUM; i++ ) 
      {
	current = get_current(i);
	if (current < current_value[i])   current_pwm[i] = current_pwm[i]+1;
	if (current > current_value[i])   current_pwm[i] = current_pwm[i]-1;
	analogWrite(current_pin[i],current_pwm[i]);
      }
  }

 private:
  int size;                         // Number of positions
  long int cycleCount;
  int      current_pin[NUM_CURRENT+1];  // What PWM pin controls the current
  int      current_value[NUM_CURRENT+1];// What is the target current value
  int      current_pwm[NUM_CURRENT+1];  // What is the current PWM value
  int      current_r[NUM_CURRENT+1];    // What is the current limiting resistor
  float    voltage[NUM_CURRENT+1];      // What is the drop voltage of the device
  int      analogPin[NUM_CURRENT+1];    // Which Analog input is monitoring the current
  unsigned long lastcycle;  // Beginning of current time interval
  unsigned long cycletime; // Cycle duration (always > valve on time)
 } ;
#endif



// c&p https://github.com/adafruit/MAX6675-library/blob/master/max6675.h
// 5/20/19 austin@austindavid.com

// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple
/*
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
*/

#include "Particle.h"
#include <math.h>

class MAX6675 {
 public:
  MAX6675(int8_t SCLKpin, int8_t CSpin, int8_t MISOpin);

  double readCelsius(void);
  double readFahrenheit(void);
  // For compatibility with older versions:
  double readFarenheit(void) { return readFahrenheit(); }
 private:
  int8_t sclk, miso, cs;
  uint8_t spiread(void);
};

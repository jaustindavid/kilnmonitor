// This #include statement was automatically added by the Particle IDE.
#include "max6675.h"

// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

#include <Particle.h>
#include <math.h>

#define thermoDO    D6
#define thermoCS    D5
#define thermoCLK   D4
#define thermoVCC   D7

#define OLED_POWER  D3
#define OLED_GROUND D2
#define OLED_SCL    D1
#define OLED_SCA    D0


MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
Adafruit_SSD1306 display(-1);

double tempF = 0;

void setup() {
    power_setup();
    initDisplay();
    thermo_setup();

    banner(3, "Kiln\nMonitor");
    delay(500); 
    
    Particle.variable("temperature", tempF);
} // setup()


void loop() {
    display.clearDisplay();
    display.setCursor(0,32);
    display.setTextSize(2);
    tempF = thermocouple.readFahrenheit();
    justify(7, tempF, 2);
    display.print("F");
    display.display();
    delay(1000);
} // loop()


/*************************
 * 
 *  THERMOCOUPLE
 * 
 *************************/

void thermo_setup() {
    pinMode(thermoVCC, OUTPUT);
    digitalWrite(thermoVCC, HIGH);
    delay(500);
}

/*************************
 * 
 *  DISPLAY
 * 
 *************************/


void initDisplay() {
    display_power(HIGH);
    delay(500);           // NOT a cloud delay
    display.begin();
} // initDisplay()


void power_setup() {
    pinMode(OLED_POWER, OUTPUT);
    pinMode(OLED_GROUND, OUTPUT);
    digitalWrite(OLED_GROUND, LOW);
} // powerSetup()


void display_power(bool level) {
    if (level == HIGH) {
        digitalWrite(OLED_POWER, HIGH);
        // TODO: refresh the display
    } else {
        digitalWrite(OLED_POWER, LOW);
    }
} // display_power(level)


void banner(byte size, const char * buf) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    // display.setFont(COMICS_8);
    display.setTextSize(size);
    display.setCursor(0,0);
    display.print(buf);
    display.display();
    display.setCursor(0, 32);
    display.setTextSize(1);
} // banner(size, buf)


void justify(byte width, float value, byte decimals) {
  byte i;
  for (i = 0; i < decimals; i++) {
    value *= 10;
  }
  value = (int)value;
  for (i = 0; i < decimals; i++) {
    value /= 10;
  }

  // total = log10(value) + 1 + decimals
  byte spaces = 1;
  float working = value;
  if (working < 0) {
    working = working * -1;
    spaces += 1;
  }
  while (working >= 10) {
    ++spaces;
    working = working / 10;
  }

  if (decimals) {
    spaces += 1 + decimals;
  }

  
  if (spaces > width) {
    decimals = max(0, decimals - (spaces - width));

    if (decimals == 0) {
      spaces -= 3;
    }
  }
  
  for (; spaces < width; spaces ++) {
    display.print(F(" "));        
  }
  display.print(value, decimals);
} // justify(width, value, decimals)

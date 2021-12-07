#include "led.h"



LED::LED(int _pin,int _on_timeout=500,int _off_timeout=500) {
  on_timeout=0;
  off_timeout=0;
  on_timeout=_on_timeout;
  off_timeout=_off_timeout;
  pin = _pin;
  pinMode(pin, OUTPUT);
}

LED::LED(int _pin) {
  on_timeout=0;
  off_timeout=0;
  on_timeout=500;
  off_timeout=500;
  pin = _pin;
  pinMode(pin, OUTPUT);
}


LED::~LED() {

}


void LED::set_on_timeout(int t) {
  on_timeout = t;
}

void LED::set_off_timeout(int t) {
  off_timeout = t;
}

void LED::on() {
  on_start_time = millis();
  digitalWrite(pin, HIGH);
  led_state=true;
}

void LED::off() {
  off_start_time = millis();
  digitalWrite(pin, LOW);
  led_state=false;
}

void LED::run() {

  if ((on_start_time + on_timeout) < millis() && led_state)
    off();

  if ((off_start_time + off_timeout) < millis() && !led_state)
    on();
}

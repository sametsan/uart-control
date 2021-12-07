#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {

  private:
    int pin;
    unsigned long on_start_time;
    unsigned long off_start_time;
    int on_timeout;
    int off_timeout;
    bool led_state = false;

  public:
      void on();
    void off();
    LED(int pin, int _on_timeout, int _off_timeout);
    LED(int pin);
    ~LED();
    void set_on_timeout(int);
    void set_off_timeout(int);
    void run();



};


#endif

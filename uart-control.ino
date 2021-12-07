#include "debug.h"
#include "led.h"


#define USART_BAUDRATE 115200
#define LED_PIN 2
#define DEBUG_LED_PIN 3


String command;
LED led(LED_PIN);
bool echo_activation=true;


void command_parse(String command) {

  if (command.length() == 0) return;

  if (!command.compareTo("start")) {
    echo_activation = true;
    debugln("Echo started");
  }

  if (!command.compareTo("stop")) {
    echo_activation = false;
    debugln("Echo Stopped");
  }

  int index = command.indexOf('=');

  if (!command.substring(0, index).compareTo("ledon")) {
    int led_on_time = command.substring(index + 1).toInt();
    led.set_on_timeout(led_on_time);
    debug("Led on time = ");
    debugln(led_on_time);
  }

  if (!command.substring(0, index).compareTo("ledoff")) {
    int led_off_time = command.substring(index + 1).toInt();
    led.set_off_timeout(led_off_time);
    debug("Led off time = ");
    debugln(led_off_time);
  }


}

void setup() {
  // Serial select baudrate
  Serial.begin(USART_BAUDRATE);
}


void serialEvent() {

  // Command buffer clear
  command.remove(0,command.length());

  while (Serial.available()) {
    char ch = (char)Serial.read();

    // If command is end,break while
    if (ch == '\n')
       break;
     
    command += ch;
    delay(5);
  }

  command_parse(command);

  if (echo_activation)
    Serial.println(command.c_str());
    
}

void loop() {

  led.run();

}

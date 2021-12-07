#include "debug.h"
#include "led.h"

#define USART_BAUDRATE 115200
#define LED_PIN 2
#define DEBUG_LED_PIN 3


String command;
bool is_active_echo = true;

LED led(LED_PIN);
LED debug_led(DEBUG_LED_PIN);

void command_parse() {

  if (!command.compareTo("start")) {
    is_active_echo = true;
    debugln("Echo started");
  }

  if (!command.compareTo("stop")) {
    is_active_echo = false;
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

  // Command buffer clear
  command.remove(0, command.length());
}

void setup() {
  // Serial select baudrate
  Serial.begin(USART_BAUDRATE);

  // Pin mode select
  pinMode(3, OUTPUT);
}


void serialEvent() {
  debug_led.on();

  while (Serial.available()) {
    char ch = (char)Serial.read();

    // If command is end,break while
    if (ch == '\n')
      break;
    command += ch;
  }

  command_parse();

  if (is_active_echo)
    Serial.println(command.c_str());

  debug_led.off();
}

void loop() {

  led.run();


}

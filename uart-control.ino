#include "debug.h"

#define USART_BAUDRATE 9600


int timeout = 300;
String command;
bool is_active_echo = true;

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
    timeout = command.substring(index + 1).toInt();
    debug("Led on time = ");
    debugln(timeout);
  }

  if (!command.substring(0, index).compareTo("ledoff")) {
    timeout = 1000 - command.substring(index + 1).toInt();
    debug("Led off time = ");
    debugln(1000 - timeout);
  }

  // Command buffer clear
  command.remove(0, command.length());
}

void setup() {
  // Serial select baudrate
  Serial.begin(USART_BAUDRATE);

  // Pin mode select
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}


void serialEvent() {
  digitalWrite(3, HIGH);

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

  digitalWrite(3, LOW);
}

void loop() {



  digitalWrite(2, LOW);
  delay(1000 - timeout);
  digitalWrite(2, HIGH);
  delay(timeout);

}

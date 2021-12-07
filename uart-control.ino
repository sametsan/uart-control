#define USART_BAUDRATE 9600

int timeout = 300;
String command;
bool is_active_echo = true;

void command_parse() {

  if (command.length() == 0)
    return;

  if (!command.compareTo("start")) {
    is_active_echo = true;
    Serial.println("Echo started");
  }

  if (!command.compareTo("stop")) {
    is_active_echo = false;
    Serial.println("Echo Stopped");
  }

  int index = command.indexOf('=');

  if (!command.substring(0, index).compareTo("ledon")) {
    timeout = command.substring(index + 1).toInt();
    Serial.print("Led on time = ");
    Serial.println(timeout);
  }

  if (!command.substring(0, index).compareTo("ledoff")) {
    timeout = 1000 - command.substring(index + 1).toInt();
    Serial.print("Led off time = ");
    Serial.println(1000 - timeout);
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

  if (is_active_echo)
    Serial.println(command.c_str());

  digitalWrite(3, LOW);
}

void loop() {

  command_parse();

  digitalWrite(2, LOW);
  delay(1000 - timeout);
  digitalWrite(2, HIGH);
  delay(timeout);

}

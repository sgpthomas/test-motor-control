#include <EEPROM.h>

// identity
String id = "";

// variables
int LED = 13;

// response
String estCall = "? listen _";
String estResponse = "$ listen yes";

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  Serial.setTimeout(250);
  pinMode(LED, OUTPUT);
  
  id = rememberID();
}

void serialEvent() {
  if (Serial.available()) {
    String symbol = Serial.readStringUntil(' ');
    String command = Serial.readStringUntil(' ');
    String info = Serial.readStringUntil('\n');
    receivedMessage(symbol, command, info);
    // digitalWrite(LED, HIGH);
    // delay(500);
    // digitalWrite(LED, LOW);
  }
}

void receivedMessage(String symbol, String command, String info) {  
  if (symbol == "?") {
    if (command == "listen") {
      Serial.println(estResponse);
      
    } 
    
    else if (command == "id") {
      Serial.println("$ id " + id);
    }
  }
  
  if (symbol == "!") {
    if (command == "set_id") {
      id = info;
      setID(info);
      Serial.println("# set_id " + info);
    }
  }
}

String rememberID() {
  char value;
  int address = 0;
  String id = "";
  while (true) { // loop
    value = EEPROM.read(address);
    
    if (value != 0) { // value is not null
      id += value;
    } else {
      break;
    }
    
    address++;
  }
  
  return id;
}

void setID(String id) {
  clearMem();
  for (int i = 0; i < id.length(); i++) {
    EEPROM.write(i, id[i]);
  }
}

void clearMem() {
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }  
}

int address = 0;
byte value;
boolean l = true;

// the loop function runs over and over again forever
void loop() {

}



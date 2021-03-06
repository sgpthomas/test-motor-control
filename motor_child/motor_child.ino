#include <EEPROM.h>

// identity
String id = "";

// variables
int LED = 13;

// version number
String version_number = "0.1";

// is streaming?
bool stream = false;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
//  Serial.setTimeout(250);/
  pinMode(LED, OUTPUT);
  
  id = rememberID();
}

void serialEvent() {
  if (Serial.available() && !stream) {
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
//  if (symbol == "?") {
//    if (command == "listen") {
//      Serial.println(estResponse);
//      
//    } 
//    
//    else if (command == "id") {
//      Serial.println("$ id " + id);
//    }
//  }
//  
//  if (symbol == "!") {
//    if (command == "id") {
//      id = info;
//      setID(info);
//      Serial.println("# id " + info);
//    }
//  }

  if (command == "version") {
    Serial.println("$ version " + version_number);
  }

  else if (command == "id") {
    if (symbol == "?") { // asking for id
      Serial.println("$ id " + id);
    } 
    
    else if (symbol == "!") { // set id
      id = info;
      setID(info);
      Serial.println("# id " + info);
    }
  }

  else if (command == "move") {
    if (symbol == "!") { // move and open data stream
      stream = true;
      Serial.println("> move " + info);
      delay(100);
      for (int i = 0; i < info.toInt(); i++) {
        Serial.println(i);
        // delay(200);
      }
      Serial.println("/ move " + info);
      stream = false;
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



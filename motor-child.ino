
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
}

void serialEvent() {
  if (Serial.available()) {
    String symbol = Serial.readStringUntil(' ');
    String command = Serial.readStringUntil(' ');
    String info = Serial.readStringUntil('\n');
    receivedMessage(symbol, command, info);
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
      Serial.println("# set_id " + info);
    }
  }
}

// the loop function runs over and over again forever
void loop() {

}



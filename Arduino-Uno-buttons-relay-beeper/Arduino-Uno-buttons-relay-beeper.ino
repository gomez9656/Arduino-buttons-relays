//Define pins
#define button1 2
#define button2 3
#define button3 4
#define button4 5

#define relay   13
#define beeper 14

//define time duration in ms
#define time1   1000
#define time2   2000
#define time3   3000
#define time4   4000

//function declaration
void checkButton(int button);
void updateState(int button);
void trigger_relay(int button);
void programming_mode();

int buttonState = 0;      // current state of the button
int lastButtonState = 0;  // previous state of the button
int startPressed = 0;     // the moment the button was pressed
int endPressed = 0;       // the moment the button was released
int holdTime = 0;         // how long the button was hold
int idleTime = 0;         // how long the button was idle

void setup() {

  Serial.begin(9600);
  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  
  pinMode(relay, OUTPUT);
  pinMode(beeper, OUTPUT);
}

void loop() {

  checkButton(button1);
  checkButton(button2);
  checkButton(button3);
  checkButton(button4);
}

/*
 * check the button status. If the status changed, then update the status
 */
void checkButton(int button) {

  buttonState = digitalRead(button);

  if (buttonState != lastButtonState) { // button state changed
    updateState(button);
  }

  lastButtonState = buttonState;        // save state for next loop
}

/*
 * start measuring the time the button was pressed.
 * if the status changed, then calculate the time the button was pressed
 */
void updateState(int button){

  if (buttonState == HIGH){          // the button has been just pressed
    startPressed = millis();
  }
  else{                              // the button has been just released
    endPressed = millis();
    holdTime = endPressed - startPressed;

    if (holdTime < 2000) {
      Serial.println("Button was held for less than two second");
      trigger_relay(button);
    }

    if (holdTime >= 2000) {
      Serial.println("Button was held for two second or more");
      programming_mode();
    }
  }
}

void trigger_relay(int button){
  
  if(button == button1){
    digitalWrite(relay, HIGH);
    delay(time1);
    digitalWrite(relay, LOW);
  }
  else if(button == button2){
    digitalWrite(relay, HIGH);
    delay(time2);
    digitalWrite(relay, LOW);
  }
  else if(button == button3){
    digitalWrite(relay, HIGH);
    delay(time3);
    digitalWrite(relay, LOW);
  }
  else if(button == button4){
    digitalWrite(relay, HIGH);
    delay(time4);
    digitalWrite(relay, LOW);
  }
}

void programming_mode(){
  digitalWrite(beeper, HIGH);
}

//Define button, relay, and beeper pins
#define button1 8
#define button2 9
#define button3 10
#define button4 11
#define relay   12
#define beeper  13

//define time duration for each button in ms
uint16_t time1 = 1000;
uint16_t time2 = 2000;
uint16_t time3 = 3000;
uint16_t time4 = 4000;

//functions declaration
void checkButton1();
void updateState1();
void checkButton2();
void updateState2();
void checkButton3();
void updateState3();
void checkButton4();
void updateState4();

int buttonState1 = 0;      // current state of the button
int lastButtonState1 = 0;  // previous state of the button
int startPressed1 = 10;     // the moment the button was pressed
int endPressed1 = 0;       // the moment the button was released
int holdTime1 = 0;         // how long the button was hold
int idleTime1 = 0;         // how long the button was idle

int buttonState2 = 0;      // current state of the button
int lastButtonState2 = 0;  // previous state of the button
int startPressed2 = 10;     // the moment the button was pressed
int endPressed2 = 0;       // the moment the button was released
int holdTime2 = 0;         // how long the button was hold
int idleTime2 = 0;         // how long the button was idle

int buttonState3 = 0;      // current state of the button
int lastButtonState3 = 0;  // previous state of the button
int startPressed3 = 10;     // the moment the button was pressed
int endPressed3 = 0;       // the moment the button was released
int holdTime3 = 0;         // how long the button was hold
int idleTime3 = 0;         // how long the button was idle

int buttonState4 = 0;      // current state of the button
int lastButtonState4 = 0;  // previous state of the button
int startPressed4 = 10;     // the moment the button was pressed
int endPressed4 = 0;       // the moment the button was released
int holdTime4 = 0;         // how long the button was hold
int idleTime4 = 0;         // how long the button was idle


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //set inputs and outputs
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  pinMode(relay, OUTPUT);
  pinMode(beeper, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  checkButton1();
  checkButton2();
  checkButton3();
  checkButton4();
}

void checkButton1() {

  buttonState1 = digitalRead(button1);

  if (buttonState1 != lastButtonState1) { // button state changed
    updateState1();
  }

  lastButtonState1 = buttonState1;        // save state for next loop
}

/*
   start measuring the time the button was pressed.
   if the status changed, then calculate the time the button was pressed
*/
void updateState1() {

  if (buttonState1 == HIGH) {         // the button has been just pressed
    startPressed1 = millis();
  }
  else {                             // the button has been just released
    endPressed1 = millis();
    holdTime1 = endPressed1 - startPressed1;

    if (holdTime1 < 2000) {

      trigger_relay(button1);
    }

    if (holdTime1 >= 2000) {

      //programming_mode(button);
    }
  }
}

void checkButton2() {

  buttonState2 = digitalRead(button2);

  if (buttonState2 != lastButtonState2) { // button state changed
    updateState2();
  }

  lastButtonState2 = buttonState2;        // save state for next loop
}

/*
   start measuring the time the button was pressed.
   if the status changed, then calculate the time the button was pressed
*/
void updateState2() {

  if (buttonState2 == HIGH) {         // the button has been just pressed
    startPressed2 = millis();
  }
  else {                             // the button has been just released
    endPressed2 = millis();
    holdTime2 = endPressed2 - startPressed2;

    if (holdTime2 < 2000) {

      trigger_relay(button2);
    }

    if (holdTime2 >= 2000) {

      //programming_mode(button);
    }
  }
}

void checkButton3() {

  buttonState3 = digitalRead(button3);

  if (buttonState3 != lastButtonState3) { // button state changed
    updateState3();
  }

  lastButtonState3 = buttonState3;        // save state for next loop
}

/*
   start measuring the time the button was pressed.
   if the status changed, then calculate the time the button was pressed
*/
void updateState3() {

  if (buttonState3 == HIGH) {         // the button has been just pressed
    startPressed3 = millis();
  }
  else {                             // the button has been just released
    endPressed3 = millis();
    holdTime3 = endPressed3 - startPressed3;

    if (holdTime3 < 2000) {
      trigger_relay(button3);
    }

    if (holdTime3 >= 2000) {

      //programming_mode(button);
    }
  }
}

void checkButton4() {

  buttonState4 = digitalRead(button4);

  if (buttonState4 != lastButtonState4) { // button state changed
    updateState4();
  }

  lastButtonState4 = buttonState4;        // save state for next loop
}

/*
   start measuring the time the button was pressed.
   if the status changed, then calculate the time the button was pressed
*/
void updateState4() {

  if (buttonState4 == HIGH) {         // the button has been just pressed
    startPressed4 = millis();
  }
  else {                             // the button has been just released
    endPressed4 = millis();
    holdTime4 = endPressed4 - startPressed4;

    if (holdTime4 < 2000) {
      trigger_relay(button4);
    }

    if (holdTime4 >= 2000) {
      //programming_mode(button);
    }
  }
}

void trigger_relay(int button) {

  if (button == button1) {
    digitalWrite(relay, HIGH);
    delay(time1);
    digitalWrite(relay, LOW);
  }
  else if (button == button2) {
    digitalWrite(relay, HIGH);
    delay(time2);
    digitalWrite(relay, LOW);
  }
  else if (button == button3) {
    digitalWrite(relay, HIGH);
    delay(time3);
    digitalWrite(relay, LOW);
  }
  else if (button == button4) {
    digitalWrite(relay, HIGH);
    delay(time4);
    digitalWrite(relay, LOW);
  }
}

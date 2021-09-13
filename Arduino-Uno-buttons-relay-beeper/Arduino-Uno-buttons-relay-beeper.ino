#include <EEPROM.h>

#define button1 8
#define button2 9
#define button3 10
#define button4 11
#define relay   12
#define beeper  7

//define time duration in ms for relay depending on each button
uint16_t time1 = 1000;
uint16_t time2 = 2000;
uint16_t time3 = 3000;
uint16_t time4 = 4000;

//address value in EEPROM for buttons time
int addr1 = 0;
int addr2 = 1;
int addr3 = 2;
int addr4 = 3;

//functions declaration
void checkButton1();
void updateState1();
void checkTime1();
void checkButton2();
void updateState2();
void checkTime2();
void checkButton3();
void updateState3();
void checkTime3();
void checkButton4();
void updateState4();
void checkTime4();
void trigger_relay(int button);
void programming_mode(int button);

int buttonState1 = 1;      // current state of the button
int lastButtonState1 = 1;  // previous state of the button
int startPressed1 = 10;     // the moment the button was pressed
int endPressed1 = 0;       // the moment the button was released
int holdTime1 = 0;         // how long the button was hold
int idleTime1 = 0;         // how long the button was idle

int buttonState2 = 1;      // current state of the button
int lastButtonState2 = 1;  // previous state of the button
int startPressed2 = 10;     // the moment the button was pressed
int endPressed2 = 0;       // the moment the button was released
int holdTime2 = 0;         // how long the button was hold
int idleTime2 = 0;         // how long the button was idle

int buttonState3 = 1;      // current state of the button
int lastButtonState3 = 1;  // previous state of the button
int startPressed3 = 10;     // the moment the button was pressed
int endPressed3 = 0;       // the moment the button was released
int holdTime3 = 0;         // how long the button was hold
int idleTime3 = 0;         // how long the button was idle

int buttonState4 = 1;      // current state of the button
int lastButtonState4 = 1;  // previous state of the button
int startPressed4 = 10;     // the moment the button was pressed
int endPressed4 = 0;       // the moment the button was released
int holdTime4 = 0;         // how long the button was hold
int idleTime4 = 0;         // how long the button was idle

bool first_time = false;  //this helps to reset the button time when entering the programming mode for first time

void setup() {

  Serial.begin(9600);

  //set inputs and outputs
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);

  pinMode(relay, OUTPUT);
  pinMode(beeper, OUTPUT);
}

void loop() {
  checkButton1();
  checkButton2();
  checkButton3();
  checkButton4();
}

void programming_mode(int button) {
  
  delay(1000);

  digitalWrite(beeper, HIGH);

  //to exit programming mode for button 4 the user needs to press button 1
  if (button == button4) {
    while (digitalRead(button1) != LOW) {
      checkTime4();
    }
    //different delay for beeper to differentiate from button 1, 2 and 3
    digitalWrite(beeper, LOW);
    delay(500);
    digitalWrite(beeper, HIGH);
    delay(500);
    digitalWrite(beeper, LOW);
    delay(500);
    digitalWrite(beeper, HIGH);
  }

  if (button == button1 | button == button2 | button == button3) {
    while (digitalRead(button4) != LOW) {
      if (button == button1) {
        checkTime1();
      }
      if (button == button2) {
        checkTime2();
      }
      if (button == button3) {
        checkTime3();
      }
    }
  }

  delay(500);
  digitalWrite(beeper, LOW);
}

void checkTime1() {

  buttonState1 = digitalRead(button1);

  if (buttonState1 != lastButtonState1) {       // button state changed
    if (buttonState1 == LOW) {                 // the button has been just pressed
      startPressed1 = millis();
      digitalWrite(relay, HIGH);
    }
    else {                                     // the button has been just released
      endPressed1 = millis();
      holdTime1 = endPressed1 - startPressed1;
      digitalWrite(relay, LOW);
      time1 += holdTime1;                       //add time pressed to corresponging button time
      EEPROM.write(addr1, time1 / 128);

      //reset time button when entering programming mode for first time
      if (first_time == true) {
        time1 = 0;
        first_time = false;
      }
    }
  }

  lastButtonState1 = buttonState1;              // save state for next loop
}

void checkTime2() {

  buttonState2 = digitalRead(button2);

  if (buttonState2 != lastButtonState2) {       // button state changed
    if (buttonState2 == LOW) {                 // the button has been just pressed
      startPressed2 = millis();
      digitalWrite(relay, HIGH);
    }
    else {                                      // the button has been just released
      endPressed2 = millis();
      holdTime2 = endPressed2 - startPressed2;
      digitalWrite(relay, LOW);
      time2 += holdTime2;                       //add time pressed to corresponging button time
      EEPROM.write(addr2, time2 / 128);

      if (first_time == true) {
        time2 = 0;
        first_time = false;
      }
    }
  }

  lastButtonState2 = buttonState2;              // save state for next loop
}

void checkTime3() {

  buttonState3 = digitalRead(button3);

  if (buttonState3 != lastButtonState3) {       // button state changed
    if (buttonState3 == LOW) {                 // the button has been just pressed
      startPressed3 = millis();
      digitalWrite(relay, HIGH);
    }
    else {                                      // the button has been just released
      endPressed3 = millis();
      holdTime3 = endPressed3 - startPressed3;
      digitalWrite(relay, LOW);
      time3 += holdTime3;                       //add time pressed to corresponging button time
      EEPROM.write(addr3, time3 / 128);
      
      if (first_time == true) {
        time3 = 0;
        first_time = false;
      }
    }
  }

  lastButtonState3 = buttonState3;              // save state for next loop
}

void checkTime4() {

  buttonState4 = digitalRead(button4);

  if (buttonState4 != lastButtonState4) {       // button state changed
    if (buttonState4 == LOW) {                 // the button has been just pressed
      startPressed4 = millis();
      digitalWrite(relay, HIGH);
    }
    else {                                     // the button has been just released
      endPressed4 = millis();
      holdTime4 = endPressed4 - startPressed4;
      digitalWrite(relay, LOW);
      time4 += holdTime4;                       //add time pressed to corresponging button time
      EEPROM.write(addr4, time4 / 128);
        
      if (first_time == true) {
        time4 = 0;
        first_time = false;
      }
    }
  }

  lastButtonState4 = buttonState4;              // save state for next loop
}


/*
   check if button is pressed or not. If the button is pressed, it means the status changed,
   so enter updateState()
*/
void checkButton1() {

  buttonState1 = digitalRead(button1);

  if (buttonState1 != lastButtonState1) { // button state changed
    updateState1();
  }

  lastButtonState1 = buttonState1;        // save state for next loop
}

/*  start measuring the time when the button was pressed.
    if the status changed, then calculate the time the button was pressed
*/

void updateState1() {

  if (buttonState1 == LOW) {         // the button has been just pressed
    startPressed1 = millis();
  }
  else {                             // the button has been just released
    endPressed1 = millis();
    holdTime1 = endPressed1 - startPressed1;

    if (holdTime1 < 2000) {

      trigger_relay(button1);
    }

    if (holdTime1 >= 2000) {

      first_time = true;
      programming_mode(button1);
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

  if (buttonState2 == LOW) {         // the button has been just pressed
    startPressed2 = millis();
  }
  else {                             // the button has been just released
    endPressed2 = millis();
    holdTime2 = endPressed2 - startPressed2;

    if (holdTime2 < 2000) {
      first_time = true;
      trigger_relay(button2);
    }

    if (holdTime2 >= 2000) {

      programming_mode(button2);
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

  if (buttonState3 == LOW) {         // the button has been just pressed
    startPressed3 = millis();
  }
  else {                             // the button has been just released
    endPressed3 = millis();
    holdTime3 = endPressed3 - startPressed3;

    if (holdTime3 < 2000) {
      trigger_relay(button3);
    }

    if (holdTime3 >= 2000) {
      first_time = true;
      programming_mode(button3);
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

  if (buttonState4 == LOW) {         // the button has been just pressed
    startPressed4 = millis();
  }
  else {                             // the button has been just released
    endPressed4 = millis();
    holdTime4 = endPressed4 - startPressed4;

    if (holdTime4 < 2000) {
      trigger_relay(button4);
    }

    if (holdTime4 >= 2000) {
      first_time = true;
      programming_mode(button4);
    }
  }
}

void trigger_relay(int button) {

  if (button == button1) {
    digitalWrite(relay, HIGH);
    delay(EEPROM.read(addr1) * 128);
    digitalWrite(relay, LOW);
  }
  else if (button == button2) {
    digitalWrite(relay, HIGH);
    delay(EEPROM.read(addr2) * 128);
    digitalWrite(relay, LOW);
  }
  else if (button == button3) {
    digitalWrite(relay, HIGH);
    delay(EEPROM.read(addr3) * 128);
    digitalWrite(relay, LOW);
  }
  else if (button == button4) {
    digitalWrite(relay, HIGH);
    delay(EEPROM.read(addr4) * 128);
    digitalWrite(relay, LOW);
  }
}

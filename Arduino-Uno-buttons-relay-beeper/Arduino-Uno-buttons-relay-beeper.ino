//Define button, relay, and beeper pins
#define button1 2
#define button2 3
#define button3 4
#define button4 5
#define relay   13
#define beeper  14

//define time duration for each button in ms
uint16_t time1 = 1000;
uint16_t time2 = 2000;
uint16_t time3 = 3000;
uint16_t time4 = 4000;

//function declaration
void checkButton(int button);
void updateState(int button);
void trigger_relay(int button);
void programming_mode(int button);
void countButtonTime(int button);

int buttonState = 0;      // current state of the button
int lastButtonState = 0;  // previous state of the button
int startPressed = 0;     // the moment the button was pressed
int endPressed = 0;       // the moment the button was released
int holdTime = 0;         // how long the button was hold
int idleTime = 0;         // how long the button was idle
uint16_t time_button_pressed = 0;

void setup() {

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

  //check button status using polling mode.
  checkButton(button1);
  checkButton(button2);
  checkButton(button3);
  checkButton(button4);
}

/*
   check the button status. If the status changed, then update the status
*/
void checkButton(int button) {

  buttonState = digitalRead(button);

  if (buttonState != lastButtonState) { // button state changed
    updateState(button);
  }

  lastButtonState = buttonState;        // save state for next loop
}

/*
   start measuring the time the button was pressed.
   if the status changed, then calculate the time the button was pressed
*/
void updateState(int button) {

  if (buttonState == HIGH) {         // the button has been just pressed
    startPressed = millis();
  }
  else {                             // the button has been just released
    endPressed = millis();
    holdTime = endPressed - startPressed;

    if (holdTime < 2000) {
      Serial.println("Button was held for less than two second");
      trigger_relay(button);
    }

    if (holdTime >= 2000) {
      Serial.println("Button was held for two second or more");
      programming_mode(button);
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

void programming_mode(int button) {
  digitalWrite(beeper, HIGH);

  //0 means me are in programming status
  int programming_status = 0;

  while (programming_status != 0) { //if button 4 is pressed it means we need to exit programming mode

    buttonState = digitalRead(button); // read button status based upon function parameter

    if (buttonState != lastButtonState) { // button state changed
      countButtonTime(button);            //due to status change, we need to count the button time being pressed
    }
    lastButtonState = buttonState;        // save state for next loop

    programming_status = digitalRead(button4);
  }

  //1 means ww need to exit programming status
  if (programming_status == 1) {

    digitalWrite(beeper, LOW);
  }
}

/*
 * count how long the button is being pressed
 */
void countButtonTime(int button) {

  if (buttonState == HIGH) {        // the button has been just pressed
    startPressed = millis();
  }
  else {                             // the button has been just released
    endPressed = millis();
    holdTime = endPressed - startPressed;

    // assign new times
    if (button == button1) {
      time1 += holdTime;
    }
    else if (button == button2) {
      time2 += holdTime;
    }
    else if (button == button3) {
      time3 += holdTime;
    }
    else if (button == button4) {
      time4 += holdTime;
    }
  }
}

#include <ezButton.h>
#include <EEPROM.h>

#define first_button 8
#define second_button 9
#define third_button 10
#define fourth_button 11
#define fifth_button 12
#define relay   13
#define beeper  7

//define time duration in ms for relay depending on each button
uint16_t time1 = 1000;
uint16_t time2 = 2000;
uint16_t time3 = 3000;
uint16_t time4 = 4000;

//useful for emergency stop
unsigned long time_now = 0;

//address value in EEPROM for buttons time
int addr1 = 0;
int addr2 = 1;
int addr3 = 2;
int addr4 = 3;

//address value in EEPROM to check if it is first time
int addr5 = 4;

int buttonState1 = 1;       //they start as 1 due to pull up resistor
int lastButtonState1 = 1;   //they start as 1 due to pull up resistor
int startPressed1 = 0;      //time when the button is pressed for first time
int holdTime1 = 0;          //time the button was being pressed
int endPressed1 = 0;        //time when button was released

int buttonState2 = 1;
int lastButtonState2 = 1;
int startPressed2 = 0;
int holdTime2 = 0;
int endPressed2 = 0;

int buttonState3 = 1;
int lastButtonState3 = 1;
int startPressed3 = 0;
int holdTime3 = 0;
int endPressed3 = 0;

int buttonState4 = 1;
int lastButtonState4 = 1;
int startPressed4 = 0;
int holdTime4 = 0;
int endPressed4 = 0;

int buttonState5 = 1;
int lastButtonState5 = 1;
int startPressed5 = 0;
int holdTime5 = 0;
int endPressed5 = 0;

//this variable helps reset the time for each button when entering programming mode
bool first_time = true;

ezButton button1(first_button);  // create ezButton object that attach to pin
ezButton button2(second_button);
ezButton button3(third_button);
ezButton button4(fourth_button);
ezButton button5(fifth_button);


void setup() {

  Serial.begin(9600);

  //set debounce time to 50 milliseconds
  button1.setDebounceTime(50);
  button2.setDebounceTime(50);
  button3.setDebounceTime(50);
  button4.setDebounceTime(50);
  button5.setDebounceTime(50);

  //set outputs
  pinMode(relay, OUTPUT);
  pinMode(beeper, OUTPUT);

}

void loop() {

  // MUST call the loop() function first
  button1.loop();
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();

  //check if button is pressed
  checkButton1();
  checkButton2();
  checkButton3();
  checkButton4();
  checkButton5();
}

void checkButton1() {

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed1 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  buttonPress = button1.isPressed();

  //if button is pressed stop checking for other buttons and wait until current buttonn is released
  if (buttonPress == true) {

    //start counting the time
    startPressed1 = millis();

    //wait until button is released
    while (buttonRelease == false) {

      //trace the time the button has been pressed
      currentTime = millis() - startPressed1;

      //let the user know that 2 seconds has passed so the user can release the button
      if (currentTime > 2000) {
        tone(beeper, 1000);
      }

      button1.loop();
      buttonRelease = button1.isReleased();
    }

    //if the code exits the while loop it means the button was released and the code decides
    //to go to programming mode or trigger the relay
    if (buttonRelease == true) {
      if (currentTime > 2000) {
        noTone(beeper);
        delay(1000);
        programming_mode(first_button);
      }
      else if ( currentTime < 2000) {
        trigger_relay(first_button);
      }
    }
  }
}

void checkButton2() {

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed2 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  buttonPress = button2.isPressed();

  //if button is pressed stop checking for other buttons and wait until current buttonn is released
  if (buttonPress == true) {

    //start counting the time
    startPressed2 = millis();

    //wait until button is released
    while (buttonRelease == false) {

      //trace the time the button has been pressed
      currentTime = millis() - startPressed2;

      //let the user know that 2 seconds has passed so the user can release the button
      if (currentTime > 2000) {
        tone(beeper, 1000);
      }

      button2.loop();
      buttonRelease = button2.isReleased();
    }

    //if the code exits the while loop it means the button was released and the code decides
    //to go to programming mode or trigger the relay
    if (buttonRelease == true) {
      if (currentTime > 2000) {
        noTone(beeper);
        delay(1000);
        programming_mode(second_button);
      }
      else if ( currentTime < 2000) {
        trigger_relay(second_button);
      }
    }
  }
}

void checkButton3() {

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed3 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  buttonPress = button3.isPressed();

  //if button is pressed stop checking for other buttons and wait until current buttonn is released
  if (buttonPress == true) {

    //start counting the time
    startPressed3 = millis();

    //wait until button is released
    while (buttonRelease == false) {

      //trace the time the button has been pressed
      currentTime = millis() - startPressed3;

      //let the user know that 2 seconds has passed so the user can release the button
      if (currentTime > 2000) {
        tone(beeper, 1000);
      }

      button3.loop();
      buttonRelease = button3.isReleased();
    }

    //if the code exits the while loop it means the button was released and the code decides
    //to go to programming mode or trigger the relay
    if (buttonRelease == true) {
      if (currentTime > 2000) {
        noTone(beeper);
        delay(1000);
        programming_mode(third_button);
      }
      else if ( currentTime < 2000) {
        trigger_relay(third_button);
      }
    }
  }
}

void checkButton4() {

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed4 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  buttonPress = button4.isPressed();

  //if button is pressed stop checking for other buttons and wait until current buttonn is released
  if (buttonPress == true) {

    //start counting the time
    startPressed4 = millis();

    //wait until button is released
    while (buttonRelease == false) {

      //trace the time the button has been pressed
      currentTime = millis() - startPressed4;

      //let the user know that 2 seconds has passed so the user can release the button
      if (currentTime > 2000) {
        tone(beeper, 1000);
      }

      button4.loop();
      buttonRelease = button4.isReleased();
    }

    //if the code exits the while loop it means the button was released and the code decides
    //to go to programming mode or trigger the relay
    if (buttonRelease == true) {
      if (currentTime > 2000) {
        noTone(beeper);
        delay(1000);
        programming_mode(fourth_button);
      }
      else if ( currentTime < 2000) {
        trigger_relay(fourth_button);
      }
    }
  }
}

void checkButton5() {

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed5 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  buttonPress = button5.isPressed();

  //if button is pressed stop checking for other buttons and wait until current buttonn is released
  if (buttonPress == true) {

    //start counting the time
    startPressed5 = millis();

    //wait until button is released
    while (buttonRelease == false) {

      //trace the time the button has been pressed
      currentTime = millis() - startPressed5;

      //let the user know that 5 seconds has passed so the user can release the button
      if (currentTime > 5000) {
        digitalWrite(beeper, HIGH);
        tone(beeper, 2000);
      }

      button5.loop();
      buttonRelease = button5.isReleased();
    }

    //if the code exits the while loop it means the button was released and we need to reset time buttons
    if (buttonRelease == true) {
      if (currentTime > 5000) {
        delay(1000);
        noTone(beeper);
        time1 = 1000;
        time2 = 2000;
        time3 = 3000;
        time4 = 4000;
        EEPROM.write(addr5, 0);
      }
    }
  }
}

void programming_mode(int button_number) {

  //let the user know is in programming mode
  tone(beeper, 2000);
  delay(1000);
  noTone(beeper);

  bool buttonPress5 = false;

  //wehen button 5 is pressed it means the user wants to exit programming mode
  while (buttonPress5 == false) {
    if (button_number == first_button) {
      programTime1();
    }
    else if (button_number == second_button) {
      programTime2();
    }
    else if (button_number == third_button) {
      programTime3();
    }
    else if (button_number == fourth_button) {
      programTime4();
    }

    button5.loop();
    buttonPress5 = button5.isPressed();
  }

  first_time = true;
}

void programTime1() {

  //if it's the first time the user enters programming mode, it should reset the time
  //for the given button
  if (first_time == true) {
    time1 = 0;
    first_time = false;
  }

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed1 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  button1.loop();
  buttonPress = button1.isPressed();

  //if button is pressed wait until it is released
  if (buttonPress == true) {
    digitalWrite(relay, HIGH);

    //start counting the time
    startPressed1 = millis();

    //wait until button is released
    while (buttonRelease == false) {
      button1.loop();
      buttonRelease = button1.isReleased();
    }

    //count how much time the button was pressed
    digitalWrite(relay, LOW);
    endPressed1 = millis();
    holdTime1 = endPressed1 - startPressed1;

    //add the time the button was pressed to time1
    time1 += holdTime1;
    EEPROM.write(addr1, time1 / 128);  //EEPROM accepts values between 0-255
    EEPROM.write(addr5, 1);
  }
}

void programTime2() {

  //if it's the first time the user enters programming mode, it should reset the time
  //for the given button
  if (first_time == true) {
    time2 = 0;
    first_time = false;
  }

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed2 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  button2.loop();
  buttonPress = button2.isPressed();

  //if button is pressed wait until it is released
  if (buttonPress == true) {
    digitalWrite(relay, HIGH);

    //start counting the time
    startPressed2 = millis();

    //wait until button is released
    while (buttonRelease == false) {
      button2.loop();
      buttonRelease = button2.isReleased();
    }

    //count how much time the button was pressed
    digitalWrite(relay, LOW);
    endPressed2 = millis();
    holdTime2 = endPressed2 - startPressed2;

    //add the time the button was pressed to time1
    time2 += holdTime2;
    EEPROM.write(addr2, time2 / 128);
    EEPROM.write(addr5, 1);
  }
}

void programTime3() {

  //if it's the first time the user enters programming mode, it should reset the time
  //for the given button
  if (first_time == true) {
    time3 = 0;
    first_time = false;
  }

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed3 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  button3.loop();
  buttonPress = button3.isPressed();

  //if button is pressed wait until it is released
  if (buttonPress == true) {
    digitalWrite(relay, HIGH);

    //start counting the time
    startPressed3 = millis();

    //wait until button is released
    while (buttonRelease == false) {
      button3.loop();
      buttonRelease = button3.isReleased();
    }

    //count how much time the button was pressed
    digitalWrite(relay, LOW);
    endPressed3 = millis();
    holdTime3 = endPressed3 - startPressed3;

    //add the time the button was pressed to time1
    time3 += holdTime3;
    EEPROM.write(addr3, time3 / 128);
    EEPROM.write(addr5, 1);
  }
}

void programTime4() {

  //if it's the first time the user enters programming mode, it should reset the time
  //for the given button
  if (first_time == true) {
    time4 = 0;
    first_time = false;
  }

  //button starts not pressed and released
  bool buttonPress = false;
  bool buttonRelease = false;
  startPressed4 = 0;

  //time the button has been pressed
  int currentTime = 0;

  //check if button is pressed
  button4.loop();
  buttonPress = button4.isPressed();

  //if button is pressed wait until it is released
  if (buttonPress == true) {
    digitalWrite(relay, HIGH);

    //start counting the time
    startPressed4 = millis();

    //wait until button is released
    while (buttonRelease == false) {
      button4.loop();
      buttonRelease = button4.isReleased();
    }

    //count how much time the button was pressed
    digitalWrite(relay, LOW);
    endPressed4 = millis();
    holdTime4 = endPressed4 - startPressed4;

    //add the time the button was pressed to time1
    time4 += holdTime4;
    EEPROM.write(addr4, time4 / 128);
    EEPROM.write(addr5, 1);
  }
}

void trigger_relay(int button_number) {

  time_now = millis();
  int statusButton = 0;   //the button start released
  bool exitFlag = false;  //enter the while loop at start

  if (button_number == first_button) {
    //if addr == 1 it means in the past the user entered programming mode
    if (EEPROM.read(addr5) == 1) {
      digitalWrite(relay, HIGH);
      int eepromTime = EEPROM.read(addr1) * 128;
      while ((millis() < time_now + eepromTime) & exitFlag == false) {
        button1.loop();
        statusButton = button1.isPressed();
        if (statusButton == 1) {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
    else {
      digitalWrite(relay, HIGH);

      while ((millis() < time_now + time1) & exitFlag == false) {
        button1.loop();
        statusButton = button1.isPressed();
        if (statusButton == 1) {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
  }
  else if (button_number == second_button)
  {
    if (EEPROM.read(addr5) == 1)
    {
      digitalWrite(relay, HIGH);
      int eepromTime = EEPROM.read(addr2) * 128;

      while ((millis() < time_now + eepromTime) & exitFlag == false)
      {
        button2.loop();
        statusButton = button2.isPressed();

        if (statusButton == 1)
        {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
    else
    {
      digitalWrite(relay, HIGH);

      while ((millis() < time_now + time2) & exitFlag == false)
      {
        button2.loop();
        statusButton = button2.isPressed();

        if (statusButton == 1)
        {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
  }
  else if (button_number == third_button) {
    if (EEPROM.read(addr5) == 1)
    {
      digitalWrite(relay, HIGH);
      int eepromTime = EEPROM.read(addr3) * 128;

      while ((millis() < time_now + eepromTime) & exitFlag == false)
      {
        button3.loop();
        statusButton = button3.isPressed();

        if (statusButton == 1)
        {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
    else
    {
      digitalWrite(relay, HIGH);

      while ((millis() < time_now + time3) & exitFlag == false)
      {
        button3.loop();
        statusButton = button3.isPressed();

        if (statusButton == 1)
        {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
  }
  else if (button_number == fourth_button) {
    if (EEPROM.read(addr5) == 1)
    {
      digitalWrite(relay, HIGH);
      int eepromTime = EEPROM.read(addr4) * 128;

      while ((millis() < time_now + eepromTime) & exitFlag == false)
      {
        button4.loop();
        statusButton = button4.isPressed();

        if (statusButton == 1)
        {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
    else
    {
      digitalWrite(relay, HIGH);

      while ((millis() < time_now + time4) & exitFlag == false)
      {
        button4.loop();
        statusButton = button4.isPressed();

        if (statusButton == 1)
        {
          digitalWrite(relay, LOW);
          exitFlag = true;
        }
      }
      digitalWrite(relay, LOW);
    }
  }
}

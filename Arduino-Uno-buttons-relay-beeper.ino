//Define pins 
#define button1 2
#define button2 3
#define button3 4
#define button4 5

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}
int button1State = 0;

void loop() {

  button1State = digitalRead(button1);
  Serial.println(button1State);

   if (button1State == HIGH) {
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
  }
  
}

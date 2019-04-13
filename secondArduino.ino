// Arduino 2 (C)
// Servo Motor latch and rgb light
#include <Servo.h>

Servo myservo;
int redPin = 5;
int greenPin = 6;
int bluePin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(0);
  //gives us 5 seconds to close the door before it locks
  delay(5000);
  //locks the door
  myservo.write(115);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0){
    char reading = Serial.read();

    //if the remote says to close or reset then reset the latch to the closed position
    if(reading == 'C' || reading == 'R'){
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      myservo.write(115);
    }
    else if(reading == 'O'){
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      myservo.write(0);
    }
  }
}

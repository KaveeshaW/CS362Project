// Arduino 3 (K)
// Buttons, Buzzer, Ultrasonic Sensor, LEDs

//there is only one real button in the safe that works, the other two buttons are dummies. the real button pin is 11
const byte realButton = 11; 

//creates a continuous sound a second after the user enters the right password. The sound can only be turned of by pressing the button connected to pin 11
const int buzzer = 10;  

//pins that is used for the ultrasonic sensor
const int trigPin = 8;
const int echoPin = 9;

//used in tandem with the motion tracking, all of them either turn off or on based on where the users hand is in the safe
const int whiteLED = 7;
const int greenLED = 6;
const int blueLED = 5;
const int redLED = 4;

//keeps track of the state of the actual button
int buttonState;

//used in order to track the hand of the person using the safe, once the users hand is close enough, all of the LED's turn on
long duration;
int distance;

//*********************************************************************************
//setup()
void setup() {

  // Sets the trigPin as an Output
  pinMode(trigPin, OUTPUT);
  // Sets the echoPin as an Input 
  pinMode(echoPin, INPUT); 

  // pin 11 is the real button, sets realButton as an input
  pinMode(realButton, INPUT);  

  //sets the buzzer as output
  pinMode(buzzer, OUTPUT);

  //sets up all of the LEDs to be output
  pinMode(whiteLED, OUTPUT);
  pinMode(greenLED ,OUTPUT); 
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Starts the serial communication
  Serial.begin(9600); 

  //sets up all of the LEDs to off at the start of the program
  digitalWrite(whiteLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);

  //makes sure the buzzer is off before the program starts, that is the second arduino send 'B' or begin to this arduino
  noTone(buzzer);
}
//end setup()
//*********************************************************************************

//*********************************************************************************
//loop()
void loop() {
  //*********************************************************************************
  //reads in information from the second arduino to know what to do in the program
  //two options, either q or b
  if(Serial.available() > 0) {
    //reads in what the second arduino sent
    char readIn = Serial.read();
    //'Q' is for reset or quit
    if(readIn == 'Q') {
      //turns off all of the LEDs
      digitalWrite(whiteLED, LOW);
      digitalWrite(greenLED, LOW);
      digitalWrite(blueLED, LOW);
      digitalWrite(redLED, LOW); 
      
      //shuts off the buzzer
      noTone(buzzer);
   }
    //b is for buzzer, meaing to start the buzzer sound to begin this part of the program
    else if(readIn == 'B') {
      // delay is so that the buzzer does not immediately make a sound when the user enters the right password
      delay(1000);
      //buzzer makes a sound
      tone(buzzer, 1000);
    }    
  }
  //*********************************************************************************

  //*********************************************************************************
  //code to turn off buzzer
  //reads in the real button state
  buttonState = digitalRead(realButton);
  //if the button was pressed, then turn off the buzzer
  if(buttonState == HIGH) {
    noTone(buzzer);
  }
  //*********************************************************************************

  //*********************************************************************************
  //tracks where the users hand is in the safe
  //Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  //Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  //Calculating the distance
  distance= duration*0.034/2;
  //*********************************************************************************

  //*********************************************************************************
  //handles what happens when the users hand is close to the buttons
  //if the user's hand is less then 60 mm, then the program turns on all of the LEDs
  if(distance < 60) {
    digitalWrite(whiteLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
    digitalWrite(redLED, HIGH);
  }
  //else, have all of the LEDs turn off
  else {
    digitalWrite(whiteLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, LOW);
  }
  //*********************************************************************************
}
//end loop()
//*********************************************************************************

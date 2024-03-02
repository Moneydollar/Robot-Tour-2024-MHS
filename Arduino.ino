#include <Arduino.h>

// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B
int enB = 3;
int in3 = 4;
int in4 = 5;

bool isProgramEnded = false;

enum State {READY, STOP, FORWARD, BACKWARD,  RIGHT, LEFT};
State state = READY;
float MAX_SPEED = 255; // Maximum PWM for full speed
float THREE_FOURTH_SPEED = MAX_SPEED * 0.75;
float HALF_SPEED = MAX_SPEED * 0.5;
float QUARTER_SPEED = MAX_SPEED * 0.25;


float speedMODE = MAX_SPEED;

float turnTime = 1000; // in milliseconds

void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  // Serial.println('Setup Complete!');
}

 /* Duration is in Milliseconds*/

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  state = STOP; // update state
}

void forward(int speed, unsigned long duration) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stop();
  state = FORWARD; // update state
}

void backward(int speed, unsigned long duration) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stop();
  state = BACKWARD; // update state
}


void left(int speed, unsigned long duration) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stop();
  state = LEFT; // update state
}


void right(int speed, unsigned long duration) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stop();
  state = RIGHT; // update state
}


float pwmToSpeed(int pwmValue) {
  // Placeholder conversion, replace with your own logic
  // For example, assume linear relationship for simplicity (unlikely to be accurate)
  float maxSpeedMetersPerSecond = 0.70; // Maximum speed in m/s corresponding to 255 PWM
  return (pwmValue / 255.0) * maxSpeedMetersPerSecond;
}


float turningSpeed(float ModeSpeed) {
  // Assuming ModeSpeed is the current speed mode (e.g., speedMODE)
  if (ModeSpeed == MAX_SPEED) {
    return  375.0 ;
  } else if (ModeSpeed == THREE_FOURTH_SPEED) {
     return  460.0 ;
  } else if (ModeSpeed == HALF_SPEED) {
   return  825.0 ;  }
    else {
    // Consider adding a default case if none of the above conditions are met
    return 1000; // Default turn time or adjust as necessary
  }
}

float calculateTime(float distance, float speed){ // Distance in Meters 
  speed = pwmToSpeed(speed);
  float time = distance / speed;

  return time * 1000; // Convert to milliseconds since delay() expects milliseconds
}


  /* Insert Instructions Here */

  /*375 ms is proper time for turn (Tested on max speed)*/
  /* 460 ms is proper duration for turn on 3/4 speed */
  /* 825 ms is proper duration for turn on half speed */

  /* 1Speed mode can be changed globally and per instruction */

void loop() {
  // First movement with dynamic speed
  forward(speedMODE, calculateTime(.25, speedMODE));
  delay(100);
  left(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.25, speedMODE));
  delay(100);
  right(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.25, speedMODE));
  delay(100);
  right(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.25, speedMODE));
  delay(100);
  left(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.60, speedMODE));
  delay(100);
  left(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.25, speedMODE));
  delay(100);
  right(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.25, speedMODE));
  delay(100);
  right(speedMODE, turningSpeed(speedMODE));
  delay(100);
  forward(speedMODE, calculateTime(.35, speedMODE));


  stop();

  if (state == STOP) {
    stop();
    delay(99999999); // Effectively halts the program
  }
}



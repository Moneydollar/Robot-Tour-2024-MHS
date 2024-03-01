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

enum State {READY, STOP, FORWARD, BACKWARD, LEFT, RIGHT};
State state = READY;
float SPEED = .70; // In meters per second 

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
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stop();
  state = LEFT; // update state
}

void right(int speed, unsigned long duration) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, speed);
  analogWrite(enB, speed);
  delay(duration);
  stop();
  state = RIGHT; // update state
}

float calculateTime(float distance){ // Distance in Meters 
  float time = distance / SPEED;
  return time * 1000; // Convert to milliseconds since delay() expects milliseconds
}

void loop() {

  /* Insert Instructions Here */

 forward(255, calculateTime(.5));
 delay(500);
 left(255, 1000);
 delay(500);
 forward(255, calculateTime(.5));
 delay(500);
 left(255, 1000);
 delay(500);
 forward(255, calculateTime(.5));
 delay(500);
 left(255, 1000);
 delay(500);
 forward(255, calculateTime(.5));
 delay(500);
 left(255, 1000); 
 
 state = STOP;

 if (state == STOP){
  stop();
  delay(99999999);
 }

}
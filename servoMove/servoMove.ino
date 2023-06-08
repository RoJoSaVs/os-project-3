
#include <Servo.h>

Servo servo1;  // Create a servo object
Servo servo2;  // Create a servo object
Servo servo3                                          ;  // Create a servo object
int currentPositionServo1 = 90;
int currentPositionServo2 = 145;
int currentPositionServo3 = 45;


void setup() {
  servo1.attach(9);  // Connect the SG90 servo to pin 9
  servo2.attach(10);  // Connect the SG90 servo to pin 10
  servo3.attach(5);  // Connect the SG90 servo to pin 11

  servo1.write(currentPositionServo1);   // Move the servo to 0 degrees position
  servo2.write(currentPositionServo2);   // Move the servo to 0 degrees position
  servo3.write(currentPositionServo3);   // Move the servo to 0 degrees position
  Serial.begin(9600);  // Initialize serial communication
}

void moveServo(int currentPosition, int targetPosition, Servo servo){
  if (currentPosition < targetPosition) {
    for(int i = currentPosition; i < targetPosition; i++){
      servo.write(i);
      delay(20);
    }
  } 
  else if (currentPosition > targetPosition) {
    for(int i = currentPosition; i > targetPosition; i--){
      servo.write(i);
      delay(20);
    }
  }
}

Servo getServo(int number){
    int servo = number % 10;
    switch (servo) {

    case 1:
    return servo1;
      break;

    case 2:
    return servo2;
      break;

    case 3:
    return servo3;
      break;

    default:
      // Code to be executed if the switch state is neither HIGH nor LOW
      break;
  }
}

int getCurrentPosition(int number){
    int servo = number % 10;
    int result = 0;
    int angleValue = number/10;
    
    switch (servo) {

    case 1:
      result = currentPositionServo1;
      currentPositionServo1 = angleValue;
      break;

    case 2:
      result = currentPositionServo2;
      currentPositionServo2 = angleValue;
      break;

    case 3:
      result = currentPositionServo3;
      currentPositionServo3 = angleValue;
      break;

    default:
      // Code to be executed if the switch state is neither HIGH nor LOW
      break;
  }
  return result;
}

void loop() {
  if (Serial.available()) {
    int number = Serial.parseInt();  // Read the incoming number from serial monitor

    if (!Serial.parseFloat()) {

      Servo servo = getServo(number);
      int currentPositionServo = getCurrentPosition(number);

      moveServo(currentPositionServo, number/10, servo);

      if(number % 10 == 2){
        moveServo(currentPositionServo, (number/10 + 60), servo);
      }
    }
  }
}

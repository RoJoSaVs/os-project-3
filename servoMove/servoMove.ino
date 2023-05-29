
#include <Servo.h>

Servo servo1;  // Create a servo object
Servo servo2;  // Create a servo object
Servo servo3                                          ;  // Create a servo object

void setup() {
  servo1.attach(9);  // Connect the SG90 servo to pin 9
  servo2.attach(10);  // Connect the SG90 servo to pin 10
  servo3.attach(5);  // Connect the SG90 servo to pin 11
  servo1.write(170);   // Move the servo to 0 degrees position
  servo2.write(5);   // Move the servo to 0 degrees position
  servo3.write(90);   // Move the servo to 0 degrees position
  Serial.begin(9600);  // Initialize serial communication
}

void moveServo(int currentPosition, int targetPosition, Servo servo){
  if (currentPosition < targetPosition) {
    currentPosition += 1;
    if (currentPosition > targetPosition) {
      currentPosition = targetPosition;
    }
  } else if (currentPosition > targetPosition) {
    currentPosition -= 1;
    if (currentPosition < targetPosition) {
      currentPosition = targetPosition;
    }
  }

  servo.write(currentPosition);
  delay(15);
}


void loop() {
  if (Serial.available()) {
    int number = Serial.parseInt();  // Read the incoming number from serial monitor

    switch (number) {

      case 1:
        moveServo(170, 90, servo1);
        Serial.println("Servo 1 moved to 90 degrees");
        break;
      case 2:
        moveServo(90, 170, servo1);
        Serial.println("Servo 1 moved to 180 degrees");
        break;
      case 3:
        moveServo(5, 90, servo2);
        Serial.println("Servo 2 moved to 0 degrees");
        break;
      case 4:
        moveServo(90, 5, servo2);
        Serial.println("Servo 2 moved to 90 degrees");
        break;

      case 5:
        moveServo(150, 70, servo3);
        Serial.println("Servo 3 moved to 90 degrees");
        break;
      case 6:
        moveServo(70, 150, servo3);
        Serial.println("Servo 3 moved to 180 degrees");
        break;
      default:
        Serial.println("Invalid number");
        

        break;
    }
  }
}

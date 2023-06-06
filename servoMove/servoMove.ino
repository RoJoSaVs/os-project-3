
#include <Servo.h>

Servo servo1;  // Create a servo object
Servo servo2;  // Create a servo object
Servo servo3                                          ;  // Create a servo object
int currentPosition;


void setup() {
  servo1.attach(9);  // Connect the SG90 servo to pin 9
  servo2.attach(10);  // Connect the SG90 servo to pin 10
  servo3.attach(5);  // Connect the SG90 servo to pin 11

  servo1.write(90);   // Move the servo to 0 degrees position
  servo2.write(50);   // Move the servo to 0 degrees position
  servo3.write(10);   // Move the servo to 0 degrees position
  Serial.begin(9600);  // Initialize serial communication
}

void moveServo(int targetPosition, Servo servo){
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


void loop() {
  if (Serial.available()) {
    int number = Serial.parseInt();  // Read the incoming number from serial monitor


    moveServo(number, servo1);
    // switch (number) {

    //   case 1:
    //     moveServo(90, 12.8, servo1);
    //     Serial.println("Servo 1 moved to 90 degrees");
    //     break;
    //   case 2:
    //     moveServo(12.8, 90, servo1);
    //     Serial.println("Servo 1 moved to 180 degrees");
    //     break;
    //   case 3:
    //     moveServo(5, 90, servo2);
    //     Serial.println("Servo 2 moved to 0 degrees");
    //     break;
    //   case 4:
    //     moveServo(90, 5, servo2);
    //     Serial.println("Servo 2 moved to 90 degrees");
    //     break;

    //   case 5:
    //     moveServo(150, 70, servo3);
    //     Serial.println("Servo 3 moved to 90 degrees");
    //     break;
    //   case 6:
    //     moveServo(70, 150, servo3);
    //     Serial.println("Servo 3 moved to 180 degrees");
    //     break;
    //   default:
    //     Serial.println("Invalid number");
        

    //     break;
    // }
  }
}

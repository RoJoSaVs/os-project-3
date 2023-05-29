
#include <Servo.h>

Servo servo1;  // Create a servo object
Servo servo2;  // Create a servo object
Servo servo3                                          ;  // Create a servo object

void setup() {
  servo1.attach(9);  // Connect the SG90 servo to pin 9
  servo2.attach(10);  // Connect the SG90 servo to pin 10
  servo3.attach(5);  // Connect the SG90 servo to pin 11
  servo1.write(5);   // Move the servo to 0 degrees position
  servo2.write(5);   // Move the servo to 0 degrees position
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if (Serial.available()) {
    int number = Serial.parseInt();  // Read the incoming number from serial monitor

    switch (number) {
      case 1:
        servo1.write(5);   // Move the servo to 0 degrees position
        Serial.println("Servo 1 moved to 0 degrees");
        break;
      case 2:
        servo1.write(90);  // Move the servo to 90 degrees position
        Serial.println("Servo 1 moved to 90 degrees");
        break;
      case 3:
        servo1.write(170); // Move the servo to 180 degrees position
        Serial.println("Servo 1 moved to 180 degrees");
        break;
      case 4:
        servo2.write(5);   // Move the servo to 0 degrees position
        Serial.println("Servo 2 moved to 0 degrees");
        break;
      case 5:
        servo2.write(90);  // Move the servo to 90 degrees position
        Serial.println("Servo 2 moved to 90 degrees");
        break;
      case 6:
        servo2.write(170); // Move the servo to 180 degrees position
        Serial.println("Servo 2 moved to 180 degrees");
        break;
      case 7:
        servo3.write(5);   // Move the servo to 0 degrees position
        Serial.println("Servo 3 moved to 0 degrees");
        break;
      case 8:
        servo3.write(90);  // Move the servo to 90 degrees position
        Serial.println("Servo 3 moved to 90 degrees");
        break;
      case 9:
        servo3.write(170); // Move the servo to 180 degrees position
        Serial.println("Servo 3 moved to 180 degrees");
        break;
      default:
        Serial.println("Invalid number");
        

        break;
    }
  }
}

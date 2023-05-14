#include <Servo.h>

Servo sg90;  // Create a servo object

void setup() {
  sg90.attach(9);  // Connect the SG90 servo to pin 9
  Serial.begin(9600);  // Initialize serial communication
}

void loop() {
  if (Serial.available()) {
    int number = Serial.parseInt();  // Read the incoming number from serial monitor

    switch (number) {
      case 1:
        sg90.write(0);   // Move the servo to 0 degrees position
        Serial.println("Servo moved to 0 degrees");
        break;
      case 2:
        sg90.write(90);  // Move the servo to 90 degrees position
        Serial.println("Servo moved to 90 degrees");
        break;
      case 3:
        sg90.write(170); // Move the servo to 180 degrees position
        Serial.println("Servo moved to 180 degrees");
        break;
      default:
        Serial.println("Invalid number");
        break;
    }
  }
}

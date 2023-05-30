// Pin para el LED que se encenderá dependiendo de la variable
const int ledPin = 2;

// Variable para almacenar la opción seleccionada
int selectedOption = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    //selectedOption = Serial.parseInt();
    selectedOption = 3;
    // Encender el LED correspondiente a la opción seleccionada
    switch (selectedOption) {
      case 0:
        digitalWrite(ledPin, LOW);
        break;
      case 1:
        digitalWrite(ledPin, HIGH);
        break;
      case 2:
        blinkLED(1000); // Frecuencia de parpadeo: 1 segundo
        break;
      case 3:
        blinkLED(500); // Frecuencia de parpadeo: 0.5 segundos
        break;
      case 4:
        blinkLED(200); // Frecuencia de parpadeo: 0.2 segundos
        break;
    }
  }
}

// Función para hacer parpadear el LED a una frecuencia específica
void blinkLED(int interval) {
  digitalWrite(ledPin, HIGH);
  delay(interval / 2);
  digitalWrite(ledPin, LOW);
  delay(interval / 2);
    digitalWrite(ledPin, HIGH);
  delay(interval / 2);
  digitalWrite(ledPin, LOW);
  delay(interval / 2);
    digitalWrite(ledPin, HIGH);
  delay(interval / 2);
  digitalWrite(ledPin, LOW);
  delay(interval / 2);
    digitalWrite(ledPin, HIGH);
  delay(interval / 2);
  digitalWrite(ledPin, LOW);
  delay(interval / 2);
}

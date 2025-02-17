const int moisturePin = A0;       
const int motorPin = 2;           
const int redLed = 3;             // low moisture/spraying
const int greenLed = 4;           // adequate moisture
const int moistureThreshold = 500; 
const int moistureIncrement = 150; 

unsigned long lastSprayTime = 0;
const unsigned long sprayDuration = 2000; 
bool isSpraying = false;
int simulatedMoisture = 0; 

void setup() {
  pinMode(motorPin, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  Serial.begin(9600);
  simulatedMoisture = analogRead(moisturePin); 
}

void loop() {
  int sensorValue = analogRead(moisturePin);
  
  if (isSpraying) {
    if (millis() - lastSprayTime >= sprayDuration) {
      isSpraying = false;
      digitalWrite(motorPin, LOW);
      simulatedMoisture += moistureIncrement; 
      Serial.print("Moisture increased to: ");
      Serial.println(simulatedMoisture);
    }
  } else {
    if (simulatedMoisture < moistureThreshold) {
      isSpraying = true;
      lastSprayTime = millis();
      digitalWrite(motorPin, HIGH);
      Serial.println("Spraying started");
    }
  }

  if (simulatedMoisture >= moistureThreshold) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
  } else {
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH); 
  }

  delay(500); 
}
#include <Adafruit_LiquidCrystal.h>
#include <Wire.h>

const int tempSensorPin = A0;
const int greenLEDPin = 8;
const int redLEDPin = 9;
const int buzzerPin = 10;
const int buttonPin = 7;

Adafruit_LiquidCrystal lcd(0);

bool alertState = false;

void setup() {
  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.setBacklight(1);
  
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(tempSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  float temperature = (voltage - 0.5) * 100.0;
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  if (temperature > 25.0) {
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, HIGH);
    tone(buzzerPin, 1000);
    delay(1000);
    digitalWrite(redLEDPin, LOW);
    delay(100);
    alertState = true;
  } 
  else if (temperature > 15.0) {
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
    noTone(buzzerPin);
    alertState = false;
  } 
  else {
    digitalWrite(greenLEDPin, LOW);
    digitalWrite(redLEDPin, LOW);
    noTone(buzzerPin);
    alertState = false;
  }
  
  if (digitalRead(buttonPin) == LOW) {
    resetSystem();
  }
  
  delay(500);
}

void resetSystem() {
  digitalWrite(greenLEDPin, LOW);
  digitalWrite(redLEDPin, LOW);
  noTone(buzzerPin);
  
  alertState = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Reset");
  delay(1000);
}

/***********************
Author: Mahmoud Elbhrawy
***********************/

#include <LiquidCrystal.h>

const int trigPin = 9;    // Trigger pin of ultrasonic sensor
const int echoPin = 10;   // Echo pin of ultrasonic sensor
const int numReadings = 5;  // Number of readings for averaging

// Initialize the LiquidCrystal library with the appropriate pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2); // (RS, E, D4, D5, D6, D7)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set up the number of columns and rows for the LCD
  lcd.begin(16, 2);
}

void loop() {
  long duration;
  float distance;
  float totalDistance = 0;

  for (int i = 0; i < numReadings; i++) {
    // Trigger ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the duration of the echo signal
    duration = pulseIn(echoPin, HIGH);

    // Calculate distance in centimeters
    distance = (duration * 0.0343) / 2;

    // Add up the distances for averaging
    totalDistance += distance;

    delay(50); // Delay between readings
  }

  // Calculate average distance
  float averageDistance = totalDistance / numReadings;

  // Display average distance on the Serial Monitor
  Serial.print("Average Distance: ");
  Serial.print(averageDistance);
  Serial.println(" cm");

  // Display average distance on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(averageDistance);
  lcd.print(" cm");

  //delay(1000); // Delay before next measurement
}

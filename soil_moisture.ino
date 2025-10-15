#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 if your LCD has a different I2C address

// Servo setup
Servo myServo;
const int servoPin = 9;

// Soil sensor setup
const int sensorPin = A0;
int threshold = 40;  // Moisture threshold (%)

void setup() {
  myServo.attach(servoPin);
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(sensorPin);              
  int moisturePercent = map(sensorValue, 0, 1023, 0, 100);

  // Serial Monitor Output
  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // LCD Output
  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moisturePercent);
  lcd.print("%   "); // extra spaces to clear old values

  lcd.setCursor(0, 1);
  if (moisturePercent < threshold) {
    myServo.write(90); // Servo ON (simulate watering)
    lcd.print("Watering: ON  ");
    Serial.println("Watering: ON");
  } else {
    myServo.write(0);  // Servo OFF
    lcd.print("Watering: OFF ");
    Serial.println("Watering: OFF");
  }

  delay(1000); // 1-second delay between readings
}

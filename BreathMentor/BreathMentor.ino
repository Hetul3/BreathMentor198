#include <LiquidCrystal.h>
//make sure to install liquidcrystal by arduino in Library Manager

//RS, Enable, then d4, 5, 6, 7 (out of d0-7 but we use 4bit mode).
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
void setup() {
  Serial.begin(9600); //for stretch sensor

  lcd.begin(16,2); // for LCD
}
void loop() {
  lcd.print("test");
  delay(3000);
  lcd.clear();
  delay(3000); // ^ for LCD


  // For the stretch sensor:
  int sensorValue = analogRead(A0); // Read analog input
  float voltage = sensorValue * (5.0 / 1023.0); // Convert analog value to voltage
  float knownResistance = 1000.0; // Replace with the value of the known resistor in ohms
  float wireResistance = (5.0 * knownResistance) / (voltage) - knownResistance; // Calculate wire resistance

  Serial.print("Wire Resistance: ");
  Serial.println(wireResistance);
  delay(1000); // Delay for readability, adjust as needed
  
}

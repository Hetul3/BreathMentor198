#include <LiquidCrystal_I2C.h>
//make sure to install liquidcrystal by arduino in Library Manager

//RS, Enable, then d4, 5, 6, 7 (out of d0-7 but we use 4bit mode).
LiquidCrystal_I2C lcd(0x27, 16, 2);
int sensorValue;

void setup() {
  //pinMode(7, OUTPUT);
  //Serial.begin(9600); //for stretch sensor
  lcd.init();
  lcd.backlight(); // for LCD
  lcd.setCursor(0,0);
  lcd.print("Begin Test");
}
void loop() {
  // lcd.setCursor(0,0);
  // lcd.print("test");
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(3000);
  // lcd.clear();
  // digitalWrite(LED_BUILTIN, LOW);
  // delay(3000); // ^ for LCD

  // For the stretch sensor:
  //  // Read analog input
  sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0); // Convert analog value to voltage
  float knownResistance = 2000.0; // Replace with the value of the known resistor in ohms
  float wireResistance = (5.0 * knownResistance) / (voltage) - knownResistance; // Calculate wire resistance

  //constants for converting to force
  const float initialResistence;
  const float sensitivityFactor;
  const float radius = 0.001;
  const float crossSectionalArea = 3.14159 * radius * radius;
  const float originalLength = 0.87;
  const float modulus;

  float changeInResistence = wireResistance - initialResistence;
  float force = (changeInResistence / initialResistence) * (1 / sensitivty) * (crossSectionalArea / originalLength) * modulus;


  //constants for changing it to change in length
  const float springConstant = 640;

  float changeInLength = force / springConstant;
  
  //constants for moles and pressure
  const float area;

  float pressure = force / area;

  const float gasConstant = 8.31;
  const float absoluteTemperature = 310;
  float circumfrance = (originalLength + changeInLength) / (2*3.14159);
  float volume = 3.14159 * circumfrance * circumfrance * 0.27;

  float moles = (pressure * volume) / (gasConstant * absoluteTemperature);



  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Wire Resistance:");
  lcd.setCursor(0,1);
  lcd.print(wireResistance);
  delay(100); // Delay for readability, adjust as needed
  
}

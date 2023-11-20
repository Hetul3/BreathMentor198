<<<<<<< Updated upstream
#include <LiquidCrystal.h>
//make sure to install liquidcrystal by arduino in Library Manager
=======
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int sensorValue;
float voltage;
int pastSince = 0;
int timeSince;
float wireResistance;
float knownResistence = 2000.0;
const float initialResistence = 7300;
const float sensitivityFactor = 3.3;
const float radius = 0.001;
const float crossSectionalArea = 3.14159 * radius * radius;
const float originalLength = 0.87;
const float modulus = 12000000;

const float springConstant = 32;

const float area = 0.000254;

const float gasConstant = 8.31;
const float absoluteTemperature = 310;

const float originalMoles = 1.71;

>>>>>>> Stashed changes

//RS, Enable, then d4, 5, 6, 7 (out of d0-7 but we use 4bit mode).
LiquidCrystal lcd(1, 2, 3, 4, 5, 6);
void setup() {
  Serial.begin(9600); //for stretch sensor

  lcd.begin(16,2); // for LCD
}
void loop() {
<<<<<<< Updated upstream
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
  
=======
  sensorValue = analogRead(A0);
  voltage = sensorValue * (5.0 / 1023.0);
  wireResistance = (5.0 * knownResistence) / (voltage) - knownResistence;

  float changeInResistence = wireResistance - initialResistence;
  float force;
  force = (changeInResistence / initialResistence) * (1 / sensitivityFactor) * (crossSectionalArea / originalLength) * modulus;
  float changeInLength = force / springConstant;

  float pressure = force / area;

  float radii = (originalLength + changeInLength) / (2 * 3.14159);
  float volume = 3.14159 * radii * radii * 0.27;

  float moles = (pressure * volume) / (gasConstant * absoluteTemperature);
  timeSince = millis();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Length:");
  lcd.setCursor(8,0);
  lcd.print((changeInLength * 100 + originalLength * 100)*0.935 ); //0.935 calibrated adjustment
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print(originalMoles + moles);
  lcd.setCursor(8,1);
  
  

  

//  lcd.print("Log: ");
  lcd.print(1000/(timeSince-pastSince));
  lcd.print(" FPS"); //logs the frames per second = frame update hz, equals 1000ms/the ms time since last loop frame. Each loop frame updates the lcd once and also samples the data once.
  pastSince = timeSince; 
  delay(50);
>>>>>>> Stashed changes
}

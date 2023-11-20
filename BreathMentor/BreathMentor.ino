#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int sensorValue;
float voltage;
int newTime;
int oldTime;
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


void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Begin Test");
}

void loop() {
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


  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Length:");
  lcd.setCursor(8,0);
  lcd.print(changeInLength * 100 + originalLength * 100);
  lcd.print("cm");
  lcd.setCursor(0,1);
  lcd.print(originalMoles + moles);
  lcd.print("mol");
  lcd.setCursor(8,1);
  newTime=millis();
  lcd.print(1000/(newTime-oldTime));
  lcd.print(" FPS");
  oldTime = newTime;
  //delay(10);
}

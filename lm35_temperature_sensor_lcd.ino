#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int lm35Pin = A0; // LM35 output connected to A0

// Set the LCD address to 0x27 or 0x3F depending on your module, and size to 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change 0x27 to your actual LCD I2C address if needed

void setup() {
  Serial.begin(9600);        // Start serial communication
  lcd.begin();                // Initialize the LCD
  lcd.backlight();           // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Temp Monitor");
}

void loop() {
  int analogValue = analogRead(lm35Pin); // Read analog value (0-1023)
  
  // Convert to voltage (assuming 5V reference)
  float voltage = analogValue * (5.0 / 1023.0); 
  
  // LM35 gives 10mV per degree Celsius
  float temperatureC = voltage * 100.0;

  // Serial output
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  // LCD output
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureC, 1); // Show one decimal place
  lcd.print((char)223); // Print degree symbol
  lcd.print("C     ");  // Extra spaces to clear old data

  delay(1000); // Wait 1 second
}

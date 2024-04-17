#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define PIR_PIN 2 // PIR sensor pin
#define GAS_SENSOR_PIN A3 // Gas sensor pin
#define RELAY_PIN 3 // Relay 


#define BUZZER_PIN 4 // Buzzer pin

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(9600);
  pinMode(PIR_PIN, INPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.init();                      // Initialize the LCD
  lcd.backlight();                 // Turn on the backlight
  lcd.setCursor(0, 0);
  lcd.print("Worker's Safety");   // Print a message to the LCD
  lcd.setCursor(0, 1);
  lcd.print("Monitor System");   // Print a message to the LCD
  delay(3000);
  lcd.clear();

}

void loop() {

  int MotionValue = digitalRead(PIR_PIN) ;
  // Read gas sensor value
  int gasValue = analogRead(GAS_SENSOR_PIN);
  // float voltage = (gasValue / 1024.0) * 5.0;
  // float ppm = (voltage / 5.0) * 10000; // Convert to parts per million (ppm)
  
  lcd.setCursor(0, 1);
  lcd.print("Pollution: ");
  lcd.print(gasValue);
  
  // Check PIR sensor
  if (MotionValue == 1) {
    digitalWrite(RELAY_PIN, HIGH); // Turn off relay
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Object detected!"); // Print accident message
    digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
 
  } 
  // Check gas pollution level
  else if (gasValue > 600) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("High Pollution!"); // Print high pollution message
    PollutionIndicator(); 

  }else
   {
    lcd.clear();
    digitalWrite(RELAY_PIN, LOW); // Turn on relay
    digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
  }
  Serial.println("gas: " + String(gasValue));
  Serial.println("PIR: " + String(MotionValue));

  delay(500); // Wait for 1 second before next iteration
}
void PollutionIndicator() {
  // Generate a pulsating tone
  for (int i = 200; i <= 2000; i += 200) {
    tone(BUZZER_PIN, i); // Start tone at frequency i
    delay(150); // Tone duration
    noTone(BUZZER_PIN); // Turn off tone
    delay(50); // Pause between tones
  }
}
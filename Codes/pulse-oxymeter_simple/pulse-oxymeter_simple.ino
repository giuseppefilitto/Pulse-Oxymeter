
#include <LiquidCrystal.h>// LCD MONITOR
#include <Wire.h> // SDA (data line) and SCL (clock line)
#include "MAX30100_PulseOximeter.h" //SENSOR

#define PERIOD 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;


/*A +5V
 *K GND
 *VSS GND
 *VDD +5V
 *RW  GND
 *V0 to 10k resistor
  */

//                RS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//



void setup() {
  
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter...");
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  delay(3000);
  lcd.clear();
 
 //
 //
 //
 //
 if (!pox.begin()){
  Serial.println("FAILED");
  for(;;);
  }
else {
  Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);


  
}

void loop() {
  // 
  pox.update();
  if(millis()-tsLastReport > PERIOD){
    Serial.print("BPM :");
    Serial.print(pox.getHeartRate());
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("BPM :");
    lcd.print(pox.getHeartRate());
    Serial.print("bpm/ SpO2:");
    Serial.print(pox.getSpO2());
    Serial.println("%");
    lcd.setCursor(0, 1);
    lcd.print("SpO2:");
    lcd.print(pox.getSpO2());
    lcd.print("%");
  

    tsLastReport = millis(); }
  

}

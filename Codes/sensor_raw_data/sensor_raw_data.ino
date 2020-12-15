#include <LiquidCrystal.h>
#include <MAX30100.h>
#include <Wire.h>

// Sampling is tightly related to the dynamic range of the ADC.
// refer to the datasheet for further info
#define SAMPLING_RATE                       MAX30100_SAMPRATE_100HZ
// The LEDs currents must be set to a level that avoids clipping and maximises the
// dynamic range
#define IR_LED_CURRENT                      MAX30100_LED_CURR_11MA 
#define RED_LED_CURRENT                     MAX30100_LED_CURR_11MA

// The pulse width of the LEDs driving determines the resolution of
// the ADC (which is a Sigma-Delta).
// set HIGHRES_MODE to true only when setting PULSE_WIDTH to MAX30100_SPC_PW_1600US_16BITS
#define PULSE_WIDTH                         MAX30100_SPC_PW_1600US_16BITS
#define HIGHRES_MODE                        true


// Instantiate a MAX30100 sensor class and LCD screen

MAX30100 sensor;
/*A +5V
 *K GND
 *VSS GND
 *VDD +5V
 *RW  GND
 *V0 to 10k resistor
  */

//                RS  E  D4 D5  D6 D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


void setup()
{
    Serial.begin(115200);
    lcd.begin(16, 2);
    

    Serial.print("Initializing MAX30100..");
    lcd.print("Initializing...");
    delay(2000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Getting raw data");
        lcd.setCursor(0,1);
        lcd.print("Open plotter");
        

    // Initialize the sensor
    // Failures are generally due to an improper I2C wiring, missing power supply
    // or wrong target chip
    if (!sensor.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }

    // Set up the wanted parameters
    sensor.setMode(MAX30100_MODE_SPO2_HR);
    sensor.setLedsCurrent(IR_LED_CURRENT, RED_LED_CURRENT);
    sensor.setLedsPulseWidth(PULSE_WIDTH);
    sensor.setSamplingRate(SAMPLING_RATE);
    sensor.setHighresModeEnabled(HIGHRES_MODE);
}

void loop()
{
    uint16_t ir, red;

    sensor.update();

       

    while (sensor.getRawValues(&ir, &red)) {
        Serial.print(ir);
        Serial.print('\t');
        Serial.println(red);
     
         }
}

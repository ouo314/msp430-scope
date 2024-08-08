/*Development Log: 
Debugging and testing hardware. The ADC seems to have some issues; I might need a 1uF capacitor to filter out noise.

I tried not using the ESP32's IO to generate test signals directly, but instead used a variable resistor. 
The results seem to work normally, but if the ADC pin is left disconnected, it still shows a sine wave.
Suspected it might be a voltage issue.
It seems to be a pin issue. After switching to output through IO2, it worked normally.

 */
#include <driver/adc.h>
#include "esp_adc_cal.h"
#include <analogWrite.h>  

const int pwmPin = 2;
const int pwmFrequency = 1000;  
const int pwmResolution = 8;
const int samplesPerStep = 50;
esp_adc_cal_characteristics_t adc_chars;

void setup() {
  Serial.begin(115200);
  
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);  
  
  ledcSetup(0, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin, 0);
  //pinMode(2,OUTPUT);
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
}

void loop() {
  for (int i = 0; i < 256; i++) {
    ledcWrite(0, i);  
    
    long sum = 0;
    for (int j = 0; j < samplesPerStep; j++) {
      int val = adc1_get_raw(ADC1_CHANNEL_0);  
      sum += val;
      delayMicroseconds(100);
    }
    int avgAdcValue = sum / samplesPerStep; 
    
    uint32_t voltage = esp_adc_cal_raw_to_voltage(avgAdcValue, &adc_chars);
    
    Serial.print("PWM: ");
    Serial.print(i);
    Serial.print(" ADC: ");
    Serial.print(avgAdcValue);
    Serial.print(" Voltage: ");
    Serial.print(voltage);
    Serial.println(" mV");
    
    delay(10);
  }
  delay(100);
}

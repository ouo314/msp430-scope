#include <driver/adc.h>
#include "esp_adc_cal.h"

const int pwmPin = 39;
const int pwmFrequency = 10;  
const int pwmResolution = 8;
const int samplesPerStep = 50;


esp_adc_cal_characteristics_t adc_chars;

void setup() {
  Serial.begin(115200);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);
  ledcSetup(0, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin, 0);
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
    int scaledAdcValue = map(avgAdcValue, 0, 4095, 0, 255);
    Serial.print("PWM: ");
    Serial.print(i);
    Serial.print(" ADC: ");
    Serial.println(scaledAdcValue);
  }

  delay(100);
}

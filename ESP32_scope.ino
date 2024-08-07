
const int analogPin = 34;    
const int pwmPin = 25;       

// 設置PWM參數
const int pwmFrequency = 1000; 
const int pwmResolution = 8;  
const int pwmDutyCycle = 128;  

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  ledcSetup(0, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin, 0);
  ledcWrite(0, pwmDutyCycle);
}

void loop() {
  int adcValue = analogRead(analogPin);
  Serial.println(adcValue);  
  delay(10); 
}

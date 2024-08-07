const int analogPin = 36;    
const int pwmPin = 39;       

const int pwmFrequency = 1000; 
const int pwmResolution = 8;  
const int pwmDelay = 10;      

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);   
  ledcSetup(0, pwmFrequency, pwmResolution);
  ledcAttachPin(pwmPin, 0);
}

void loop() {
  for(int i = 0; i < 256; i++) {
    ledcWrite(0, i);          
    int adcValue = analogRead(analogPin); 
    Serial.print("PWM: ");
    Serial.print(i);
    Serial.print(" ADC: ");
    Serial.println(adcValue);  
    delay(pwmDelay);          
  }
  
  delay(100);                
}

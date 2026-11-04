
int sensorValue = 0; 
  int sensorPin = A0; 
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:



}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);

}

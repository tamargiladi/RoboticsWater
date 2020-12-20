#include <DHT.h>
#define Type DHT11
#define RELAY 3 
void getValuesToArr(DHT HT,int sensorPin,int sensorPin1,int sensorPin2,float res*)
{
  int sensorValue = 0; // variable to store the value coming from the sensor
  int sensorValue1=0;
  int sensorValue2 = 0;
  humidity=HT.readHumidity();
  tempC=HT.readTemperature();
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  sensorValue = map(sensorValue,550,0,0,100);
  sensorValue1 = analogRead(sensorPin1); // read the value from the sensor
  sensorValue1 = map(sensorValue1,550,0,0,100);
  sensorValue2=analogRead(sensorPin2);
  res[0]=humidity;
  res[1]=tempC;
  res[2]=sensorValue;
  res[3]=sensorValue1;
  res[4]=sensorValue2;
  return();
}

int sensePin=2;
DHT HT(sensePin,Type);
float humidity;
float tempC;
float tempF;
bool toPlant=False;
int sensorPin = A0; // select the input pin for LDR
int sensorPin1 = A1;
int sensorPin2=A2;
int sensorValue = 0; // variable to store the value coming from the sensor
int sensorValue1=0;
int sensorValue2 = 0;
void setup() {
Serial.begin(9600); //sets serial port for communication
pinMode(RELAY, OUTPUT);
HT.begin();
delay(500);
}
void loop() {
humidity=HT.readHumidity();
tempC=HT.readTemperature();
Serial.print("humidity: ");
Serial.println(humidity);
Serial.print(" Temperature C ");
Serial.print(tempC);
Serial.println(" C ");
sensorValue = analogRead(sensorPin); // read the value from the sensor
sensorValue = map(sensorValue,550,0,0,100);
Serial.println("ground moister sensor no1:");
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
sensorValue1=analogRead(sensorPin1);
sensorValue1=map(sensorValue1,550,0,0,100);
Serial.println("ground moister sensor no2:");
Serial.println(sensorValue1);
sensorValue2=analogRead(sensorPin2);
Serial.println("light value:");
Serial.println(sensorValue2);
toPlant=shouldIopenWater(humidity,tempC,sensorValue,sensorValue1,sensorValue2);
while (shouldIopenWater==True):
  {
    digitalWrite(RELAY, HIGH);
  }
  delay(3000);
digitalWrite(RELAY, LOW);
delay(3000);

delay(1000);

}

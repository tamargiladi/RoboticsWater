#include <DHT.h>
#define Type DHT11
#define RELAY 3 

int sensePin=2;
DHT HT(sensePin,Type);
float humidity;
float tempC;
float tempF;
float res[5];
char *sensorName[]={"humidity:","temperature:","first ground moisture:","second ground moisture:","light:"};
int sensorPin = A0; // select the input pin for LDR
int sensorPin1 = A1;
int sensorPin2=A2;
int sensorValue = 0; // variable to store the value coming from the sensor
int sensorValue1=0;
int sensorValue2 = 0;
void getValuesToArr(DHT HT,int sensorPin,int sensorPin1,int sensorPin2,float res[])
{
  
  humidity=HT.readHumidity();
  tempC=HT.readTemperature();
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  sensorValue = map(sensorValue,550,0,0,100);
  sensorValue1 = analogRead(sensorPin1); // read the value from the sensor
  sensorValue1 = map(sensorValue1,550,0,0,100);
  sensorValue2=analogRead(sensorPin2);
  res[0]=humidity;
  res[1]=tempC;
  res[2]=sensorValue;//first ground moisture sensor
  res[3]=sensorValue1;//second ground moisture sensor
  res[4]=sensorValue2;//light sensor
  return;
}

void setup() 
{
  Serial.begin(9600); //sets serial port for communication
  pinMode(RELAY, OUTPUT);
  HT.begin();
  delay(500);
}
void loop() 
{
  humidity=HT.readHumidity();
  tempC=HT.readTemperature();
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  sensorValue = map(sensorValue,550,0,0,100);
  sensorValue1=analogRead(sensorPin1);
  sensorValue1=map(sensorValue1,550,0,0,100);
  sensorValue2=analogRead(sensorPin2);
  getValuesToArr(HT,sensorPin,sensorPin1,sensorPin2,res);
  digitalWrite(RELAY, HIGH);
  delay(3000);
  digitalWrite(RELAY, LOW);
  delay(3000);

  int i=0;
  for (i=0;i<5;i++)
  {
    Serial.print(sensorName[i]);
    Serial.println(res[i]);
  }
}

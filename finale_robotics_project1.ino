#include <DHT.h>
#define Type DHT11
#define RELAY 9
const int s1 = 10;
const int s2 = 11;
const int s3 = 12;
const int s4 = 13;
int motorSpeed = 1500; // motor speed between 1000-4000. small number is bigger speed 
void openTap() 
{
  int watring_time=50000;
  digitalWrite(RELAY, HIGH);
  delay(watring_time);
  digitalWrite(RELAY, LOW);
  return;
}
void motorOff(){ // turn off motor
 digitalWrite(s1, LOW); 
 digitalWrite(s2, LOW); 
 digitalWrite(s3, LOW); 
 digitalWrite(s4, LOW); 
}

void back(){ // function to move 1 step back
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, HIGH); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, HIGH); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, HIGH); 
  digitalWrite(s4, HIGH); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, HIGH); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, HIGH); 
  delayMicroseconds(motorSpeed);
}

void forward(){ // function to move 1 step forward
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, HIGH); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, HIGH); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, HIGH); 
  digitalWrite(s4, HIGH); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, HIGH); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, HIGH); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, LOW); 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
  digitalWrite(s1, HIGH); 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW); 
  digitalWrite(s4, LOW); 
  delayMicroseconds(motorSpeed);
}
void openLeftTap()
{
  for (int i=0; i<=150; i++){ // go forward one circle, 509 steps
    back();
  }
  for (int i=0; i<=150; i++){ // go back one circle. 
    forward();
 }
 return;
}
void left_close_or_open(int res)
{
  if (res==1||res==0)
  {
    //close left tap
  }
  if (res==2)
  {
    //open right
  }
}

int day_or_night1(int light_sensor)
{
  if(light_sensor<300)
  {
    return(0);
  }
  else
  {
    return (1);
  }
}
int checkStatus(int leftHumidity,int rightHumdity,int light_sensor)
{
  int day_or_night=day_or_night1(light_sensor);
  //res possible outcomes:
  //0 - dont open taps
  //1 - open left tap
  //2 - open both taps
  int res=0;
  //sensor1=left tap
  //sensor2=right tap
  if (day_or_night==0)
  {
    if (leftHumidity>400 && rightHumdity>400)
    {
      res=2;
    }
    else if (leftHumidity>400 && rightHumdity<400)
    {
      res=1;
    }
  }
  return (res);
}
int sensePin=7;
DHT HT(sensePin,Type);
float humidity;
float tempC;
float tempF;
int day_or_night;
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
  sensorValue1 = analogRead(sensorPin1); // read the value from the sensor
  sensorValue2=analogRead(sensorPin2);
  res[0]=humidity;
  res[1]=tempC;
  res[2]=sensorValue1;//first ground moisture sensor
  res[3]=sensorValue2;//second ground moisture sensor
  res[4]=sensorValue;//light sensor
  return;
}

void setup() 
{
  Serial.begin(9600); //sets serial port for communication
  pinMode(RELAY, OUTPUT);
  HT.begin();
  delay(500);
  pinMode(s1, OUTPUT); 
 pinMode(s2, OUTPUT); 
 pinMode(s3, OUTPUT); 
 pinMode(s4, OUTPUT); 
}
void loop() 
{
  humidity=HT.readHumidity();
  tempC=HT.readTemperature();
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  sensorValue1=analogRead(sensorPin1);
  sensorValue2=analogRead(sensorPin2);
  getValuesToArr(HT,sensorPin,sensorPin1,sensorPin2,res);
  openLeftTap();
  digitalWrite(RELAY, LOW);
  delay(3000);
  digitalWrite(RELAY, HIGH);
  delay(3000);

  int i=0;
  for (i=0;i<5;i++)
  {
    Serial.print(sensorName[i]);
    Serial.println(res[i]);
  }
  
}

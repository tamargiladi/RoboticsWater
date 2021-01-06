// FINALE ROBOTICS PROJECT:
// Submitted By:
// Ran Ben Melech , ID: 204296792
// Tamar Giladi , ID: 207491549



#include <DHT.h> // lib for digital tmp and humidity sensor
#define Type DHT11
#define RELAY 9
int a;
#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(6,7); // RX | TX 
//define step motor connections and speed to arduino
const int s1 = 10;
const int s2 = 11;
const int s3 = 12;
const int s4 = 13;
int motorSpeed = 1500; // motor speed between 1000-4000. small number is bigger speed 

//a function that opens the main tap of the system
void openTap() 
{
  int watring_time=10000;
  digitalWrite(RELAY, HIGH);
  delay(watring_time);
  digitalWrite(RELAY, LOW);
  closeLeftTap(); 
  return;
}

//step motor
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

//using step motor back and forwerd to open and close the left tap
void openLeftTap()
{
  for (int i=0; i<=150; i++){ // go forward one circle, 509 steps
    forward();
  }
  return;
}
void closeLeftTap()
{
  for (int i=0; i<=150; i++){ // go back one circle. 
    back();
 }
 return;
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

//a function that will dictate if and which tap to open
int checkStatus(int leftHumidity,int rightHumdity)
{
  
  //res possible outcomes:
  //0 - dont open taps
  //1 - open left tap
  //2 - open both taps
  int res=0;
  //sensor1=left tap
  //sensor2=right tap

  if (leftHumidity<300 && rightHumdity<300)
  {
    res=2;
  }
  else if (leftHumidity>300 && rightHumdity<300)
  {
    res=1;
  }
  return (res);
}

//declaring varibles that we will use in loop or setup
int sensePin=5;//digital temp and humidity sensor pin
DHT HT(sensePin,Type);
float humidity;
float tempC;
float tempF;
int day_or_night;
float res[5];// array that contains all of the sensor reading values
int res1=0;
int leftRes=0;
String tempe;
String humidity1;
char *sensorName[]={"humidity:","temperature:","first ground moisture:","second ground moisture:","light:"};
int sensorPin = A0; // input pin for LDR
int sensorPin1 = A1;//input pin for first ground humidity sensor
int sensorPin2=A2;//input pin for second ground humidity sensor
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
  MyBlue.begin(9600);
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
  tempe=String(tempC);
  humidity1=String(humidity);
  sensorValue = analogRead(sensorPin); // read the value from the sensor
  sensorValue1=analogRead(sensorPin1);
  sensorValue2=analogRead(sensorPin2);
  delay(5000);
  getValuesToArr(HT,sensorPin,sensorPin1,sensorPin2,res);
  day_or_night=day_or_night1(sensorValue);
  if (day_or_night==0)
  {
    res1=checkStatus(sensorValue1,sensorValue2);
    if (res1==2||res1==1)
    {
      openLeftTap();
      delay(5000);
      openTap();   
      closeLeftTap(); 
    }
  }
  else
  {
    res1=checkStatus(sensorValue1,sensorValue2);
    //Serial.println(res1);
    if (res1==2||res1==1)
    {
      //lcd print low level of water need to plant and waiting for night
    }
  }
  int i=0;
  if (MyBlue.available()) 
  {
    String toSend=(String(humidity) + ',' + String(tempC)+ ',');
    a=MyBlue.read();
    a=int (a);
    char str[12];
    sprintf(str, "%f", humidity);
    char str1[12];
    sprintf(str1, "%f", tempC);
    //MyBlue.write(tempC);                                //Serial.write will send only one byte at a time  
     
    //MyBlue.write(humidity);                                //Serial.write will send only one byte at a time  
    delay(1000);
    Serial.print(tempC);
    //MyBlue.write(tempC);
    delay(100);  
    MyBlue.print(toSend);
    Serial.print(humidity);
    delay(400);  
    //Serial.print(str);
    //Serial.print(str1);


  if(a==2)

  {
      openLeftTap();
      openTap();
      closeLeftTap();
  }
  if (a==1)
  {
    closeLeftTap();
    openTap();
      
  }


}
  //for (i=0;i<5;i++)
  //{
    //Serial.print(sensorName[i]);
    //Serial.println(res[i]);
  //}
  
}

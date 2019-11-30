#include <SoftwareSerial.h>
int sensorPin1a = A0; 
int sensorPin2a = A1; 
int value=2;
int sensorPin1b = A2; 
int sensorPin2b = A3; 

int sensorPin1c = A4; 
int sensorPin2c = A5; 

int sensorValue1a;  
int sensorValue2a;

int sensorValue1b;  
int sensorValue2b;

int sensorValue1c;  
int sensorValue2c;

int sensorValue1ainit=1023;  
int sensorValue2ainit=1023;

int sensorValue1binit=1023;  
int sensorValue2binit=1023;

int sensorValue1cinit=1023;  
int sensorValue2cinit=1023; 
 
 
int drysum=0;
float drypercent=0;
int n=0;

int rainpin=3;
int rainvalue=100;

int txPin = 12;
int rxPin = 11;
SoftwareSerial BT(txPin,rxPin);

int flag=0;
  
void setup() {
 BT.begin(9600);
 Serial.begin(9600);
 pinMode(13, OUTPUT);
//pinMode(rxPin, INPUT);
//pinMode(txPin, OUTPUT);
  //pinMode(buzzerpin,OUTPUT);
}
void loop() 
{
  n=0;
rainvalue=digitalRead(rainpin);
Serial.println(rainvalue);

//FOR THE RESET CONDITION
if(BT.available())
{
  Serial.println("MILA");
  value=BT.read();

  if(value==50)
  {
    Serial.println("RESET MILA");
      flag=0;
      n=value;
    // tone(7,100000);
      value=2;
  }
  if(value ==100)
  {
     Serial.println("PAUSE MILA");
    flag=3;
    Serial.println(flag);
    Serial.println(flag);
    //  tone(7,100000);
    value=1;
  }
 if(value==25)
 {
  value=2;
 // tone(7,100000);
  
 }
 
}
if(value==2)
{
 Serial.println("ayaa");
sensorValue1ainit = analogRead(sensorPin1a);

sensorValue2ainit = analogRead(sensorPin2a);

sensorValue1binit = analogRead(sensorPin1b);

sensorValue2binit = analogRead(sensorPin2b);

//sensorValue1cinit = analogRead(sensorPin1c);

sensorValue2cinit = analogRead(sensorPin2c);
value=5;
    
  }
  drysum=0;
  if(!(sensorValue1ainit<=1023 and sensorValue1ainit>=1000))
  {
    sensorValue1a = analogRead(sensorPin1a); 
    Serial.println(sensorValue1a);
    drysum+=sensorValue1a; 
    n++;   
  }
    if(!(sensorValue2ainit<=1023 and sensorValue2ainit>=1000))
  {
    sensorValue2a = analogRead(sensorPin2a); 
    Serial.println(sensorValue2a);
    drysum+=sensorValue2a;  
    n++;  
  }
    if(!(sensorValue1binit<=1023 and sensorValue1binit>=1000))
  {
    sensorValue1b = analogRead(sensorPin1b); 
    Serial.println(sensorValue1b);
    drysum+=sensorValue1b;    
    n++;
  }
    if(!(sensorValue2binit<=1023 and sensorValue2binit>=1000))
  {
    sensorValue2b = analogRead(sensorPin2b); 
    Serial.println(sensorValue2b);
    drysum+=sensorValue2b;  
    n++;  
  }

    if (!(sensorValue2cinit<=1023 and sensorValue2cinit>=1000))
  {
    sensorValue2c = analogRead(sensorPin2c); 
    Serial.println(sensorValue2c);
    drysum+=sensorValue2c;
    n++;    
  }
  Serial.println(n);
//  Serial.println(drysum);
  drypercent=(float(drysum)/float(n)*0.2841)-191;
 // Serial.println(drypercent);
  //BT.print(rainvalue);
  if(flag==0 and rainvalue==0 and n>0)
  {
    Serial.println("raining");
    BT.print("RAINING");
    //tone(buzzerpin,1000);
    flag+=1;
  }
  
  else 
  {
    if(n==0)
    {
      BT.print(0); 
    }
   //Until data is being found in Serial, turn on serial on Bluetooth
   Serial.println(drypercent);
     BT.print(drypercent);   
  }  

    delay(1200); 
}

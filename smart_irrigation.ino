#include<SoftwareSerial.h>
SoftwareSerial Serial1(2,3);
String str="";

int relay = 10;
#define sensor 7

void setup()
{
  
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(relay, OUTPUT);
  pinMode(sensor, INPUT_PULLUP);
  Serial.println("Water Irrigaton");
  delay(2000);
  Serial.println("Circuit Digest");
  Serial.println("Welcomes You");
  delay(2000);
  gsmInit();
  Serial.println("System Ready");
}

void loop()
{
    Serial.println("Automatic Mode    ");
    if(digitalRead(sensor)==1)
    {
      delay(1000);
      if(digitalRead(sensor)==1)
      {
        sendSMS("Low Soil Moisture detected. Motor turned ON");
     

        Serial.println("Motor ON    ");
        digitalWrite(relay, HIGH);
        delay(2000);
       
      }
    }

    else if(digitalRead(sensor)==0 )
    {
      delay(1000);
      if(digitalRead(sensor)==0)
      {
        sendSMS("Soil Moisture is Normal. Motor turned OFF");
        digitalWrite(relay, LOW);
        
        Serial.println("Motor OFF");
        
        Serial.println("Motor OFF");
        delay(2000);
      
      }
    }
}
 
void sendSMS(String msg)
{
  
  Serial.println("Sending SMS");
  Serial1.println("AT+CMGF=1");
  delay(500);
  Serial1.print("AT+CMGS=");
  Serial1.print('"');
  Serial1.print("+919962825788");    // number
  Serial1.print('"');
  Serial1.println();
  delay(500);
  Serial1.println(msg);
  delay(500);
  Serial1.write(26);
  delay(1000);
  
  Serial.println("SMS Sent");
  delay(1000);
  
}

void gsmInit()
{
  Serial.println("Finding Module..");
  boolean at_flag=1;
  while(at_flag)
  {
    Serial1.println("AT");
    while(Serial1.available()>0)
    {
      if(Serial1.find("OK"))
      at_flag=0;
    }
    delay(1000);
  }
  Serial1.println("ATE0");
  
  Serial.println("Finding Network..");
  boolean net_flag=1;
  while(net_flag)
  {
    Serial1.println("AT+CPIN?");
    while(Serial1.available()>0)
    {
      if(Serial1.find("READY"))
      net_flag=0;
      break;
    }
    delay(1000);
  }
   Serial1.println("AT+CNMI=2,2,0,0,0");
   delay(1000);
   Serial1.println("AT+CMGF=1");
   delay(1000);
   Serial1.println("AT+CSMP=17,167,0,0");
   
   Serial1.flush();
}

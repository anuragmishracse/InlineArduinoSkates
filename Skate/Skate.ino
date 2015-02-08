#include <LiquidCrystal.h>//Library for LCD
 
#include <dht.h>// Library for DHT11 sensor

#define dht_dpin A1
#define echoPin 9 // Echo Pin
#define trigPin 8 // Trigger Pin
dht DHT;
long duration, distance;
int LDR = 0;
int LDRValue = 0;
double c =0;
double v=0;
int past=100;
unsigned long time;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  delay(300);
  pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
  Serial.println("Humidity\t\tTemperature\n\n");
  delay(700);
  digitalWrite(13,HIGH);
  lcd.begin(16, 2);
  lcd.print("HEY There!");
  lcd.setCursor(0, 1);
  lcd.print("Initialising....");
  lcd.setCursor(0,0);
}
void loop()
{
   c=0;
   DHT.read11(dht_dpin);
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    digitalWrite(trigPin, LOW);
 
    duration = pulseIn(echoPin, HIGH);
    distance = duration*0.0170145;
     if(distance>0 && distance<15)
     {
        Serial.print("Humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("Temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("*C  ");
      time=millis();
   time=time/1000;
   while(((millis()/1000)-time)<=2)
   {
      LDRValue=analogRead(LDR);
     if(past==100 &&LDRValue<=70)
      {
        past=0;
      }
      else if(past==0 &&LDRValue>70)
      {
        past=100;
        c++;
      }
   }
   
   c=(c*60)/16;
   v=c*0.072*3.14;
   v/=60;
   v=v*18;
   v/=5;
   lcd.clear();
  lcd.print("Speed:");
  lcd.print(v);
  lcd.print(" km/hr");
  lcd.setCursor(0,1);
  lcd.print("T:");
  lcd.print(DHT.temperature);
  lcd.print(" H:");
  lcd.print(DHT.humidity);
  lcd.print("%");
  lcd.setCursor(0,0);
   Serial.print("RPM of wheels  : ");
   Serial.println(c);  
  Serial.print("Linear Speed : ");
   Serial.print(v);
   Serial.println(" km/hr");
     }
 }

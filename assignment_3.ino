#include<DHT.h>
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
int freq=5000;
int ledchannel=0;
int ledresolution=8;
int t2=28;
void setup()
{
  
  pinMode(2,OUTPUT);  // light
  pinMode(15,OUTPUT); // fan
  pinMode(4,INPUT);
  ledcSetup(ledchannel,freq,ledresolution);
  ledcAttachPin(15,ledchannel);
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  dht.begin();
}
void loop()
{
 
  delay(6000);
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  float f=dht.readTemperature(true);
  int ldr=analogRead(4);
  if(isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("dht failed");
  }
  else
  {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Temparature: ");
    Serial.print(t);
    Serial.println(" °C");
    Serial.print("Temp in F: ");
    Serial.print(f);
    Serial.println(" °F"); 
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println(" ");
    display.print("intensity= ");
    display.println(ldr);
    display.print("Humidity: ");
    display.print(h);
    display.println("%");
    display.print("Temparature: ");
    display.print(t);
    display.println(" Celsius");
    
    display.display(); 
    
    if(ldr<=3800)
    {
      digitalWrite(2,LOW);
      Serial.println("led is off");      
    }
    else
    {
      digitalWrite(2,HIGH);
      Serial.println("led is on");
      Serial.print("ldr value = ");
      Serial.println(ldr);
    }
    if(t>=t2)
    {
      int fs=(t-t2)*11.590;
      ledcWrite(ledchannel,fs);
      int fanspeed=fs*100/255;
      Serial.print("fan speed = ");
      Serial.print(fanspeed);
      Serial.println("%");
      
    }
    else
    {
      digitalWrite(15,LOW);
      Serial.println(" fan is off");
    }
  }
}

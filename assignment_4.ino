#include "BluetoothSerial.h"
int trigpin=26;
int echopin=27;
BluetoothSerial SerialBT;
void setup() {
  // put your setup code here, to run once:
 pinMode(4,OUTPUT);
Serial.begin(115200);
  Serial.println("data");
  delay(3000);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device has started, now you can pair it with bluetooth!");
pinMode(echopin,INPUT);
pinMode(trigpin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
digitalWrite(trigpin,HIGH);
delay(1000);
digitalWrite(trigpin,LOW);#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
int selected;
char supply;

const char turnON ='O';
const char turnOFF ='F';
const int LEDpin = 2;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); 
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("To turn ON WATER SUPPLY CHOOSE: O");  
  Serial.println("To turn OFF WATER SUPPLY CHOOSE: F"); 
  pinMode(LEDpin, OUTPUT);
 
}

void loop() {
    supply =(char)SerialBT.read();

  if (Serial.available()) {
    SerialBT.write(Serial.read());

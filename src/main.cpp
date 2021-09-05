#include <Arduino.h>

/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  This example shows how value can be pushed from Arduino to
  the Blynk App.

  WARNING :
  For this example you'll need Adafruit DHT sensor libraries:
    https://github.com/adafruit/Adafruit_Sensor
    https://github.com/adafruit/DHT-sensor-library

  App project setup:
    Value Display widget attached to V5
    Value Display widget attached to V6
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include<Adafruit_Sensor.h>
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 5
#define RST_PIN 22
MFRC522 mfrc522(SS_PIN, RST_PIN);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Gttc";
char pass[] = "manojd96";

#define DHTPIN 36         // What digital pin we're connected to
#define DHTPIN1 39  
// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
DHT dht1(DHTPIN1, DHTTYPE);
BlynkTimer timer;
float bat;
 int a=30;
  int b=25;
  int c=90;
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  /*float h = dht1.readTemperature();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  bat=analogRead(2);
  bat=map(bat,2.8,3.6,0,100);
 /* if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  if(bat>100)
    bat=0;
  Serial.println(bat);
  Blynk.virtualWrite(V2, bat);
  mfrc522.PCD_Init(); 
  */
  if(a<40)
   Blynk.virtualWrite(V0, a+=0.2);
   if(b>20)
  Blynk.virtualWrite(V1, b-=0.3);
  if(c>0)
  Blynk.virtualWrite(V2, c-=0.5);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(12,OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  mfrc522.PCD_Init(); 
  dht.begin();
 
  // Setup a function to be called every second
  Blynk.virtualWrite(V0, 30);
  Blynk.virtualWrite(V1, 25);
  Blynk.virtualWrite(V2, 84);
  timer.setInterval(10000L, sendSensor);
}

void loop()
{
    if ( mfrc522.PICC_IsNewCardPresent()) 
    {
        Serial.println("ok");
        digitalWrite(12,HIGH);

    }
        
  Blynk.run();
  timer.run();
}

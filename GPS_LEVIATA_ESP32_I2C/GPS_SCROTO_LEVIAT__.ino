#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Only needed for Arduino 1.6.5 and earlier
#include<SH1106.h> 
#include <BlynkSimpleEsp32.h>
float latitude , longitude;
String  lat_str , lng_str;
const char *ssid =  "Leandro";     // Enter your WiFi Name
const char *pass =  "Leandro123"; // Enter your WiFi Password
char auth[] = "tHDsXYvDVucy4dhr4oQu1f8yLcyGRPRD"; 
WidgetMap myMap(V0); 
LiquidCrystal_I2C lcd(0x27,20,4);
WiFiClient client;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);
void setup()
{
   lcd.init();
  
  Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V0, "clr"); 
}
void loop()
{
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        Serial.print("Latitude = ");
        Serial.println(lat_str);
        Serial.print("Longitude = ");
        Serial.println(lng_str);
        
        lcd.setBacklight(HIGH);
        lcd.setCursor(0,0);
        lcd.print("Lat: ");
        lcd.print(lat_str);
        lcd.setCursor(0,1);
        lcd.print("Lng: ");
        lcd.print(lng_str);       
        Blynk.virtualWrite(V0, 1, latitude, longitude, "Location");
      }
     delay(1000);
     Serial.println();  
    }
  }  
  Blynk.run();
}

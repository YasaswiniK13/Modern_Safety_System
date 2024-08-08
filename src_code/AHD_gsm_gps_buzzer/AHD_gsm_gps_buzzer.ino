#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

static const int GPS_RXPin = 19, GPS_TXPin =18;
static const uint32_t GPSBaud = 9600;
#define PIN_BUZZER 13
#define PIN_BUTTON 4

TinyGPSPlus gps;
SoftwareSerial ss(GPS_RXPin, GPS_TXPin);

void setup(){
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(3000);
  send_SMS();
  ss.begin(GPSBaud);
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  }

void loop(){
 if (digitalRead(PIN_BUTTON) == LOW) {
    digitalWrite(PIN_BUZZER,HIGH);
    delay(10000);
    updateSerial();
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 5);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 5);
      delay(1000);
    }
  }
}else{
    digitalWrite(PIN_BUZZER,LOW);
  }
}
void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    Serial2.write(Serial.read());
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());
  }
}
void send_SMS() //to send sms to a specified person
{
  Serial2.println("AT+CMGF=1");
  updateSerial();
  Serial2.println("AT+CMGS=\"+xxxxxxxxxxx\"");
  updateSerial();
  Serial2.print("I am in Danger");
  updateSerial();
  Serial.println();
  Serial.println("Message Sent");
  Serial2.write(26);
}

}

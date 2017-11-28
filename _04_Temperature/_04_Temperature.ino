#include<Wire.h>
#include<SSD1306Ascii.h>
#include<SSD1306AsciiWire.h>
#include<Adafruit_SHT31.h>

#define TRIGGER_PIN D8 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN D7 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define I2C_ADDRESS 0x3C

Adafruit_SHT31 sht31 = Adafruit_SHT31();

SSD1306AsciiWire oled;

float t;
float h;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  pinMode(TRIGGER_PIN , OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(Adafruit5x7);

  sht31.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  pinMode(ECHO_PIN, INPUT);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // convert the time into a distance
  long cm = (duration/2) / 29.1;
  long inches = (duration/2) / 74;
  Serial.println(cm);

  t = sht31.readTemperature();
  h = sht31.readHumidity();
  char temperature[10];
  dtostrf(t,1,1,temperature);
  char hum[10];
  dtostrf(h,1,1,hum);
  
  oled.clear();
  oled.set1X();
  oled.println("Temperture lah!");
  oled.println(String(temperature) + " hots");
  oled.println("Humidity lah!");
  oled.println(String(hum) + " wets");
 
  delay(500);

}

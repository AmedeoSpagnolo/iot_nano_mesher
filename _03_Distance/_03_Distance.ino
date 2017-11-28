#include<Wire.h>
#include<SSD1306Ascii.h>
#include<SSD1306AsciiWire.h>

#define TRIGGER_PIN D8 // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN D7 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define I2C_ADDRESS 0x3C

SSD1306AsciiWire oled;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  Wire.begin();

  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(Adafruit5x7);
  //Define Trigger pin and Echo Pin
  pinMode(TRIGGER_PIN , OUTPUT);
  pinMode(ECHO_PIN, INPUT);
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

  oled.clear();
  oled.set2X();
  oled.println(String(cm) + " cm");
  delay(500);

}

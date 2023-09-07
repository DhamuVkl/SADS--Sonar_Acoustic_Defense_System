#include <Arduino.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);
SoftwareSerial gsm(4, 5);

int ledPin = 7;  // LED
int pirPin = A1; // PIR Out pin
int pirStat = 0; // PIR status
int relayInput = 6;
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(relayInput, OUTPUT);
  XBee.begin(9600);
  Serial.begin(9600);
  gsm.begin(9600); // Begin serial communication with Arduino and SIM800L
}

void SendMessage() // Function to Send Message
{
  lcd.setCursor(0, 1);
  lcd.print("Sending Message");
  delay(1000);

  gsm.println("AT+CMGF=1"); // Sets the GSM Module in Text Mode
  delay(1000);

  gsm.println("AT+CMGS=\"+919080108892\"\r"); // Replace x with mobile number
  delay(1000);

  gsm.println("Device Triggered"); // The SMS text you want to send
  delay(100);

  gsm.println((char)26); // ASCII code of CTRL+Z
  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DEVICE ACTIVATED");
  lcd.setCursor(0, 1);
  lcd.print("Message SENT");
  delay(1000);
}


void loop()
{
  pirStat = digitalRead(pirPin);
  if (pirStat == HIGH)
  {                             // if motion detected
    digitalWrite(ledPin, HIGH); // turn LED ON
    digitalWrite(relayInput, HIGH);
    XBee.write("  Device Triggered  ");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DEVICE TRIGGERED");
    delay(1000);
    SendMessage();
    delay(5000);
  }
  else
  {
    digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
    digitalWrite(relayInput, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DEVICE  INACTIVE");
    delay(1000);
  }
}

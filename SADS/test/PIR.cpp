#include <Arduino.h>
int ledPin = 13; // LED
int pirPin = 7;  // PIR Out pin
int pirStat = 0; // PIR status
int relayInput = 5;
void setup()
{
    pinMode(ledPin, OUTPUT);
    pinMode(pirPin, INPUT);
    pinMode(relayInput, OUTPUT);
    Serial.begin(9600);
}
void loop()
{
    pirStat = digitalRead(pirPin);
    if (pirStat == HIGH)
    {                               // if motion detected
        digitalWrite(ledPin, HIGH); // turn LED ON
        digitalWrite(relayInput, HIGH);
        Serial.println("Hey I got you!!!");
    }
    else
    {
        digitalWrite(ledPin, LOW); // turn LED OFF if we have no motion
        digitalWrite(relayInput, LOW);
    }
}

#include <Arduino.h>
#include <SoftwareSerial.h>

// Create software serial object to communicate with SIM800L
SoftwareSerial gsm(4, 5); // SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
    // Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
    Serial.begin(9600);

    // Begin serial communication with Arduino and SIM800L
    gsm.begin(9600);

    Serial.println("Initializing...");
    delay(1000);

    gsm.println("AT"); // Once the handshake test is successful, it will back to OK
    updateSerial();

    gsm.println("AT+CMGF=1"); // Configuring TEXT mode
    updateSerial();
    gsm.println("AT+CMGS=\"+919080108892\""); // change ZZ with country code and xxxxxxxxxxx with phone number to sms
    updateSerial();
    gsm.print("Device Triggerd"); // text content
    updateSerial();
    gsm.write(26);
}

void loop()
{
}

void updateSerial()
{
    delay(500);
    while (Serial.available())
    {
        gsm.write(Serial.read()); // Forward what Serial received to Software Serial Port
    }
}

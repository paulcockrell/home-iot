#include <Arduino.h>
#include <SoftwareSerial.h>

const byte HC12RxdPin = 16;
const byte HC12TxdPin = 14;
const byte HC12SetPin = 12;
const byte OFF = HIGH;
const byte ON = LOW;

const long BAUD = 1200;

unsigned long timer = millis();

char serialByteIn;
char hc12ByteIn;
String serialReadBuffer = "";
String hc12ReadBufer = "";
boolean serialEnd = false;
boolean hc12End = false;
boolean commandMode = false;

SoftwareSerial HC12(HC12TxdPin, HC12RxdPin);

void setup() {
  hc12ReadBufer.reserve(64);
  serialReadBuffer.reserve(64);

  // Onboard LED
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(HC12SetPin, OUTPUT);
  digitalWrite(HC12SetPin, HIGH);

  delay(80); // 80 ms delay before operation per datasheet

  Serial.begin(BAUD);
  HC12.begin(BAUD);

  Serial.println("Ready!");
  digitalWrite(LED_BUILTIN, OFF);
}

void loop() {
  while(HC12.available()) {
    digitalWrite(LED_BUILTIN, ON);

    hc12ByteIn = HC12.read();
    Serial.print(hc12ByteIn);
    hc12ReadBufer += char(hc12ByteIn);
    if (hc12ByteIn == '\n') {
      hc12End = true;
      digitalWrite(LED_BUILTIN, OFF);
    }
  }

  while(Serial.available()) {
    serialByteIn = Serial.read();
    serialReadBuffer += char(serialByteIn);
    if (serialByteIn == '\n') {
      serialEnd = true;
    }
  }

  if (serialEnd) {
    // We have a command to send to the HC12
    if (serialReadBuffer.startsWith("AT")) {
      HC12.print(serialReadBuffer); // Send local command to remote HC12 before changing local HC12 settings
      delay(100);
      digitalWrite(HC12SetPin, LOW); // Enter command mode
      delay(100); // Allow chip time to enter command mode
      Serial.print(serialReadBuffer);
      HC12.print(serialReadBuffer);
      delay(500); // Wait 0.5s for response
      digitalWrite(HC12SetPin, HIGH); // Exit command / enter transparent mode
      delay(100); // Delay before proceeding
    } else {
      HC12.print(serialReadBuffer); // Transmit non-command message
    }

    serialReadBuffer = "";
    serialEnd = false;
  }

  if (hc12End) {
    if (hc12ReadBufer.startsWith("AT")) {
      digitalWrite(HC12SetPin, LOW); // Enter command mode
      delay(100);
      Serial.print(serialReadBuffer);
      HC12.print(hc12ReadBufer); // Write command to local HC12
      delay(500);
      digitalWrite(HC12SetPin, HIGH); // Exit command / enter transparent mode
      delay(100);
      HC12.println("Remote command executed"); // Ack
    } else {
      Serial.print(hc12ReadBufer); // Echo
    }

    hc12ReadBufer = "";
    hc12End = false;
  }
}
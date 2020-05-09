#include <Servo.h>
#include <MFRC522.h>

Servo servoLid;
Servo servoLatch;
MFRC522 sensorOpen(10, 9);
bool isOpen;

void setup() {
  Serial.begin(57600);
  while (!Serial);
  Serial.println("Starting up...");
  SPI.begin();
  sensorOpen.PCD_Init();
  delay(10);
  sensorOpen.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  
  servoLid.attach(7);
  servoLatch.attach(8);
  closeLid();
  lock();
  // unlock();
  // openLid();
}

void loop() {
  if (!sensorOpen.PICC_IsNewCardPresent()) {
    // Serial.println("No card present");
    delay(500);
    return;
  }

  if (!sensorOpen.PICC_ReadCardSerial()) {
    Serial.println("Card read failed");
    delay(500);
    return;
  }

  Serial.print("UID tag: ");
  String uuid = readUUID();
  Serial.println(uuid);
  
  if (uuid != "D4 37 43 73") { // card
  // if (uuid != "C0 4B 19 A4") { // fob
    Serial.println("Access denied!");
    delay(500);
    return;
  }
  
  Serial.println("Access granted!");
      
  if (isOpen) {
    closeLid();
    lock();
  } else {
    unlock();
    openLid();
  }

  delay(750);
}

void openLid() {
  Serial.println("Opening lid...");
  servoLid.write(0);
  awaitReposition();
  isOpen = true;
}

void closeLid() {
  Serial.println("Closing lid...");
  servoLid.write(107);
  awaitReposition();
  isOpen = false;
}

void lock() {
  Serial.println("Locking lid...");
  servoLatch.write(140);
  awaitReposition();
}

void unlock() {
  Serial.println("Unlocking lid...");
  servoLatch.write(70);
  awaitReposition();
}

void awaitReposition() {
  delay(300);
}

String readUUID() {
  String content= "";
  byte letter;
  for (byte i = 0; i < sensorOpen.uid.size; i++) 
  {
     content.concat(String(sensorOpen.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(sensorOpen.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content.substring(1);
}

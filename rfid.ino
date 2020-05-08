#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(10, 9);

void setup() {
	Serial.begin(9600);
	while (!Serial);
	SPI.begin();
	mfrc522.PCD_Init();
	delay(4);
	mfrc522.PCD_DumpVersionToSerial();
	Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}

void loop() {
	if (!mfrc522.PICC_IsNewCardPresent()) {
		return;
	}

	if (!mfrc522.PICC_ReadCardSerial()) {
		return;
	}

  Serial.print("UID tag: ");
  String uuid = readUUID();
  Serial.println(uuid);
  
  if (uuid == "D4 37 43 73")
  {
    Serial.println("Access granted!");
    Serial.println();
    delay(3000);
  }
 
 else   {
    Serial.println("Access denied");
    delay(3000);
  }
}

String readUUID() {
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  return content.substring(1);
}

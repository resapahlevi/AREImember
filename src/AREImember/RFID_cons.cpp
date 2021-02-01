#include "RFID_cons.h"

MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522::StatusCode status; 

byte buffer[18];  
byte size = sizeof(buffer);

uint8_t pageAddr = 0x06;

void RFIDInit() {
  SPI.begin();
  mfrc522.PCD_Init();
}

uint8_t WritetoTag(char *stringtotag) {

  if ( ! mfrc522.PICC_IsNewCardPresent()){
    return 0;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()){
    return 0;
  }
  
  memcpy(buffer, stringtotag, 16);

  for (int i = 0; i < 4; i++) {
    status = (MFRC522::StatusCode) mfrc522.MIFARE_Ultralight_Write(pageAddr + i, &buffer[i * 4], 4);
    if (status != MFRC522::STATUS_OK) {
      return 7;
    }
  }
  mfrc522.PICC_HaltA();
  return 9;
}

char *ReadtoTag() {
   if ( ! mfrc522.PICC_IsNewCardPresent()){
    return NULL;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()){
    return NULL;
  }
  byte Readbuffer[18];
  byte Readsize = sizeof(Readbuffer);
  char* blockdata = (char*)malloc(19);
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pageAddr, Readbuffer, &Readsize);
  if (status != MFRC522::STATUS_OK) {
    return NULL;
  }

  mfrc522.PICC_HaltA();
  strcpy(blockdata,((char*)Readbuffer));

  return blockdata;
}

uint8_t IsNewCardPresent(){
  return mfrc522.PICC_IsNewCardPresent();
}

uint8_t PICC_ReadcardSerial(){
  return mfrc522.PICC_ReadCardSerial();
}

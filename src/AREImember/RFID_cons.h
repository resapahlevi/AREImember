
#ifndef _RFID_CONS_H__
#define _RFID_CONS_H__

#include <SPI.h>
#include <MFRC522.h>


#define SS_PIN          2
#define RST_PIN         5

void RFIDInit(void);
uint8_t WritetoTag(char *stringtotag);
char * ReadtoTag();
uint8_t IsNewCardPresent();
uint8_t PICC_ReadcardSerial();

#endif

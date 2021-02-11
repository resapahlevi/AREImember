
#include "Disp_cons.h"
#include "BLE_cons.h"
#include "RFID_cons.h"

#define LEDON digitalWrite(12,HIGH);
#define LEDOFF digitalWrite(12,LOW);
#define TimeToSleep 300;

uint16_t timersleep = 0;

void setup() {
  RFIDInit();
  BLEInit();
  DisplayInit();
  drawLogoAreimember();
  delay(2000);
  pinMode(12, OUTPUT);
  LEDON;
}

void loop() {

  if (deviceConnected) {
    LEDOFF;
    if (blemode == readtag) {
      char *Readbuffer = ReadtoTag();
      if (Readbuffer != NULL) {
        sendtonotify(Readbuffer);
        free(Readbuffer);
      }
      blemode = nulltag;
    }
    else if (blemode == writetag) {
      drawFontFaceDemo("Write to tag");
    }
    else if (blemode == nulltag)
    {
      drawFontFaceDemo("Device Ready");
    }
  }
  else {
    char *Readbuffer = ReadtoTag();
    if (Readbuffer != NULL) {
      LEDON;
      drawFontFaceDemo(Readbuffer);
      free(Readbuffer);
      timersleep = 0;
    }
    timersleep++;
  }
  
  if (timersleep == 200) {
    drawFontFaceDemo("Sleep in \n 10s");
  }
  if (timersleep >= 300) {
    LEDOFF;
  }
  delay(100);
}

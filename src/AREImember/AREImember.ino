
#include "Disp_cons.h"
#include "BLE_cons.h"
#include "RFID_cons.h"

void setup() {
  Serial.begin(9600);
  RFIDInit();
  BLEInit();
  DisplayInit();
  drawLogoAreimember();
  delay(2000);
}

void loop() {

  if (deviceConnected) {
    if (blemode == readtag) {
      char *Readbuffer = ReadtoTag();
      if (Readbuffer != NULL) {
        Serial.print(Readbuffer);
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
      Serial.print(Readbuffer);
      drawFontFaceDemo(Readbuffer);
      free(Readbuffer);
    }
  }
  delay(1000);
}

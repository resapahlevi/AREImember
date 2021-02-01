
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
    ClearDisp();
    char *Readbuffer = ReadtoTag();
    if(Readbuffer != NULL){
      Serial.print(Readbuffer);
      sendtonotify(Readbuffer);
      free(Readbuffer);
    }
    


//    for (byte i = 0; i < sizeof(Readbuffer); i++) {
//      Serial.print(Readbuffer[i]);
//    }


    //    if (1)
    //    {
    //
    //      float tempAmbiente = 100;
    //
    //      sendtonotify("Squanix \n");
    //
    //    }
  }
  else {
    drawLogoAreimember();
  }
  delay(1000);
}

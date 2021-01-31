
#include "Disp_cons.h"
#include "BLE_cons.h"

void setup() {

  BLEInit();
  DisplayInit();
  drawLogoAreimember();
  delay(2000);

}

void loop() {

  if (deviceConnected) {
    ClearDisp();
    if (1)
    {

      float tempAmbiente = 100;

      sendtonotify("Squanix \n");

    }
  }
  else {
    drawLogoAreimember();
  }
  delay(1000);
}

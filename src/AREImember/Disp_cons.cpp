
#include "Disp_cons.h"

SSD1306Wire display(0x3c, SDA, SCL);

void DisplayInit(){
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void drawLogoAreimember() {

    display.drawXbm(0, 0, Areimember_Logo_width, Areimember_Logo_height, Areimember_Logo_bits);
    Displayed();
}

void ClearDisp(){
  display.clear();
  Displayed();
}

void Displayed(){
      display.display();
}
 


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

void drawFontFaceDemo(char *text) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_24);
    display.drawString(0,10, text);
    Displayed();
}

void drawTextFlowDemo() {
    display.setFont(ArialMT_Plain_10);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.drawStringMaxWidth(0, 0, 128,
      "Lorem ipsum\n dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor invidunt ut labore." );
}
 


#include "Disp_cons.h"

//SSD1306Wire display(0x3c, SDA, SCL);
TFT_eSPI display = TFT_eSPI();

void DisplayInit() {
  display.init();

  display.fillScreen(TFT_BLACK);
  display.setRotation(0);
}

void drawLogoAreimember() {

  display.drawXBitmap(64, 0, Areimember_Logo_bits, Areimember_Logo_width, Areimember_Logo_height, TFT_WHITE, TFT_RED);
}

void ClearDisp() {
  display.fillScreen(TFT_BLACK);
}

void drawFontFaceDemo(char *text) {
  ClearDisp();
  drawLogoAreimember();
  display.setTextSize(2);
  display.setTextColor(TFT_RED, TFT_BLACK);

  display.drawString(text, 0, 96, 4);
}

#include "FS.h"
#include <SPI.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#define CALIBRATION_FILE "/calibrationData"

void setup(void) {
  uint16_t calibrationData[5];
  bool calDataOK = false;

  Serial.begin(115200);
  Serial.println("starting");

  tft.init();

  tft.setRotation(0);           //adjust this to your display position
  tft.fillScreen((TFT_WHITE));

  //This output should match your display resolution
  Serial.printf("display pixel width=%d\r\n",tft.width());
  Serial.printf("display pixel height=%d\r\n",tft.height());

  tft.setCursor(20, 0, 2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);  tft.setTextSize(1);
  tft.println("calibration run");

  // check file system
  if (!SPIFFS.begin()) {
    Serial.println("formating file system");

    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists, and read it
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    File f = SPIFFS.open(CALIBRATION_FILE, "r");
    if (f) {
      if (f.readBytes((char *)calibrationData, 14) == 14) {
        calDataOK = true;
      }
      f.close();
    }
  }

  if (calDataOK) {
    Serial.println("calibration data valid");
    tft.setTouch(calibrationData);
  } 
  else {
    Serial.println("data not valid. recalibrate");
    tft.calibrateTouch(calibrationData, TFT_WHITE, TFT_RED, 15); //15 = size of the calibration square
    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calibrationData, 14);
      f.close();
    }
  }

  tft.fillScreen((TFT_WHITE));

}

void loop() {
  uint16_t x, y;
  static uint16_t color;
  
  //Display the coordinates and draw a colored pixel at the detected position
  if (tft.getTouch(&x, &y)) {

    tft.setCursor(5, 5, 2);
    tft.printf("x: %i     ", x);
    tft.setCursor(5, 20, 2);
    tft.printf("y: %i    ", y);

    tft.drawPixel(x, y, color);
    color += 155;
  }
}




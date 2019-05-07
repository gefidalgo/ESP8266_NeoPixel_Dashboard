#ifndef _MATRIX_H
#define _MATRIX_H

#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>
#include <Fonts/TomThumb.h>

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

//Constructor for the matrix, passinging in the height and width of the matrix as well as the Pin number.
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, LED_PIN,
    NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);

//Init the matrix, to start using it.
void matrixInit()
{
  matrix->setFont(&TomThumb);
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(brightness);
  matrix->fillScreen(matrix->Color(150, 150, 150));
  matrix->show();
  delay(100);
  matrix->fillScreen(0);
  matrix->show();
  x    = matrix->width();
}

//Runs evertime the msg or time needs to be displayed
void MSGEvent()
{
  if (State != START_STATE)
  {
    matrix->fillScreen(0);
    matrix->setCursor(x, 5);
    matrix->setTextColor(matrix->Color(red, green, blue));
    int len;
    if (State == MSG_STATE)
    {
      len = msg.length() * 6;
      matrix->print(msg);
    }
    if (State == TIME_STATE)
    {
      len = timeIs.length() * 6;
      matrix->print(timeIs);
    }

    if (--x < -len) {
      x = matrix->width();
    }
    if (alarmOn == true)
    {
      matrix->drawPixel(0, 0, matrix->Color(255, 0, 0));
    }
    if (blynkConnected==false)
    {
      matrix->drawPixel(0, 0, matrix->Color(255, 0, 0)); 
    }
    matrix->show();
    delay(textSpeed);
  }
}

#endif

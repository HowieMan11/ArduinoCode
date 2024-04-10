#ifndef tftButton_h
#define tftButton_h
#include <Arduino.h>
#include <timer.h>
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"

// Display Things
#define TFT_RST -1  // dont use a reset pin, tie to arduino RST if you like
#define TFT_DC 15
#define TFT_CS 14

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 50//110
#define TS_MINY 80
#define TS_MAXX 900// default 900
#define TS_MAXY 940

#define MINPRESSURE 125
#define MAXPRESSURE 1000

//Colors
#define backgroundColor 0x5AAB
#define white 0xFFFF
#define black 0x0000
#define buttonColor 0x035F
#define keypadColor 0xF800

class tftButton{
  public:
    tftButton();
    void setParams(int _x, int _y, int _xLen, int _ylen, int _color);
    void setCornerRadius(int _radius);
    void draw(Adafruit_HX8357 tft, bool hide);
    void setDelayTime(int _dt);
    void setBorderColor(int _color);
    void setValue(int _val);
    int getState(TouchScreen ts, Adafruit_HX8357 tft);
    void setTextSize(int _textSize);
    void setTextColor(int _color);
    void setText(char _text[]);
    void setCPvalue(int _val);
    void printCP(bool _x);
    void setColor(int _color);
    char *getText(void);
    void setActualValue(uint16_t _val);
    uint16_t getActualValue(void);
    void setMemLocation(int _x);
    int getMemLocation(void);
  
  private:
    int coordinates[2];
    int size[2];
    int touchPoint[3];
    int lastTouchPoint[3];
    int radius;
    int color;
    int borderColor;
    bool hasBorder;
    unsigned long lastT;
    unsigned long delayT;
    timer btnTimer;
    int value;
    int textSize;
    int textColor;
    char text[10];
    int CPvalue;
    bool printCPState;
    uint16_t actualValue;
    int memLocation;

};


#endif
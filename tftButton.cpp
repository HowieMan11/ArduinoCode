#include "Arduino.h"
#include <timer.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include "Adafruit_HX8357.h"
#include "TouchScreen.h"
#include <EEPROM.h>

#include "tftButton.h"

tftButton::tftButton(){
  delayT = 175;
  radius = 0;
  hasBorder = false;
  value = 0;
  textSize = 5;
  printCPState = 0;
  memLocation = 0;
}

int tftButton::getState(TouchScreen ts, Adafruit_HX8357 tft){
  bool isPressed = false;
  TSPoint p = ts.getPoint();
  if(p.z > MINPRESSURE && p.z < MAXPRESSURE){
    if(p.y < 1000){
      //Serial.print("x: ");Serial.println(p.x);
      //Serial.print("y: "); Serial.println(p.y);

      touchPoint[0] = map(p.y, TS_MAXX, TS_MINX, 0, tft.width());
      touchPoint[1] = map(p.x, TS_MINY, TS_MAXY, 0, tft.height());
      touchPoint[2] = p.z;
      unsigned long currentT = millis();

      if((touchPoint[0] >= coordinates[0]) && touchPoint[0] < coordinates[0] + size[0]){
        if((touchPoint[1] >= coordinates[1]) && touchPoint[1] < coordinates[1] + size[1]){
        // at this point we have pressed the button
          if(currentT - lastT > delayT){
            lastT = currentT;
            isPressed = true;
          }

        }
      }
    }
  }
  if(isPressed){return value;}
  return -1;
}

void tftButton::draw(Adafruit_HX8357 tft, bool hide){
  int _borderColor = borderColor;
  int _color = color;
  int _textColor = textColor;
  if(hide){
    _borderColor = backgroundColor;
    _color = backgroundColor;
    _textColor = backgroundColor;
  }
  if(radius != 0){
    tft.fillRoundRect(coordinates[0], coordinates[1], size[0], size[1], radius, _color);
    if(hasBorder){
      tft.drawRoundRect(coordinates[0], coordinates[1], size[0], size[1], radius, _borderColor);
      tft.drawRoundRect(coordinates[0]+1, coordinates[1]+1, size[0]-2, size[1]-2, radius, _borderColor);
    }
  }else{
    tft.fillRect(coordinates[0], coordinates[1], size[0], size[1], _color);
    if(hasBorder){
      tft.drawRect(coordinates[0], coordinates[1], size[0], size[1], _borderColor);
      tft.drawRect(coordinates[0]+1, coordinates[1]+1, size[0]-2, size[1]-2, _borderColor);
    }
  }
  tft.setCursor(coordinates[0]+10, coordinates[1]+10);
  tft.setTextColor(_textColor);tft.setTextSize(textSize);
  if(printCPState){
    tft.write(CPvalue);
  }else if(value > 9){
    tft.print(text);
  }else{
  tft.print(value);
  }
}

void tftButton::setText(char _text[]){
  strcpy(text, _text);
  value = 99;
}
void tftButton::setCPvalue(int _val){
  CPvalue = _val;
  value = 10;
}
void tftButton::setBorderColor(int _color){
  if(_color == -1){
    hasBorder = false;
  }else{
    borderColor = _color; 
    hasBorder = true;
  }
}
void tftButton::setParams(int _x, int _y, int _xLen, int _yLen, int _color){
  coordinates[0]=_x; coordinates[1]=_y;
  size[0]=_xLen; size[1]=_yLen;
  color = _color;
}

void tftButton::setCornerRadius(int _radius){radius = _radius;}
void tftButton::setDelayTime(int _dt){delayT = _dt;}
void tftButton::setValue(int _val){value = _val;}
void tftButton::setTextSize(int _textSize){textSize = _textSize;}
void tftButton::setTextColor(int _color){textColor = _color;}
char *tftButton::getText(void){return text;}
void tftButton::printCP(bool _x){printCPState = _x;}
void tftButton::setActualValue(uint16_t _val){
  actualValue = _val;
  EEPROM.put(memLocation, actualValue);
  };
uint16_t tftButton::getActualValue(void){return EEPROM.get(memLocation, actualValue);}
int tftButton::getMemLocation(void){return memLocation;}
void tftButton::setMemLocation(int _x){memLocation = _x;}
void tftButton::setColor(int _color){color = _color;}










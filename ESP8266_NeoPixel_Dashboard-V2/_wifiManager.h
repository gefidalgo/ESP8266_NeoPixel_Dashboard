#ifndef _WIFIMANAGER_H
#define _WIFIMANAGER_H

#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

WiFiManager wifiManager;


void wifiSmartConfigInit()
{
//first parameter is name of access point, second is the password
wifiManager.autoConnect();
}

void wifiReset()
{
  wifiManager.resetSettings();
  Blynk.virtualWrite(TEXT_SCROLL_BUTTON_WIDGET, 0);
  Blynk.virtualWrite(FX_BUTTON_WIDGET, 0);
  Blynk.virtualWrite(SHOW_TIME_BUTTON_WIDGET, 0);
  Blynk.virtualWrite(OTA_BUTTON_WIDGET, 0);
  matrix->fillScreen(0);
  matrix->setCursor(1, 1);
  matrix->setBrightness(brightness);
  matrix->setTextColor(matrix->Color(150, 150, 150));
  matrix->print("W");
  matrix->show();
  if (!wifiManager.startConfigPortal("Led-Matrix")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }
}

#endif

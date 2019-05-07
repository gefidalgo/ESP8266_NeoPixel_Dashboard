#ifndef _TIME_H
#define _TIME_H

#include <NTPClient.h>
#ifndef _WIFIUDP_H
#include <WiFiUdp.h>
#endif

void syncTime();

// Define NTP Client to get time
// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
// GMT -3 = -(3600 * 3);
// By default 'pool.ntp.org' is used with 60 seconds update interval and no offset

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, -10800);

void timeInit()
{
  timeClient.begin();
  syncTime();
}

void syncTime()
{
  timeClient.update(); // get the time from the NTP server
  unsigned long secsTillEpoch = timeClient.getEpochTime() - 946684800;
  RtcDateTime compiled = RtcDateTime(secsTillEpoch);
  printDateTime(compiled);
  Rtc.SetDateTime(compiled);
}

#endif

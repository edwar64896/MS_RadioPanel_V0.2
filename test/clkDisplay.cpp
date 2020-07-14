#include <Arduino.h>
#include <gspswitch.h>
#include <gspquad.h>
#include <gspflash.h>
#include <gspserialresponse.h>
#include <gspseven.h>

#include <Wire.h>
#include <RtcDS1307.h>

RtcDS1307<TwoWire> Rtc(Wire);

char datestring[10];
char timestring[10];

String printDate(const RtcDateTime& dt)
{
    snprintf_P(datestring, 
            10,
            PSTR("%02u%02u%04u"),
            dt.Month(),
            dt.Day(),
            dt.Year());

    return String(datestring);
}

String printTime(const RtcDateTime& dt)
{
    snprintf_P(timestring, 
            10,
            PSTR("%02u %02u %02u"),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );

    return String(timestring);

}

int display=0;


//data,clock,chipselect/load
gspSeven ld1(7,6,9);
gspSeven ld2(7,6,10);

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
 
  delay(500);

  Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    //printDateTime(compiled);
    //Serial.println();

    if (!Rtc.IsDateTimeValid()) 
    {
        if (Rtc.LastError() != 0)
        {
            // we have a communications error
            // see https://www.arduino.cc/en/Reference/WireEndTransmission for 
            // what the number means
            Serial.print("RTC communications error = ");
            Serial.println(Rtc.LastError());
        }
        else
        {
            // Common Causes:
            //    1) first time you ran and the device wasn't running yet
            //    2) the battery on the device is low or even missing

            Serial.println("RTC lost confidence in the DateTime!");
            // following line sets the RTC to the date & time this sketch was compiled
            // it will also reset the valid flag internally unless the Rtc device is
            // having an issue

            Rtc.SetDateTime(compiled);
        }
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) 
    {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) 
    {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    // never assume the Rtc was last configured by you, so
    // just clear them to your needed state
    Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low); 
}

int ii=0;

void loop() {
  // put your main code here, to run repeatedly:

      if (!Rtc.IsDateTimeValid()) 
    {
        if (Rtc.LastError() != 0)
        {
            // we have a communications error
            // see https://www.arduino.cc/en/Reference/WireEndTransmission for 
            // what the number means
            Serial.print("RTC communications error = ");
            Serial.println(Rtc.LastError());
        }
        else
        {
            // Common Causes:
            //    1) the battery on the device is low or even missing and the power line was disconnected
            Serial.println("RTC lost confidence in the DateTime!");
        }
    }

    RtcDateTime now = Rtc.GetDateTime();

    String dt=printDate(now);
    String tm=printTime(now);

    ld1.displayRtcDate(dt);
    ld2.displayRtcTime(tm);


//  ld1.displayNums("12345678");





}



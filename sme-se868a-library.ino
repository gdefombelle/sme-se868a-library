/*
    SmeGPS Library - Localization and Time Information
   
    This example shows how to retrieve the GPS localization information + Time:
    Latitude, Longitude,  Altitude, Time UTC

    It shows also the number of the satellites  are visible by the GPS receiver
    This information is useful to well understand the accuracy of the localization information

    created 27 July 2016
    include additional UTC and move methods  provided by Gabriel de Fombelle - line-up.io - gabriel.de.fombelle@gmail.com http://www.line-up.io
    This example is in the public domain
    https://github.com/gdefombelle
    
    SE868  more information available here:
    http://www.telit.com/products/product-service-selector/product-service-selector/show/product/jupiter-se868-as/

    
 */

#include <Wire.h>

#include "sl868a.h"
#include <Arduino.h>
int led_status = HIGH;

// the setup function runs once when you press reset or power the board
void setup() {
    SerialUSB.begin(115200);
    smeGps.begin();

}

// the loop function runs over and over again forever
void loop() {
    static unsigned loop_cnt = 0;
    unsigned int altitude = 0;
    unsigned char lockedSatellites = 0;
    double latitude = 0;
    double longitude = 0;
    unsigned int utc_hour =0;
    unsigned int utc_min = 0;
    unsigned int utc_sec = 0;
    unsigned utc_secDecimals = 0;
    unsigned utc_year =0;
    unsigned utc_month =0;
    unsigned utc_dayOfMonth =0;
    double speed_knots =0;
    double course = 0;
    sl868aCachedDataT data;

    delay(5);

    if (smeGps.ready()) {

        ledGreenLight(HIGH);

        altitude   = smeGps.getAltitude();
        latitude   = smeGps.getLatitude();
        longitude  = smeGps.getLongitude();
        lockedSatellites = smeGps.getLockedSatellites();
        // new getters
        utc_hour = smeGps.getUtcHour();
        utc_min = smeGps.getUtcMinute();
        utc_sec = smeGps.getUtcSecond();
        utc_secDecimals = smeGps.getUtcSecondDecimals();
        utc_year = smeGps.getUtcYear();
        utc_month = smeGps.getUtcMonth();
        utc_dayOfMonth = smeGps.getUtcDayOfMonth();
        speed_knots = smeGps.getSpeedKnots();
        course = smeGps.getCourse();
        // get cached data
        data = smeGps.getData();
        

        if ((loop_cnt % 200) == 0) {
            SerialUSB.println(" ");
            SerialUSB.print("Latitude    =  ");
            SerialUSB.println(latitude, 6);
            SerialUSB.print("Longitude   =  ");
            SerialUSB.println(longitude, 6);
            SerialUSB.print("Altitude    =  ");
            SerialUSB.println(altitude, DEC);
            SerialUSB.print("Satellites  =  ");
            SerialUSB.println(lockedSatellites, DEC);
            SerialUSB.print("Hour  =  ");
            SerialUSB.println(data.utc_hour, DEC);
            SerialUSB.print("Minute  =  ");
            SerialUSB.println(data.utc_min, DEC);
            SerialUSB.print("Second  =  ");
            SerialUSB.print(data.utc_sec, DEC);
            SerialUSB.print(".");
            SerialUSB.println(data.utc_sec_decimals, DEC);

            SerialUSB.print("Date  =  ");
            SerialUSB.print(data.utc_year, DEC);
            SerialUSB.print("/");
            SerialUSB.print(data.utc_month, DEC);
            SerialUSB.print("/");
            SerialUSB.print(data.utc_dayOfMonth, DEC);
            SerialUSB.println();

            SerialUSB.print("Speek (knots) = ");
            SerialUSB.println(speed_knots, DEC);
            SerialUSB.print("Course = ");
            SerialUSB.println(data.course, DEC);
        }
    } else {
        if ((loop_cnt % 200) == 0) {
            SerialUSB.println("Locking GPS position...");
            if (led_status == LOW) {
                led_status = HIGH;
            } else {
                led_status = LOW;
            }
        }
    }

    loop_cnt++;
    ledGreenLight(led_status);
}

//#include <SoftwareSerial.h>
#include <NMEAGPS.h>
#include <GPSport.h>
#include <TimeLib.h>
//#include "PF.h"
//#include "PetitSerial.h"

#define UTC_OFFSET 5.30  // set time zone offset, i.e. 1 = UTC+1
#define PWRPin 7      // SIM900 software power pin

// phone number for triggered notification
#define DEFAULT_NUMBER "+918825701687"

//FATFS fs;             // file system object - for reading SD card

// GSM variables
String textMessage;               // holds the last received text message
String number = DEFAULT_NUMBER;   // phone number from last text message
char sms_msg[160];                // holds the SMS reply text

// location variables
float Lat = 0, Long = 0;
boolean valid_location = false;   // initial valid location flag
uint8_t num_sat;
NeoGPS::Location_t prevFix;       // holds previous location for distance calculation
NMEAGPS  gps;                     // parses the GPS characters
gps_fix  fix;                     // holds on to the latest values

const char *googlePrefix = "http://maps.google.com/maps?q=";
const char *filename = "DIST.TXT";
const char *settings = "SETTINGS.TXT";

// time variables
NeoGPS::time_t timeFix;   // time object for current gps fix
char datePrint[13];
char timePrint[10];

// distance tracking variables
float totalDistance = 0; // in meters
// triggerdistance (odometer notification) is read from SD card on init
float triggerDistance = 4000000;

//SoftwareSerial SIM900( TXPin, RXPin );  // SIM900 Tx & Rx is connected to Arduino #8 & #9

void setup() {

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(3, HIGH);  // turn on power LED

  Serial.begin(9600);     // serial monitor

  /*  the "while (!serial)" construct below must only be enabled for
      debugging purposes when connected to a PC. If this is kept in the
      code the program will stop in a loop when connected to external
      power sources, as no serial connection will be established
  */

  // while (!Serial);     // wait for serial port to connect - for ATmega32u4 (Leonardo)

  Serial.begin(9600);     // SIM900 module on pins #8 and #9
  gpsPort.begin(9600);    // GPS receiver on Serial1 pins #0 and #1 - defined in GPSport.h

  // initialize the SD card and reads standard setting and accumulated distance
 // initializeSD();

  // power up SIM900 with software trigger
  //SIM900power();

  Serial.println( F("AT") );        // Handshaking with SIM900
  delay(500);
 updateSIM900();
  Serial.println( F("AT+CMGF=1") ); // Configuring TEXT mode
  delay(500);
  updateSIM900();
  Serial.println( F("AT+CNMI=1,2,0,0,0") ); // Decides how newly arrived SMS messages should be handled
  delay(500);
  updateSIM900();

  connectGPRS();
  updateSerial();
}

void loop() {

  while (gps.available( gpsPort )) {
    fix = gps.read();

    num_sat = fix.satellites;

    if (fix.valid.location) {
      digitalWrite(4, HIGH);  // sets GPS lock LED

      Lat =  fix.latitude();
      Long = fix.longitude();

      // saves the first "GPS lock" flag - we now have useful data
      if (Lat != 0 && Long != 0 && !valid_location) {
        valid_location = true;
        prevFix = fix.location;
      }
    }

    if (fix.valid.date && fix.valid.time)
    {
      timeFix = fix.dateTime;
      updateTime();
    }

    // update thinger.io and write values to SD card only for valid gps fix
    // typically at startup before gps has locked in coordinates first time
    if (valid_location)
    {

      // updates the distance travelled every 15 seconds
      static const unsigned long REFRESH_INTERVAL_UPD = 15000; // 15 seconds
      static unsigned long lastRefreshTime = millis();

//      if (millis() - lastRefreshTime >= REFRESH_INTERVAL_UPD)
//      {
//        lastRefreshTime += REFRESH_INTERVAL_UPD;
//
//        // calculates distance between current and previous fix in meters
//        float distanceDelta = prevFix.DistanceKm(fix.location) * 1000;
//
//        // only update if distance is greater than 10 meters and less than 10km
//        // 10km check is implemented to avoid erroneous data reading from GPS
//        if (distanceDelta > 10 && distanceDelta < 10000) {
//          totalDistance += distanceDelta;
//        }
//
//        // reset the calculation point for next loop (set "previous" location)
//        prevFix = fix.location;
//
//      }

      // writes distance travelled to SD card every 2 minutes
      // uploads coordinates to thinger.io every 2 minutes
      static const unsigned long REFRESH_INTERVAL_WRITE_SD = 120000UL; // 2 minutes
      static unsigned long lastRefreshTimeWriteSD = millis();

      if (millis() - lastRefreshTimeWriteSD >= REFRESH_INTERVAL_WRITE_SD)
      {
        lastRefreshTimeWriteSD += REFRESH_INTERVAL_WRITE_SD;

        // file write to SD card begin
        char buf[9];
        dtostrf(totalDistance, 8, 0, buf);

       // if (PF.open(filename)) Serial.println( F("error open file") );

//        while (1) {
//          UINT nr;
//          if (PF.writeFile(buf, sizeof(buf), &nr)) Serial.println( F("error write file") );
//          if (nr == sizeof(buf))
//          {
//            PF.writeFile( 0, 0, &nr);     // finalize write operation by writing a null pointer
//            break;
//          }
//        } // Petit FS has no "close" operation on file

        // next section transfers data to thinger.io IoT cloud with HTTP POST request.
        // only update thinger.io after first successful GPS lock

        char httpContent[60];
        char tempstrLong[10];
        char tempstrLat[10];

        dtostrf(Lat, 2, 6, tempstrLat);
        dtostrf(Long, 2, 6, tempstrLong);

        // data fields to thinger.io bucket. Access to bucket is given through URL authorization in the post function.
        // format is { "field1 name" : field1 , "field2 name" : field2 , "field3 name" : field3 } with exact byte count.
        sprintf(httpContent, "{ \"longitude\": %s , \"latitude\": %s , \"date\": \"%s %s\" }", tempstrLong, tempstrLat, datePrint, timePrint);

        char httpdataLen[20];

        // exact byte count for the content must be added to HTTPDATA
        // otherwise HTTP POST request is invalid, i.e. status 400 is retured.
        sprintf(httpdataLen, "AT+HTTPDATA=%i,10000", strlen(httpContent));

        postDataThinger(httpdataLen, httpContent);

      }
    }
  }

  // send SMS notification if the total distance exceeds configured limit
  if (totalDistance > triggerDistance) {
    char distanceTotalMsg[10];
    itoa( (totalDistance / 1000) , distanceTotalMsg, 10);
    sprintf(sms_msg, "Empty catchtank! Current distance: %skm", distanceTotalMsg);
    textMessage = "";
    number = DEFAULT_NUMBER;
    totalDistance = 0;

    sendSMS(sms_msg);
  }

  updateSerial();
}

void updateSerial()
{
  // read incoming buffer. reads content of any text message
  if (Serial.available() > 0) {
    textMessage = Serial.readString();
  }

  if (textMessage.indexOf("POS") >= 0) {

    extractSenderNumber();
    textMessage = "";

    char latPrint[10];
    dtostrf(Lat, 5, 6, latPrint);

    char LonPrint[10];
    dtostrf(Long, 5, 6, LonPrint);

    if (num_sat >= 3 && valid_location)
    {
      sprintf(sms_msg, "Current location: Lat: %s, Long: %s. %s%s,+%s\n", latPrint, LonPrint, googlePrefix, latPrint, LonPrint);
    }
    else if (num_sat < 3 && valid_location)
    {
      sprintf(sms_msg, "No gps fix. Last seen %s%sat: Lat: %s, Long: %s. %s%s,+%s\n",
              datePrint, timePrint, latPrint, LonPrint, googlePrefix, latPrint, LonPrint);
    }
    else if (!valid_location)
    {
      sprintf(sms_msg, "Tom not found. Maybe he is in North-Korea?");
    }

    sendSMS(sms_msg);
  }

  // returns the current total accumulated distance
  if (textMessage.indexOf("GETKM") >= 0 ) {
    char sms_msg[32];
    char distanceTotalMsg[10];
    itoa( (totalDistance / 1000) , distanceTotalMsg, 10);
    sprintf(sms_msg, "Current distance: %skm", distanceTotalMsg);
    textMessage = "";

    sendSMS(sms_msg);
  }

  // resets the distance counter to 0
  if (textMessage.indexOf("RESETKM") >= 0) {
    totalDistance = 0;
    char sms_msg[] = "Acknowledge: distance reset";
    textMessage = "";

    sendSMS(sms_msg);
  }

}

void SIM900power()
{
  // power up SIM900 board from pin #7 (default) -> 2sec. signal
  pinMode(PWRPin, OUTPUT);
  digitalWrite(PWRPin, LOW);
  delay(1000);
  digitalWrite(PWRPin, HIGH);
  delay(2000);
  digitalWrite(PWRPin, LOW);
  delay(15000);   // give module time to boot
}

void updateSIM900()
{
  // empty incoming buffer from SIM900 with read()
  delay(500);
  while (Serial.available())
  {
    // outputs buffer to serial monitor if connected
    Serial.write(Serial.read());
  }
}

void extractSenderNumber()
{
  uint8_t startPos = textMessage.indexOf("+", 6);
  uint8_t endPos = textMessage.indexOf(",");
  number = textMessage.substring(startPos, endPos - 1);
}

void sendSMS(char *content)
{
  // really crappy string conversion since I was too lazy to do proper
  // char handling in the first place.
  // SMS is returned to the sender number.
  char numberChar[number.length() + 1];
  number.toCharArray(numberChar, number.length() + 1);

  char cmd_sms[50];
  sprintf(cmd_sms, "AT+CMGS=%c%s%c", 0x22, numberChar, 0x22);

  Serial.println(cmd_sms);
  updateSIM900();
  Serial.print(content);
  updateSIM900();
  Serial.write(0x1A);
}

void connectGPRS()
{
  Serial.println( F("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"") );
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"") );
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+SAPBR=1,1") );
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+SAPBR=2,1") );
  delay(1000);
  updateSIM900();
}

void postDataThinger(char *httpDataLen, char* content)
{
  Serial.println( F("AT+HTTPINIT") );
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+HTTPPARA=\"CID\",1") );
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+HTTPPARA=\"URL\",\"https://backend.thinger.io/v3/users/RAJAGOPALANVEMPARALA/devices/test/callback/data?authorization=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEZXZpY2VDYWxsYmFja190ZXN0IiwidXNyIjoiUkFKQUdPUEFMQU5WRU1QQVJBTEEifQ.34eSQrIIn5GA0U-oXm36pH7hY4CZ95JYNEIwlBAvJDQ\"") );
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+HTTPPARA=\"CONTENT\",\"application/json\"") );
  delay(1000);
  updateSIM900();

  Serial.println(httpDataLen);
  delay(1000);
  updateSIM900();

  Serial.println(content);
  delay(1000);
  updateSIM900();

  Serial.println( F("AT+HTTPACTION=1") );
  delay(10000);
  updateSIM900();

  Serial.println( F("AT+HTTPTERM") );
  delay(1000);
  updateSIM900();
  Serial.println("Attempted to push data to thinger.io... please check the data bucket for the data");

}

// initialize SD card and retrieves stored distance value
void initializeSD()
{

  // first section read current distance from SD card

  char buf[10];   // buffer to hold retrieved distance value

  // Initialize SD card and file system.
//  if (PF.begin(&fs)) Serial.println( F("error begin file") );

  // Open file for read - saved accumulated total distance
  //if (PF.open(filename)) Serial.println( F("error open file") );
//
//  while (1) {
//    UINT nr;
//    if (PF.readFile(buf, sizeof(buf), &nr)) Serial.println( F("error read file") );
//    if (nr == sizeof(buf)) break;
//  }
  // no close function for Petit FS.

  // retrieves stored distance value to program
  totalDistance = atof(buf);

  // second section read odometer notification trigger value

  char bufTrigger[10];   // buffer to hold trigger value

 // if (PF.open(settings)) Serial.println( F("error open file") );

//  while (1) {
//    UINT nr;
//    if (PF.readFile(bufTrigger, sizeof(bufTrigger), &nr)) Serial.println( F("error read file") );
//    if (nr == sizeof(bufTrigger)) break;
//  }

  // retrieves odometer notification value
  triggerDistance = atof(bufTrigger);

}

// corrects time object with time zone offset
void updateTime()
{
  // set time from GPS data string
  setTime(timeFix.hours, timeFix.minutes, timeFix.seconds,
          timeFix.date, timeFix.month, timeFix.year);

  // calc current time zone time by offset value
  adjustTime(UTC_OFFSET * SECS_PER_HOUR);

  sprintf(datePrint, "%02d/%02d/%04d ", day(), month(), year());
  sprintf(timePrint, "%02d:%02d:%02d ", hour(), minute(), second());
}

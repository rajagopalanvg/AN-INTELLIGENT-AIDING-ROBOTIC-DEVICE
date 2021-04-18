#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <TMRpcm.h>
#include <SD.h> 

#define RXPIN 2
#define TXPIN 3

#define TERMBAUD  9600
#define GPSBAUD  4800

#define SD_ChipSelectPin 4  

float latitude,longitude;
float Lat,Long;

TMRpcm tmrpcm;
TinyGPS gps;
SoftwareSerial uart_gps(RXPIN, TXPIN);
void getgps(TinyGPS &gps);

void setup()
{
 
  // Sets baud rate of your terminal program
  Serial.begin(TERMBAUD);
  // Sets baud rate of your GPS
  uart_gps.begin(GPSBAUD);
 
  Serial.println("");
  Serial.println("GPS Shield QuickStart Example Sketch v12");
  Serial.println("       ...waiting for lock...           ");
  Serial.println("");
  
  tmrpcm.speakerPin = 9;                  //define speaker pin. 
                                          //you must use pin 9 of the Arduino Uno and Nano
                                          //the library is using this pin
  
  if (!SD.begin(SD_ChipSelectPin))       //see if the card is present and can be initialized
{    
    return;      
}
}

void loop()
{
  while(uart_gps.available())     // While there is data on the RX pin...
  {
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {
        getgps(gps);         // then grab the data.
      }
  }

  if(41.479133 <= Lat >= 41.493510 && -71.541359 <= Long >= -71.522058)
   {
     Serial.print("Lat/Long: ");
     //while(Serial.print(latitude,5).available())
      while(Serial.print(latitude,5))
     { 
      tmrpcm.setVolume(6);
      tmrpcm.play("test");  
     }
     
     Serial.print(", ");
     while(Serial.println(longitude,5))
     { 
      tmrpcm.setVolume(6);
      tmrpcm.play("test");  
     }
   }
}


void getgps(TinyGPS &gps)
{
  // To get all of the data into varialbes that you can use in your code,
  // all you need to do is define variables and query the object for the
  // data. To see the complete list of functions see keywords.txt file in
  // the TinyGPS and NewSoftSerial libs.
 
  // Define the variables that will be used
  float latitude, longitude;
  // Then call this function
  gps.f_get_position(&latitude, &longitude);
 
 // You can now print variables latitude and longitude
 
 /* Serial.print("Lat/Long: ");
  Serial.print(latitude,5);
  Serial.print(", ");
  Serial.println(longitude,5);
  */
}

#define trigPin1 A0
#define echoPin1 A1
#define trigPin2 A2
#define echoPin2 A3

int ALARM = 8;
long duration, distance, FIRSTSensor,SECONDSensor;

#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup()
{
  pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);

//pinMode(ALARM, OUTPUT);
//digitalWrite(ALARM, LOW);


for (int thisNote = 0; thisNote < 8; thisNote++)
{
    pinMode(ALARM, OUTPUT);
    digitalWrite(ALARM, LOW);

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);


    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    noTone(8);
}
}


void loop()
{
SonarSensor(trigPin1, echoPin1);
FIRSTSensor = distance;
SonarSensor(trigPin2, echoPin2);
SECONDSensor = distance;
//SonarSensor(trigPin3, echoPin3);
//THIRDSensor = distance;
/////////////////////////////////////////////////////////////
digitalWrite(ALARM, LOW);
//////////////////////////////////////////////////////////////////////////////////////
Serial.print("S1:");Serial.println(FIRSTSensor); delayMicroseconds(10);
Serial.print("S2:");Serial.println(SECONDSensor);delayMicroseconds(10);

if((FIRSTSensor >= 10) & (FIRSTSensor <= 50)) 
{
  digitalWrite(ALARM, HIGH);
  delay(500);
 }

if((SECONDSensor >= 10) & (SECONDSensor <= 50)) 
{
  digitalWrite(ALARM, HIGH);
  delay(500);
}
///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////
void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;
}

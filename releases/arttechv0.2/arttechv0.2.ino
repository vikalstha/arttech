#include <TMRpcm.h>
#include <SPI.h>
#include <SD.h>

char mychar;
const int CS_PIN = 10;
TMRpcm tmrpcm;
const int trigPin = 2;
const int echoPin = 4;

void setup() {
  tmrpcm.speakerPin = 9;
  Serial.begin(9600);
  Serial.println("Initializing Card");
  pinMode(CS_PIN, OUTPUT);
  if(!SD.begin(CS_PIN)) {
    Serial.println("Card Failure");
    return;
  }
  Serial.println("Card Ready");

}

void loop() {
   long duration, cm, check;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  if (cm>80 || cm <= 0 ){
    Serial.print("human moved");
    Serial.println("audio stoped");
    tmrpcm.stopPlayback();
  }
  else{
    Serial.print("human detected");
    Serial.println("audio playing");
    check=tmrpcm.isPlaying();
     if((check==0) && cm<80 ){
     tmrpcm.play("test.wav");
            
             tmrpcm.setVolume(1); //check the quality as volume increases, hit&trial the best possible output. value 1to7
             delay(1000);
             tmrpcm.setVolume(2);
             delay(1000);
             tmrpcm.setVolume(4);
             delay(1000);
             tmrpcm.setVolume(6);
             delay(1000);
             tmrpcm.setVolume(7);
             delay(1000);
            
            
     }
     else{
       tmrpcm.stopPlayback();
     }
  }
  delay(200);
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

//Library for the speaker to read the microsd 
#include "SD.h"
#define SD_ChipSelectPin 10 //Pin 10 is connected to the CS pin on the microsd reader
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

const int soundInputPin = A5;

int minValue = 290;
int maxValue = 240; //For the calculation later that'll make it easier to detect voice
int threshold = 5; //The threshold so that the mic does not pick up noise
int soundValue; //Global variable so we can log it in any function

void setup() {
  //SPEAKER CODE
  //This code only plays on startup, but can be 
  tmrpcm.speakerPin=9; //Pin connected to the + of the speaker
  Serial.begin(9600);
  if(!SD.begin(SD_ChipSelectPin)) //If pin is not connected, fail
  {
    Serial.println("SD fail");
    return;
  }

  //MICROPHONE CODE
  pinMode (soundInputPin, INPUT);

  //START FIRST SCENARIO
  scenarioOne();
}

void loop() {

}

void microphoneCode(){
  //MICROPHONE CODE
  bool hasTalked = false; //The timer will start once it has first detected a voice

  while(hasTalked == false){ //Wait until you've detected speech for the first time
  Serial.println("in the waiting loop");
    if(hasTalked == false){
      //VOICE DETECTION CODE
      soundValue = analogRead(soundInputPin); //OUT pin on the microphone

      analogWrite(A4, 200); //G pin on the microphone A.K.A the Gain
      delay(100);

      minValue = 290;
      maxValue = 240;
      for (int i = 0; i < 500; i++) {
        //Set maxValue and minValue to the current soundValue to be able to calculate if the volume is above a threshold
        if (soundValue > maxValue) maxValue = soundValue;
        if (soundValue < minValue) minValue = soundValue;
      }
      soundValue = maxValue - minValue; //This will make it so the soundValue is 0 unless it picks up sound
      if (soundValue >= threshold) { //Detect if the sound picked up is higher than 5
        Serial.println("Voice Detected");
        Serial.println(soundValue);
        delay(100);
        hasTalked = true;
      }
    }else{
      break; //Once it has detected speech for the first time, it goes on with the for loop
    }
  }

  for(int i = 0; i < 30; i++){ //This for loop is to make sure that the short breaks between the sound pickups are waited over so that it doesn't talk through you

    //VOICE DETECTION CODE
    soundValue = analogRead(soundInputPin); //OUT pin on the microphone

    analogWrite(A4, 200); //G pin on the microphone A.K.A the Gain
    delay(100);

    minValue = 290;
    maxValue = 240;
    for (int i = 0; i < 500; i++) {
      //Set maxValue and minValue to the current soundValue to be able to calculate if the volume is above a threshold
      if (soundValue > maxValue) maxValue = soundValue;
      if (soundValue < minValue) minValue = soundValue;
    }
    soundValue = maxValue - minValue; //This will make it so the soundValue is 0 unless it picks up sound
    if (soundValue >= threshold) { //Detect if the sound picked up is higher than 5
      Serial.println("Voice Detected");
      Serial.println(soundValue);
      delay(100);
      i = 0;
    }
    Serial.println(i);
  }
  hasTalked = false;
}

void scenarioFive(){
  //SPEAKER CODE
  tmrpcm.setVolume(5.5); //Audio volume, louder than this breaks it
  tmrpcm.play("eeee.wav"); //Plays the audio file
  delay(4000);
  Serial.println("Done talking");
  exit(0);
}

void scenarioFour(){
  //SPEAKER CODE
  tmrpcm.setVolume(5.5); //Audio volume, louder than this breaks it
  tmrpcm.play("dddd.wav"); //Plays the audio file
  delay(6500);
  Serial.println("Done talking");
  
  microphoneCode();
  scenarioFive();
}

void scenarioThree(){
  //SPEAKER CODE
  tmrpcm.setVolume(5.5); //Audio volume, louder than this breaks it
  tmrpcm.play("cccc.wav"); //Plays the audio file
  delay(7700);
  Serial.println("Done talking");
  
  microphoneCode();
  scenarioFour();
}

void scenarioTwo(){
  //SPEAKER CODE
  tmrpcm.setVolume(5.5); //Audio volume, louder than this breaks it
  tmrpcm.play("bbbb.wav"); //Plays the audio file
  delay(6000);
  Serial.println("Done talking");
  
  microphoneCode();
  scenarioThree();
}

void scenarioOne(){
  //SPEAKER CODE
  tmrpcm.setVolume(5.5); //Audio volume, louder than this breaks it
  tmrpcm.play("aaaa.wav"); //Plays the audio file
  delay(6500);
  Serial.println("Done talking");
  delay(500); //Wait half a second so that the waiting loop doesn't bug out the first time!!!
  
  microphoneCode();
  scenarioTwo();
}

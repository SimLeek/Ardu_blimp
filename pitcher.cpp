#include "pitches.h"

//include Arduino commands
#if ARDUINO <= 23
#include <WProgram.h>
#else
// for Arduino 1.0
#include <Arduino.h>
#include <inttypes.h>
#endif

int melody_tone_buff[64];
int melody_dur_buff[64];
int melody_buff_loc;
int melody_len;
tones mtone;
bool play_melody;

int mt1=0,mt2=0;

void start_melody(){
  melody_len=melody_buff_loc;
  melody_buff_loc=0;
  Serial.println(melody_dur_buff[melody_buff_loc]);
  if(!(melody_tone_buff[0]==0)){
    tone(10,melody_tone_buff[0],melody_dur_buff[0]/1000);
  }
  else{
    noTone(10);
  }
  play_melody=true;
  mt1=micros();
}

void melody_loop(){
  if(!play_melody){
    return;
  }
  mt2=micros();
  int ellapsed=mt2-mt1;
  mt1=mt2;
  melody_dur_buff[melody_buff_loc]-=ellapsed;
  Serial.println(melody_dur_buff[melody_buff_loc]);
  if(melody_dur_buff[melody_buff_loc]<=0){
    int overflow=melody_dur_buff[melody_buff_loc];
    melody_buff_loc+=1;
    if(melody_buff_loc>=melody_len){
      melody_buff_loc=0;
      noTone(10);
      play_melody=false;
      return;
    }
    melody_dur_buff[melody_buff_loc]+=overflow;
    if(!(melody_tone_buff[0]==0)){
      tone(10,melody_tone_buff[melody_buff_loc],melody_dur_buff[melody_buff_loc]/1000);
    }
    else{
      noTone(10);
    }
  }
  
}


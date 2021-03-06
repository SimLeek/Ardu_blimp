/* An optimized parser to handle streaming input.
 * 
 *
 * Copyright (c) MIT License 2014 SimLeek
 *
 *todo:optimize if statements
 */

#include "parser.h"
#include "movement.h"
#include "pitches.h"

//include Arduino commands
#if ARDUINO <= 23
#include <WProgram.h>
#else
// for Arduino 1.0
#include <Arduino.h>
#include <inttypes.h>
#endif



void Pstart();


namespace{
  char buff[32];
  int buffl=0;
  unsigned int set=0;unsigned int next=0;
  
  void (*rdp)()=Pstart;
}

void Pinvalid(){
  if(strcmp(buff,"!")==0){//valid exit point
    Serial.println("Ready.");
    rdp=Pstart;
  }
}

void Pgoto_point();

void Pset_coord(){
  float f=atof(buff);
  switch(next){
    case 1:
      dx=f;
      break;
    case 2:
      dy=f;
      break;
    case 4:
      dz=f;
      break;
    case 8:
      dw=f;
      break;
    default:
      Serial.println("What happened?");
      break;
  }
  rdp=Pgoto_point;
}

void Pgoto_point(){
  if(strcmp(buff,"x")==0 && (~set)&1){
    set=set|1;
    next=1;
    rdp=Pset_coord;
  }
  else if(strcmp(buff,"y")==0 && (~set)&2){
    set=set|2;
    next=2;
    rdp=Pset_coord;
  }
  else if(strcmp(buff,"z")==0 && (~set)&4){
    set=set|4;
    next=4;
    rdp=Pset_coord;
  }
  else if(strcmp(buff,"w")==0 && (~set)&8){
    set=set|8;
    next=8;
    rdp=Pset_coord;
  }
  else if(strcmp(buff,"!")==0){//valid exit point
    rdp=Pstart;
    set=0;
    start_path();
  }
  else{
    Serial.print("Error: invalid or redundant coordinate:\t");Serial.println(buff);
    Serial.println("Waiting for '!'.");
    set=0;
    rdp=Pinvalid;
  }
}

void Pupdate_orientation();

void Pset_orient(){
  float f=atof(buff);
  switch(next){
    case (1<<0):
      ax=f;
      break;
    case (1<<1):
      ay=f;
      break;
    case (1<<2):
      az=f;
      break;
    case (1<<3):
      ar=f;
      break;
    case (1<<4):
      ap=f;
      break;
    case (1<<5):
      aw=f;
      break;
    case (1<<6):
      vx=f;
      break;
    case (1<<7):
      vy=f;
      break;
    case (1<<8):
      vz=f;
      break;
    case (1<<9):
      vr=f;
      break;
    case (1<<10):
      vp=f;
      break;
    case (1<<11):
      vw=f;
      break;
    case (1<<12):
      x=f;
      break;
    case (1<<13):
      y=f;
      break;
    case (1<<14):
      z=f;
      break;
    case (1<<15):
      r=f;
      break;
    case (1<<16):
      p=f;
      break;
    case (1<<17):
      w=f;
      break;
    default:
      Serial.println("What happened?");
      break;
  }
  rdp=Pupdate_orientation;
}

void Pupdate_orientation(){

  
  int i=buff[0]<<8 + buff[1];
  
  switch(i){
   case ('a'<<8 + 'x'): 
     if((~set)&(1<<0)){
       set=set|(1<<0);
       next=(1<<0);
       rdp=Pset_orient;
     }else{goto default_label;}//yup, gotos. I could have used a function or something, but who cares.
     break;
   case ('a'<<8 + 'y'): 
     if((~set)&(1<<1)){
       set=set|(1<<1);
       next=(1<<1);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('a'<<8 + 'z'): 
     if((~set)&(1<<2)){
       set=set|(1<<2);
       next=(1<<2);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('a'<<8 + 'r'): 
     if((~set)&(1<<3)){
       set=set|(1<<3);
       next=(1<<3);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('a'<<8 + 'p'): 
     if((~set)&(1<<4)){
       set=set|(1<<4);
       next=(1<<4);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('a'<<8 + 'w'): 
     if((~set)&(1<<5)){
       set=set|(1<<5);
       next=(1<<5);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('v'<<8 + 'x'): 
     if((~set)&(1<<6)){
       set=set|(1<<6);
       next=(1<<6);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('v'<<8 + 'y'): 
     if((~set)&(1<<7)){
       set=set|(1<<7);
       next=(1<<7);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('v'<<8 + 'z'): 
     if((~set)&(1<<8)){
       set=set|(1<<8);
       next=(1<<8);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('v'<<8 + 'r'): 
     if((~set)&(1<<9)){
       set=set|(1<<9);
       next=(1<<9);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('v'<<8 + 'p'): 
     if((~set)&(1<<10)){
       set=set|(1<<10);
       next=(1<<10);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('v'<<8 + 'w'): 
     if((~set)&(1<<11)){
       set=set|(1<<11);
       next=(1<<11);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('x'<<8 + '\0'): 
     if((~set)&(1<<12)){
       set=set|(1<<12);
       next=(1<<12);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('y'<<8 + '\0'): 
     if((~set)&(1<<13)){
       set=set|(1<<13);
       next=(1<<13);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('z'<<8 + '\0'): 
     if((~set)&(1<<14)){
       set=set|(1<<14);
       next=(1<<14);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('r'<<8 + '\0'): 
     if((~set)&(1<<15)){
       set=set|(1<<15);
       next=(1<<15);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('p'<<8 + '\0'): 
     if((~set)&(1<<16)){
       set=set|(1<<16);
       next=(1<<16);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('w'<<8 + '\0'): 
     if((~set)&(1<<17)){
       set=set|(1<<17);
       next=(1<<17);
       rdp=Pset_orient;
     }else{goto default_label;}
     break;
   case ('!'<<8 + '\0'):
     rdp=Pstart;
     set=0;
     break;
   default:
    default_label:
    Serial.print("Error: invalid or redundant variable:\t");Serial.println(buff);
    Serial.println("Waiting for '!'.");
    set=0;
    rdp=Pinvalid;
    break;
  }

  
  Serial.println("uo");Serial.println(buff);
}

void Pqmark_orientation();

void Pqmark_orient(){
  float f=atof(buff);
  switch(next){
    case (1<<0):
      Serial.println(ax);//don't even read the full message. Idfc.
      break;
    case (1<<1):
      Serial.println(ay);
      break;
    case (1<<2):
      Serial.println(az);
      break;
    case (1<<3):
      Serial.println(ar);
      break;
    case (1<<4):
      Serial.println(ap);
      break;
    case (1<<5):
      Serial.println(aw);
      break;
    case (1<<6):
      Serial.println(vx);
      break;
    case (1<<7):
      Serial.println(vy);
      break;
    case (1<<8):
      Serial.println(vz);
      break;
    case (1<<9):
      Serial.println(vr);
      break;
    case (1<<10):
      Serial.println(vp);
      break;
    case (1<<11):
      Serial.println(vw);
      break;
    case (1<<12):
      Serial.println(x);
      break;
    case (1<<13):
      Serial.println(y);
      break;
    case (1<<14):
      Serial.println(z);
      break;
    case (1<<15):
      Serial.println(r);
      break;
    case (1<<16):
      Serial.println(p);
      break;
    case (1<<17):
      Serial.println(w);
      break;
    default:
      Serial.println("What happened?");
      break;
  }
  rdp=Pqmark_orientation;
}

void Pqmark_orientation(){
  //todo: for a slight speedup, combine the two chars into a 16 bit int.
  if(strcmp(buff,"ax")==0 && (~set)&(1<<0)){
    set=set|(1<<0);
    next=(1<<0);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"ay")==0 && (~set)&(1<<1)){
    set=set|(1<<1);
    next=(1<<1);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"az")==0 && (~set)&(1<<2)){
    set=set|(1<<2);
    next=(1<<2);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"ar")==0 && (~set)&(1<<3)){
    set=set|(1<<3);
    next=(1<<3);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"ap")==0 && (~set)&(1<<4)){
    set=set|(1<<4);
    next=(1<<4);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"aw")==0 && (~set)&(1<<5)){
    set=set|(1<<5);
    next=(1<<5);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"vx")==0 && (~set)&(1<<6)){
    set=set|(1<<6);
    next=(1<<6);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"vy")==0 && (~set)&(1<<7)){
    set=set|(1<<7);
    next=(1<<7);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"vz")==0 && (~set)&(1<<8)){
    set=set|(1<<8);
    next=(1<<8);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"vr")==0 && (~set)&(1<<9)){
    set=set|(1<<9);
    next=(1<<9);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"vp")==0 && (~set)&(1<<10)){
    set=set|(1<<10);
    next=(1<<10);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"vw")==0 && (~set)&(1<<11)){
    set=set|(1<<11);
    next=(1<<11);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"x")==0 && (~set)&(1<<12)){
    set=set|(1<<12);
    next=(1<<12);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"y")==0 && (~set)&(1<<13)){
    set=set|(1<<13);
    next=(1<<13);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"z")==0 && (~set)&(1<<14)){
    set=set|(1<<14);
    next=(1<<14);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"r")==0 && (~set)&(1<<15)){
    set=set|(1<<15);
    next=(1<<15);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"p")==0 && (~set)&(1<<16)){
    set=set|(1<<16);
    next=(1<<16);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"w")==0 && (~set)&(1<<17)){
    set=set|(1<<17);
    next=(1<<17);
    rdp=Pqmark_orient;
  }
  else if(strcmp(buff,"!")==0){//valid exit point
    rdp=Pstart;
    set=0;
  }
  else{
    Serial.print("Error: invalid or redundant variable:\t");Serial.println(buff);
    Serial.println("Waiting for '!'.");
    set=0;
    rdp=Pinvalid;
  }
}

void Pplay_tone();

void Ptone_dur(){
  float f=atof(buff);
  melody_dur_buff[melody_buff_loc]=1000000.0/f;
  melody_buff_loc+=1;
  if(melody_buff_loc>64){
    Serial.println("Error: melody too long");
    Serial.println("Waiting for '!'");
    rdp=Pinvalid;
  }
  else{
    rdp=Pplay_tone;
  }
}

void Ptone_duration(){
  if(strcmp(buff,"l")==0){
    rdp=Ptone_dur;
  }
  else{
    Serial.print("Error: invalid syntax. Expected '_' preceeding duration, got '");
    Serial.println(buff);
    Serial.println("Waiting for'!'");
    rdp=Pinvalid;
  }
}

void Ptone_scale(){
  
  float f=atof(buff);
  int i=f;
  switch(mtone){
    case A:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_A1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_A2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_A3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_A4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_A5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_A6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_A7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case B:
      switch(i){
        case 0:
          melody_tone_buff[melody_buff_loc]=NOTE_B0;
          break;
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_B1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_B2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_B3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_B4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_B5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_B6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_B7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case C:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_C1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_C2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_C3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_C4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_C5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_C6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_C7;
          break;
        case 8:
          melody_tone_buff[melody_buff_loc]=NOTE_C8;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case D:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_D1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_D2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_D3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_D4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_D5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_D6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_D7;
          break;
        case 8:
          melody_tone_buff[melody_buff_loc]=NOTE_D8;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case E:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_E1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_E2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_E3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_E4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_E5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_E6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_E7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case F:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_F1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_F2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_F3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_F4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_F5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_F6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_F7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case G:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_G1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_G2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_G3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_G4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_G5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_G6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_G7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case AS:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_AS1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_AS2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_AS3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_AS4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_AS5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_AS6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_AS7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case CS:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_CS1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_CS2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_CS3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_CS4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_CS5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_CS6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_CS7;
          break;
        case 8:
          melody_tone_buff[melody_buff_loc]=NOTE_CS8;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case DS:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_DS1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_DS2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_DS3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_DS4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_DS5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_DS6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_DS7;
          break;
        case 8:
          melody_tone_buff[melody_buff_loc]=NOTE_DS8;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case FS:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_FS1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_FS2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_FS3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_FS4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_FS5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_FS6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_FS7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case GS:
      switch(i){
        case 1:
          melody_tone_buff[melody_buff_loc]=NOTE_GS1;
          break;
        case 2:
          melody_tone_buff[melody_buff_loc]=NOTE_GS2;
          break;
        case 3:
          melody_tone_buff[melody_buff_loc]=NOTE_GS3;
          break;
        case 4:
          melody_tone_buff[melody_buff_loc]=NOTE_GS4;
          break;
        case 5:
          melody_tone_buff[melody_buff_loc]=NOTE_GS5;
          break;
        case 6:
          melody_tone_buff[melody_buff_loc]=NOTE_GS6;
          break;
        case 7:
          melody_tone_buff[melody_buff_loc]=NOTE_GS7;
          break;
        default:
          //error: invalid tone
          rdp=Pinvalid;
          break;
      }
      break;
    case SIL:
      melody_tone_buff[melody_buff_loc]=0;
      break;
  }
  if(rdp!=Pinvalid){
    rdp=Ptone_duration;
  }
  else{
    Serial.print("Error: invalid scale:\t");Serial.println(i);
    Serial.println("Waiting for '!'.");
  }
}

void Pplay_tone(){
  //todo: for a slight speedup, combine the two chars into a 16 bit int.
  
  if(strcmp(buff,"a")==0){
    mtone=A;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"as")==0){
    mtone=AS;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"b")==0){
    mtone=B;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"c")==0){
    mtone=C;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"cs")==0){
    mtone=CS;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"d")==0){
    mtone=D;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"ds")==0){
    mtone=DS;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"e")==0){
    mtone=E;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"f")==0){
    mtone=F;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"fs")==0){
    mtone=FS;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"g")==0){
    mtone=G;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"gs")==0){
    mtone=GS;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"s")==0){
    mtone=SIL;
    rdp=Ptone_scale;
  }
  else if(strcmp(buff,"!")==0){//valid exit point
    rdp=Pstart;
    start_melody();
  }
  else{
    Serial.print("Error: invalid tone:\t");Serial.println(buff);
    Serial.println("Waiting for '!'.");
    set=0;
    rdp=Pinvalid;
  }
}

/*Pstart- the entrance to the parser (S->'/'C'!')
 *
 *it also works ahead to determine which command is being parsed.
 *(C->'g''p'W1),(C->'u''o'AX...PW),(C->'?''o'AX?...PW?),(C->'?''p'W1?)
 *
 */
void Pstart(){
  if(strcmp(buff,"/gp")==0){
    rdp=Pgoto_point;
  }
  else if(strcmp(buff,"/uo")==0){
    rdp=Pupdate_orientation;
  }
  else if(strcmp(buff,"/?o")==0){
    rdp=Pqmark_orientation;
  }
  else if(strcmp(buff,"/pt")==0){
    melody_buff_loc=0;
    rdp=Pplay_tone; 
  }
  /*else if(strcmp(buff,"/?p")==0){
    
  }*/
  else{
    Serial.print("Error: invalid command:\t");Serial.println(buff);
  }
}

/*parse - the parsing engine
 *
 *memory: stores the pointer to the next step in a single void*.
 */

void parse(){
  buff[buffl]='\0';
  rdp();//
}


/* lex - a character by character lexer
 *
 * in: c - the next character to lex and turn into a token
 *
 * memory: stores tokens in a buffer of length 30
*/
void lex(char& c){
  //start
  if(buffl==0){
    if(c=='/'){
      buff[0]='/';
      buffl=1;
    }
    else if(c>=48 && c<=57 || c==46){//number or period (doesn't check for valid numbers, but atoi will, so I don't care)
      buff[0]=c;
      buffl=1;
    }
    else if(c>=97 && c<=122){//lower case alphabetical
      buff[0]=c;
      buffl=1;
    }
    else if(c=='!'){
      buff[0]=c;
      buffl=1;
      parse();
      buffl=0;
    }
    else{
      Serial.print("Error: invalid token:\t");Serial.println(c);
    }
  }
  //end
  else if(buff[0]=='/'){
    buff[buffl]=c;
    buffl++;
    if(buffl==3){
      parse();
      buffl=0;
    }
  }
  else if(buff[0]>=48 && buff[0]<=57 || buff[0]==46){
    if(c>=48 && c<=57 || c==46){
      buff[buffl]=c;
      buffl++;
    }
    else if(c>=97 && c<=122){
      parse();
      buff[0]=c;
      buffl=1;
    }
    else if(c=='!'){
      parse();
      buff[0]=c;
      buffl=1;
      parse();
      buffl=0;
    }
    else{
      parse();
      buffl=0;
      lex(c);
    }
  }
  else if(buff[0]>=97 && buff[0]<=122){
    if(c>=97 && c<=122){
      buff[buffl]=c;
      buffl++;
    }
    else if(c>=48 && c<=57 || c==46){
      parse();
      buff[0]=c;
      buffl=1;
    }
    else if(c=='!'){
      parse();
      buff[0]=c;
      buffl=1;
      parse();
      buffl=0;
    }
    else{
      parse();
      buffl=0;
      lex(c);
    }
  }
  
  if(buffl>=30){
    buff[buffl]='\0';
    Serial.print("Error: token is larger than 30 characters:\t");Serial.println(buff);
    buffl=0;
  }
}

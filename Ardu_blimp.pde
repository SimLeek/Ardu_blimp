//blimp v0.10
#include "movement.h"
#include "parser.h"
#include "pitches.h"

void setup(){
  setup_movement();
  
  Serial.begin(9600);//the arduino can handle more than 1 Mbit/s, but the software libraries can't deal with more than 500000 kb/s. 
  //(It can actually support 2Mbit/s, but I don't want to chance briking my Arduino by setting the wrong bit. Also, I want to be a bit under an actual Mbit.)
  //(but seriously, if your computer can't run this, you need a new computer.)
  //http://arduino.stackexchange.com/questions/296/how-high-of-a-baud-rate-can-i-go-without-errors
  //http://forum.arduino.cc/index.php?topic=21497.0
  //todo: set priorities for multiple ports if data rate is shared.
  //NOTE: If you experience character skipping or loss on the receive side, build a queue and have the arduino signal when it's ready for more data after it receives a whole packet to calculate
}

void loop(){
  
  char inByte;
  while(Serial.available()){
     inByte=Serial.read();
     lex(inByte);
  }
  movement_loop();
  melody_loop();
}

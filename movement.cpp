#include "movement.h"

//include Arduino commands
#if ARDUINO <= 23
#include <WProgram.h>
#else
// for Arduino 1.0
#include <Arduino.h>
#include <inttypes.h>
#endif


float dx=0,dy=0,dz=0,dw=0;//dr=0,dp=0,dw=0;//desired, or change in x y and z, and roll pitch and yaw.
float ax=0,ay=0,az=0,ar=0,ap=0,aw=0,vx=0,vy=0,vz=0,vr=0,vp=0,vw=0,x=0,y=0,z=0,r=0,p=0,w=0;//r=0,p=0,w=0;


namespace pin{
//DIR=direction
const int PWMfrprop = 9;//front right
const int DIRfrprop = 8;
const int PWMflprop = 10;//front left
const int DIRflprop = 11;
const int PWMbrprop = 3;//back right
const int DIRbrprop = 4;
const int PWMblprop = 6;//back left
const int DIRblprop = 7;

//SENS=sensor. 1 means before motor, 2 means after. It senses current used by the propeller.
const int SENS1frprop =A0;
const int SENS2frprop =A1;
const int SENS1flprop =A2;
const int SENS2flprop =A3;
const int SENS1brprop =A4;
const int SENS2brprop =A5;
const int SENS1blprop =A6;
const int SENS2blprop =A7;
}

#define Clockwise HIGH  
#define CounterClockwise LOW

void setup_movement(){
  pinMode(pin::PWMfrprop, OUTPUT);
  pinMode(pin::DIRfrprop, OUTPUT);
  pinMode(pin::PWMflprop, OUTPUT);
  pinMode(pin::DIRflprop, OUTPUT);
  pinMode(pin::PWMbrprop, OUTPUT);
  pinMode(pin::DIRbrprop, OUTPUT);
  pinMode(pin::PWMblprop, OUTPUT);
  pinMode(pin::DIRblprop, OUTPUT);
}






inline void printcoords(){
 Serial.print(dx);Serial.print(",\t");Serial.print(dy);Serial.print(",\t");Serial.print(dz);Serial.print(",\t");
 /*Serial.print(dr);Serial.print(",\t");Serial.print(dp);Serial.print(",\t");Serial.print(dw);Serial.print(",\t");*/
}

void goto_point(){
  Serial.println("Function Reached!");
  Serial.print(dx);Serial.print(",\t");Serial.print(dy);Serial.print(",\t");Serial.print(dz);Serial.print(",\t");Serial.print(dw);
}




int t=0;
int t1,t2;

boolean moving=false;
void end_path(){
  dy=0;
  t=0;
  moving=false;
}
float d;
float s;
float m;
float ux,uy,uz;//unit vector


void start_path(){
  t2=micros();t1=t2;
  
  d=sqrt((dy-y)*(dy-y)+(dx-x)*(dx-x)+(dz-z)*(dz-z));
  s=d*1000000;//this is the time to finish to movement. I'll make it proportional to the length of the movement
  m=300*d;//multiplier. saves multiplications
  ux=dx/d;uy=dy/d;uz=dz/d;
  moving=true;
}

void follow_path(){
  
  t2=micros();
  
  //I'll be using minimum jerk trajectories
  //first, I'll just be using them for two points
  //and I'll be using acceleration, since it costs less multiplication
  //I'll just have the PID loop go for acceleration, which should make things much easier.
  //http://www.shadmehrlab.org/book/minimum_jerk/minimumjerk.htm
  //Afterwards, I'll have to calculate the general least jerk path along cubic bezier curves,
  //and for different starting and ending accelerations, so I can link multiple bezier curvese together
  //http://blog.avangardo.com/2010/10/acceleration-on-curve-path/
  //at that point though, I'm pretty much done.
   
   float p=(float)t/(float)s;//percentage done. Saves us 3 divisions
   
   float acc=m*(p-1)*p*(2*p-1);//this is the desired acceleration in the y direction
   
   if (acc>255) acc=255;//hardware limits
   else if (acc<-255) acc=-255;
   
   Serial.print(acc*ux);Serial.print(',');Serial.print(acc*uy);Serial.print(',');Serial.print(acc*uz);Serial.print(',');Serial.println(p);
     
   t+=t2-t1;//overshooting by one
   
   if(t >=s){
    end_path(); 
   }
   t1=t2;
}

void movement_loop(){
  if(moving){
    follow_path(); 
  }
}

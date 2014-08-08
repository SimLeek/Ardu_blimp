//blimp v0.10

#include <stdlib.h>

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

/* coords:
 *
 *      z,w
 *   y,r |
 *     \ |
 *      \|_ _ _ x,p
 */
float dx=0,dy=0,dz=0,dw=0;//dr=0,dp=0,dw=0;//desired, or change in x y and z, and roll pitch and yaw.
float x=0,y=0,z=0,w=0;//r=0,p=0,w=0;

inline void printcoords(){
 Serial.print(dx);Serial.print(",\t");Serial.print(dy);Serial.print(",\t");Serial.print(dz);Serial.print(",\t");
 /*Serial.print(dr);Serial.print(",\t");Serial.print(dp);Serial.print(",\t");Serial.print(dw);Serial.print(",\t");*/
}


void goto_point(){
  Serial.println("Function Reached!");
  Serial.print(dx);Serial.print(",\t");Serial.print(dy);Serial.print(",\t");Serial.print(dz);Serial.print(",\t");Serial.print(dw);
}

char buff[32];
int buffl=0;
unsigned int set=0;unsigned int next=0;

void Pstart();
void (*rdp)()=Pstart;

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
    goto_point();
  }
  else{
    Serial.print("Error: invalid or redundant coordinate:\t");Serial.println(buff);
    Serial.println("Waiting for '!'.");
    set=0;
    rdp=Pinvalid;
  }
}

void Pstart(){
  if(strcmp(buff,"/gp")==0){
    rdp=Pgoto_point;
  }
  /*else if(strcmp(buff,"/uo")==0){
    
  }
  else if(strcmp(buff,"/?o")==0){
    
  }
  else if(strcmp(buff,"/?p")==0){
    
  }*/
  else{
    Serial.print("Error: invalid command:\t");Serial.println(buff);
  }
}

void parse(){
  buff[buffl]='\0';
  rdp();
}

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

void setup(){
  pinMode(pin::PWMfrprop, OUTPUT);
  pinMode(pin::DIRfrprop, OUTPUT);
  pinMode(pin::PWMflprop, OUTPUT);
  pinMode(pin::DIRflprop, OUTPUT);
  pinMode(pin::PWMbrprop, OUTPUT);
  pinMode(pin::DIRbrprop, OUTPUT);
  pinMode(pin::PWMblprop, OUTPUT);
  pinMode(pin::DIRblprop, OUTPUT);
  Serial.begin(9600);
}

int t=0;
int t1,t2;
void end_path(){
  dy=0;
  t=0;
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
   
   Serial.print(acc);Serial.print(',');Serial.println(p);
     
   t+=t2-t1;//overshooting by one
   
   if(t >=s){
    end_path(); 
   }
   t1=t2;
}





void parse_stream(){
  
}

void loop(){
  
  char inByte;
  while(Serial.available()){
     inByte=Serial.read();
     lex(inByte);
  }
  /*if(dy!=0)
    follow_path();*/
}

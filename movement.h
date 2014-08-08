#ifndef _MOVEMENT_H__
#define _MOVEMENT_H__

/* coords:
 *
 *      z,w
 *   y,r |
 *     \ |
 *      \|_ _ _ x,p
 */
extern float dx,dy,dz,dw;//dr=0,dp=0,dw=0;//desired, or change in x y and z, and roll pitch and yaw.
extern float ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vp,vw,x,y,z,r,p,w;//orientation and position

void setup_movement();
void movement_loop();

void start_path();


#endif

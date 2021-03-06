#Blimp v0.11

This is a testing platform for various robotics using Arduino, complete with a parser for the input code

##Physics

###Blimp type

The desired radius and skin density for any carrying mass can be calculated with:

    (1.29-.178)*9.8*(4/3)*pi*r^3 - s*4*pi*r^2 - m = 0

where r is the radius of the spherical balloon (in meters), s is the skin density (in kilograms/meters^2, .288 for latex balloon), and m is the mass to be carried (in kilograms).

###Jellyfish type

For smaller drag based low power arial sensor networks that use flaps that close on free-fall, the mass for a specific terminal velocity can be calculated with:

    .5*1.29*v*A*Cd / 9.8 = m
    
where A is the area when falling, v is the desired terminal velocity, Cd is the drag coefficient(.42 for hemisphere shape), and m is the mass.

The upwards drag can be calculates with:

    .5*1.29*v*A*Cd = Fm + m*9.8
    
where A is the area when rising, v is the desired maximum velocity, Cd is the drag coefficient, Fm is the available force from the motors, and m is the mass of the device.

Energy usage compared to standard quad-copters for hovering in midair can be calculates as:

    (1-Vu/(Vu+Vd))*(Fdj/Fdn)=E
    
where E is the energy used as a percentage of the original, Vu is the velocity going up, Vd is the velocity going down, Fdj is the drag of the jellyfish model (with velocity excluded) when moving up, and Fdn is the drag of a normal quadcopter (with velocity excluded). This deos not account for extra losses for flap opening/closing times, so to remove that extra energy loss, use large vertical areas when in low power 'hovering'.

(Note: there are no energy savings for constant traveling with any of these designs. For those, use a regular quad-copter or plane.)

A pure parachute based model would use around 23.9% of the energy of a normal quad-copter:
    
    (1-8/(8+2))*(1.2/1)=0.2399
    
At 1 cm^2, this has a much better energy usage around 1.96%


##Current Availablt Input

command format \<regex\>: /(.{2})([a-z]+[0-9\\.]+)*!

| Command | Name | Variables | Description |
|---------|------|-----------|-------------|
|/gp |Go to Point | x,y,z,w   |Sets the next coordinates to go to, with the current position as the origin.|
|/uo |Update Orientation | ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vz,vw,x,y,z,r,p,w | Updates the orientation of the robot (x,y,z are with respect to the previous origin when traveling, otherwise 0) (todo: add percentage error so you can combine orientation values from camera and imu)|
|/?o |get Orientation | ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vz,vw,x,y,z,r,p,w | Prints the Arduino orientation info to the computer. (todo: report values with errors, for same reason as /uo)
|/pt |Play Tone | a,b,c,d,e,f,g,as,cs,ds,fs,gs |plays a melody. Format is (a-g)(s)?(0-8)l(inverse of length compared to sec)+. Currecntly, the max length is 64, but that can be changed if it's important.

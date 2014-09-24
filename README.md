#Blimp v0.11

This is a testing platform for various robotics using Arduino, complete with a parser for the input code

##Physics

###Blimp type

The desired radius and skin density for any carrying mass can be calculated with:

    (1.29-.178)*9.8*(4/3)*pi*r^3 - s*4*pi*r^2 - m = 0

where r is the radius of the spherical balloon (in meters), s is the skin density (in kilograms/meters^2), and m is the mass to be carried (in kilograms).

###Jellyfish type

For drag based low power arial sensor networks, the mass for a specific terminal velocity can be calculated with:

    .5*1.29*v*A*Cd / 9.8 = m
    
where A is the area when falling, v is the desired terminal velocity, Cd is the drag coefficient(.42 for hemisphere shape), and m is the mass.

##Current Availablt Input

command format \<regex\>: /(.{2})([a-z]+[0-9\\.]+)*!

| Command | Name | Variables | Description |
|---------|------|-----------|-------------|
|/gp |Go to Point | x,y,z,w   |Sets the next coordinates to go to, with the current position as the origin.|
|/uo |Update Orientation | ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vz,vw,x,y,z,r,p,w | Updates the orientation of the robot (x,y,z are with respect to the previous origin when traveling, otherwise 0) (todo: add percentage error so you can combine orientation values from camera and imu)|
|/?o |get Orientation | ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vz,vw,x,y,z,r,p,w | Prints the Arduino orientation info to the computer. (todo: report values with errors, for same reason as /uo)
|/pt |Play Tone | a,b,c,d,e,f,g,as,cs,ds,fs,gs |plays a melody. Format is (a-g)(s)?(0-8)l(inverse of length compared to sec)+. Currecntly, the max length is 64, but that can be changed if it's important.

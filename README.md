#Blimp v0.10

This is a testing platform for various robotics using Arduino, complete with a parser for the input code


##Availablt Input

command format \<regex\>: /(.{2})([a-z]+[0-9\\.]+)*!

| Command | Name | Variables | Description |
|---------|------|-----------|-------------|
|/gp |Go to Point | x,y,z,w   |Sets the next coordinates to go to, with the current position as the origin.|
|/uo |Update Orientation | ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vz,vw,x,y,z,r,p,w | Updates the orientation of the robot (x,y,z are with respect to the previous origin when traveling, otherwise 0) (todo: add percentage error so you can combine orientation values from camera and imu)|
|/?o |get Orientation | ax,ay,az,ar,ap,aw,vx,vy,vz,vr,vz,vw,x,y,z,r,p,w | Prints the Arduino orientation info to the computer. (todo: report values with errors, for same reason as /uo)

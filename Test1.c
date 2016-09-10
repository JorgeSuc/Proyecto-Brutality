#include "simpletools.h"                      // Include simpletools header
#include "ping.h"                             // Include ping header
#include "abdrive.h"

int sensor1;                                 
int sensor2;

int main()                   
{
  while(1)                                    // Repeat indefinitely
  {
    sensor1 = ping_cm(8);                    //Carga los sensores al inicio y por ciclo.
    sensor2 = ping_cm(4);                    //Carga los sensores al inicio y por ciclo.
    
    if(sensor2<20){                         
      if(sensor1<15){
        drive_speed(0, 0);
        drive_goto(-25, 26);
        pause(100);
      }
      else{
        drive_speed(40, 40);
        pause(100);
      }                
    }
    
    else{
      drive_speed(0, 0);
      drive_goto(35, 35);
      pause(100);
      drive_goto(26, -25);
      pause(100);
      drive_goto(40,40);
      pause(100);
    }                      
  } 
}  


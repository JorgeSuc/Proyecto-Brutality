#include "simpletools.h"                      // Include simpletools header
#include "ping.h"                             // Include ping header
#include "abdrive.h"

int sensor1;                                    //Definimos sensor 1
int sensor2;                                    //Definimos sensor 2

int main()                   
{
  while(1)                                    // Repeat indefinitely
  {
    sensor1 = ping_cm(8);                    //Carga los sensores al inicio y por ciclo. los configuramos a los pines de la placa
    sensor2 = ping_cm(4);                    //Carga los sensores al inicio y por ciclo. los configuramos a los pines de la placa
    
    if(sensor2<20){                         //paso 1: verifica si el sensor del lado derecho tiene una pared, osea si la distancia hacia un objeto es menor a 20 cm
      if(sensor1<15){                       //si el paso 1 se cumple, paso2: verifica si el sensor de en frente tiene una pared
        drive_speed(0, 0);                  //si el paso anterior se cumple, deja de acelerar
        drive_goto(-25, 26);                //gira sobre su eje a 90° hacia la izquierda
        pause(100);                         //y hacemos que espere 
      }
      else{                                 //Si el sensor de frente de el paso2 no detecta pared,
        drive_speed(40, 40);                // el robot acelera 
        pause(100);                         //hacemos otra pausa
      }                
    }
    
    else{                                     //Si en el paso 1 no detecto pared
      drive_speed(0, 0);
      drive_goto(35, 35);                     //acelera un poco hacia en frente, debido a que tiene que salir la distancia de el mismo para no topar en las paredes
      pause(100);                             //Hacemos pausa
      drive_goto(26, -25);                    //Hacemos que gire sobre su eje a 90° hacia la derecha
      pause(100);                             //Hacemos pausa
      drive_goto(40,40);                      //Hacemos que avance un poco hacia enfrente, para volver a entrar a donde se supone que debe existir una pared
      pause(100);                             //Haecmos pausa
    }                                         //Se repite el ciclo de forma infinita
  } 
}  


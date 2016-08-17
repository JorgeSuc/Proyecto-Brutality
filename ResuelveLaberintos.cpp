/* Universidad del Valle de Guatemala 
   Algoritmos y Estructuras de Datos
   Proyecto 1 
   Jorge Suchite 15293
   Luis Abadilla
   Maria Fernanda Cornejo
   Este programa soluciona laberintos con respecto al
   algoritmo de la mano derecha.
   
   

Bueno, la cosa es asi. Se tiene un archivo .txt dond esta guardado un laberinto 
donde estan los numeros 3,1,2 y el 0 

Donde 3 es donde esta posicionada la salida del laberinto; 1 representa una pared, en otras palabras. Donde el roboton no puede pasar.
0 es o simbolliza los espacios a seguir, donde el roboton puede caminar y/o desplazarse y 2 que es el ultimo pero no el menos
importante es el que representa a nuestro roboton en el laberinto 

Es algo sencillo

*/

//estas ondas son librerias //

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>

//declarando variables robotonicas//
void leerArchivo();
int infoC(int);
int metaCerca();
void MuestraLaberinto();
int evitaParedesDer(int);
int evitaParedesIzq(int);
void borraRastro(int,int,int);
void mueveJugador(int);
void dimensionaMatriz();




int **m; // Matriz  que me ayudara a modelar el disque laberinto ha de ser en este caso de 100 por 100 probando va          
                 
int m2[100][100];                         
int f,c;                                 // filas y columnas del laberinto            
int fp,cp;                                  // cardinalidad  de roboton 
int fs,cs;                                // posicion de la salida
int ifp,icp;                              // donde inicia roboton
const int ARRIBA=0, DERECHA=1, IZQUIERDA=2, ABAJO=3;
int direccion=ARRIBA;                                    // 
int movs;                                     //  CONTADOR QUE ME DICE CUANTAS VECES SE MOVIO EL ROBOTON
int espacios; 
bool ya=false;                                      // tal vez ya pasamos  por aqui y esto emva a decir si si o si no

void dimensionaMatriz(char ruta[]) {
     bool flag=true; 
    FILE *archivo;
    char caracter;
    int codigo;
    
    //########################################### Progra defensiva antimisiles rusos###############################################################// 
    
    archivo=fopen(ruta,"rt");                       //  CON ESTO se abre el archivaldo en modo de .txt va vos pero solo tenemos la ruta nada mas, mas abajo nos dice como abrirlo
    if (archivo==NULL) {                            // si el usuario quierehacer trampita y me dice que si hay un archivo pero no, tiramos el error defensivo
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE);   // si es verdad que no  hay nada que abri, entonce no salimo del programa
       
       
       
       
       //################################################### modulando el laberintotototo ##########################################################//
    }
    f=1;c=1;
    while(!feof(archivo)) { // Dimensionamos nuestra matriz donde f es fila y c es columna
            caracter=fgetc(archivo);
            codigo = caracter;                    //necesitamos el codigo ASCII para poder transformar el caracter 
            
            if (codigo==10) {                                   
               f++; 
               if (flag) flag=false;    // flag es para ver si seguimos agregando columnas o filas chavo
            } else if (flag) c++;              
    }
    fclose(archivo); 
    
    // Dimensionamos m[][]  osea que la volvemos en 2d la onda
    m = (int **)malloc (f*sizeof(int *));        
    for (int j=0;j<f;j++) 
    m[j] = (int *) malloc (c*sizeof(int));      
}

void leerArchivo(char ruta[]) {
    int ff,cc,codigo;
    FILE *archivo;
    char caracter;      
    
    archivo=fopen(ruta,"rt");                         // abrimos el archivo "laberinto.txt" en modo lectura de texto pero ahora para poder leerlo, ya podemos //
                                                     // dimensionarlo y ya lo ruteamos, pero ahora debdemos de leerlo  porque es un secreto//
    if (archivo==NULL) {                             // por si acaso el usuario metio mal el nombre o algo parecido //
       printf("Error en lectura de archivo\n");
       system("pause");
       exit (EXIT_FAILURE);                           // aplicamos push y pop para salir jaja
    }
    
    for (int i=0;i<f-1;i++){
       for (int ii=0;ii<c;ii++) {
           caracter=fgetc(archivo);
           codigo = caracter;                                            
           if (codigo!=10) {
               m[i][ii]=codigo-48;                 // ASCII lo volvemos entero//
               if (m[i][ii]==2){ifp=i;icp=ii;}
               if (m[i][ii]==3){fs=i;cs=ii;}
               if (m[i][ii]==0) espacios++;                    // con esta vaina contamos los espacios que tenemos para poder mover el bote//
           }
               
       }
    }        
    fclose(archivo);        //cerramos el archivito //
}

int infoC(int dir) {                                // nos da information de como va el roboton en el laberinto asi como la posiciion de la casilla actual,//
                                                    // y de que ha de hacer en la situacion dada//
    switch (dir) {
       case ARRIBA: return m[fp-1][cp];break;
       case ABAJO: return m[fp+1][cp]; break;
       case IZQUIERDA: return m[fp][cp-1]; break;
       case DERECHA: return m[fp][cp+1];break;
    }
}

int infoC(int dir,int dist) {                             // me informa al roboton de que casilla va despues o la que esta distante la cual ha de psar
    switch (dir) {
       case ARRIBA: return m[fp-dist][cp];break;
       case ABAJO: return m[fp+dist][cp]; break;
       case IZQUIERDA: return m[fp][cp-dist]; break;
       case DERECHA: return m[fp][cp+dist];break;
    }
}

int metaCerca() {                                             // miramos si la salida esta cerca para que asi no se vaya a ver que hongos del laberinto
                                                              //  no explorado y nos vamos de una a la salida 
    
       int lejos=1,aux=0,dir=-1;
       
       while (aux!=1 && aux!=3) {
           aux=infoC(ABAJO,lejos);
           if (aux==3) dir=ABAJO;
           lejos++;
       } lejos=1;aux=0;
       if (dir==-1) {
           while (aux!=1 && aux!=3) {
               aux=infoC(DERECHA,lejos);
               if (aux==3) dir=DERECHA;
               lejos++;
           } lejos=1;aux=0;
       }
       if (dir==-1) {
       while (aux!=1 && aux!=3) {
           aux=infoC(ARRIBA,lejos);
           if (aux==3) dir=ARRIBA;
           lejos++;
       } lejos=1;aux=0;
       }
       if (dir==-1) {
          while (aux!=1 && aux!=3) {
               aux=infoC(IZQUIERDA,lejos);
               if (aux==3) {dir=IZQUIERDA;}
               lejos++;
           } lejos=1;
       }
      return dir;  
}

void MuestraLaberinto() {
                                               // Esta funcio hace que las paredes se impriman como paredes (caracter ascii 219),// 
                                               // y la salida es representada como S  y a roboton como R//
    system("cls");
    for (int i=0;i<f;i++) {
        for (int ii=0;ii<c;ii++) {
           if (m[i][ii]==1) printf ("%c",char(219));       // las paredes //
           else if (i==fs && ii==cs) printf ("S");
           else if (i==fp && ii==cp) printf ("R");
           else if (m[i][ii]==4) printf (".");                  // aqui se imprime el puntito para referirnos a que roboton ya paso por aca//
           else printf (" ");
        }
    printf ("\n");
    }
    
    //############################################# METODO DE LA MANO DERECHA #####################################################################//
    
    // miramos en que direccion esta y luego utilizamos el metodo de la mo derecha //
}
int evitaParedesDer(int dir) {
    switch (dir) {
    case ARRIBA: 
        if (infoC(DERECHA)==1 && infoC(ARRIBA)!=1) {}                          // primero que nada miramos si existe una pared a la derecha // 
        else if (infoC(DERECHA)!=1) dir=DERECHA;                                 // si no hay pared a la derecha giramos viendo a la derecha         
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;                             // si no haypared izquierda entonces volveamos para la izq.
        else dir=ABAJO;                                                      // si hay dos paredes a los lados y enfrente lo obligamos a ir para abajo           
    break;    
    case DERECHA:
        if (infoC(ABAJO)==1 && infoC(DERECHA)!=1) {}      
        else if (infoC(ABAJO)!=1) dir=ABAJO;
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;
        else dir=IZQUIERDA;    
    break;                
    case ABAJO:
        if (infoC(IZQUIERDA)==1 && infoC(ABAJO)!=1) {}      
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;
        else if (infoC(DERECHA)!=1) dir=DERECHA;
        else dir=ARRIBA;
    break;
     case IZQUIERDA:
        if (infoC(ARRIBA)==1 && infoC(IZQUIERDA)!=1) {}             
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;
        else if (infoC(ABAJO)!=1) dir=ABAJO; 
        else dir=DERECHA;
    break;
    }
    return dir;           
}

int evitaParedesIzq(int dir) {                   //  por si acaso no sirve el de la mano derecha, cambiamos direccion y la volvemos metodo de la mano izquierda
                                                 // con la misma metodología pero ahora al reves 
    switch (dir) {
    case ARRIBA: 
         if (infoC(IZQUIERDA)==1 && infoC(ARRIBA)!=1) {}
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;
        else if (infoC(DERECHA)!=1) dir=DERECHA;
        else dir=ABAJO;           
    break;    
    case DERECHA:
         if (infoC(ARRIBA)==1 && infoC(DERECHA)!=1) {} 
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;
        else if (infoC(ABAJO)!=1) dir=ABAJO;
        else dir=IZQUIERDA;
    break;                
    case ABAJO:
          if (infoC(DERECHA)==1 && infoC(ABAJO)!=1) {}
        else if (infoC(DERECHA)!=1) dir=DERECHA;
        else if (infoC(IZQUIERDA)!=1) dir=IZQUIERDA;
        else dir=ARRIBA;
    break;
     case IZQUIERDA:
            if (infoC(ABAJO)==1 && infoC(IZQUIERDA)!=1) {}           
        else if (infoC(ABAJO)!=1) dir=ABAJO;
        else if (infoC(ARRIBA)!=1) dir=ARRIBA;
        else dir=DERECHA;
    break;
    }
    return dir;           
}

void Rastro(int dir,int f,int c) {                                      // esto nos sirve para reordar, o sea si ya pasamos por este conjunto de paredes
                                                                        // entramos a un ciclo lo cual nos dice que ya pasamos por aca y hacemos lo mismo
                                                                        // de la vez pasada 
     switch(dir){                                                      
        case ARRIBA: if (infoC(ARRIBA)==4) ya=true;
        case DERECHA: if (infoC(DERECHA)==4) ya=true;           
        case IZQUIERDA: if (infoC(IZQUIERDA)==4) ya=true;
        case ABAJO: if (infoC(ABAJO)==4) ya=true;            
     }
     m[f][c]=4;                                                          // si llegasemos a regresar no se vuelve a marcar el puntito otra vez
	                                                                     // sino que, si ya tiene puntito ahi lo dejamos     
}


//######################################################## ESTO SIRVE PARA MOVER AL ROBOTON ##########################################################//
void mueveJugador(int dir) {                                     
     switch(dir){                                                  // Movemos al jugador
        case ARRIBA: m[fp-1][cp]=2;                                // refrescamos la matriz  proporcionalmente a como se mueve el roboton           
            fp--;                                                  // al igual que actualizamos las cordenadas donde estamos en la matrix  ya sea para izquierda,derecha
			                                                       // arriba abajo,desde entre   
        break;            
        case DERECHA: m[fp][cp+1]=2;             
             cp++;           
        break;            
        case IZQUIERDA: m[fp][cp-1]=2;             
            cp--; // Actualizamos coordenadas del jugador           
        break; 
        case ABAJO: m[fp+1][cp]=2; // actualizamos matriz           
            fp++; // Actualizamos coordenadas del jugador           
        break;            
     }     
}    


//##################################################### aqui es para ver en el mapa/laberinto/maze ###########################################################

int main() { 
    int old_fp,old_cp;  
    int metodo=0,meta=-1;                                             // poner 1 o 0 para izquierda o derecha y para ver todo lo recorrido al igual donde esta la meta
    int codAscii;
    bool pasoApaso=false;                                             
    bool vision=true;                                                      
    char tcl, arch[]=  "laberinto.txt";                             //definimos el archivo el cual hemos de leer para poder ver el laberinto
               
    dimensionaMatriz(arch);       
    leerArchivo(arch);                                                   // ahora leemos el archivo de .txt y luego   




//########################################################################### Bienvenidos a la Matrix ##########################################################
    movs=0; fp=ifp;cp=icp;                        // Aqui definimos os valores iniciales ¿A que me refiero? a que definimos la cordenada donde ha de empezar el robot
                                                  // a moverse  ya que fp y cp estaran cambiando constantemente y es por eso que entramos a un while y cuando el roboton
                                                 // llegue a la meta se salga del siclo y termine la partida y cuando este se mueva guardamos la coordenada pra colocar un espacio
                                                 // cuando este chalio se mueva 
               
    while (fp!=fs || cp!=cs) {                           // este es un whle para que se tire de una vez a imprimir los movimientos definidos mas abajo al igual
                                                        // que muestra el alberinto ya resuelto con un camino recorrido por el roboton 
                                                        // si usted quiere podner pausa apachurra una tecla 
                                                        
                                                        // si vemos o (simulamos que vemos) la meta el roboton se ira hacia ella hasta terminar el proceso
                                                        // por si acaso topamos con una pared esta la cosa llamada girar definido aca abajito tambien
                                                        
      old_fp=fp; old_cp=cp; 
      if (pasoApaso) {
         MuestraLaberinto();
         system("pause");               
      }
      if (vision) meta=metaCerca();  
      if (meta!=-1) direccion=meta; 
      else  if (metodo==0) direccion=evitaParedesIzq(direccion);
            else direccion=evitaParedesDer(direccion);   
      
      mueveJugador(direccion);
      Rastro(direccion,old_fp, old_cp);
      movs++;
      if (espacios*2-movs<0) break;  
    }
    MuestraLaberinto();
    if (fp==fs && cp==cs) {
        if (metodo==0) printf ("%d movimientos con el metodo de la mano izquierda. <Esc>", movs); 
        else printf ("%d movimientos con el metodo de la mano derecha. <Esc>", movs);
    }
    else printf ("El laberinto no tiene solucion. <Esc>");
    while (tcl!=27) tcl = getch();                   
    
    return 0;                                                                      // si se llegase el caso donde, el roboton no pudiera resolver el problema
                                                                                   // con el algoritmo de la mano derecha y/o izquierda entonces tiramos 
                                                                                   // mensaje de que no se puede ): 
                                                                                   
                                                                                   
}                                         


 // no todo el codigo es mio por cierto, la mitad lo vi en videos de youtube asi como el punto exe no lo hice yo 

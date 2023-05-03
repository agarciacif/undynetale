

#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"

int tiempo;
int seg;
int X, LIMX;
int Y, LIMY;
int tecla;
void juego()
{	
	ESTADO=INICIO;
	ConfigurarTeclado(0x400C); // Configurar el teclado.
	ConfigurarTemporizador( 56798,  0x00C1); // Configurar el temporizador.
	HabilitarIntTeclado(); // Habilitar las interrupciones del teclado.
	HabilitarInterrupciones();
	HabilitarIntTempo(); // Habilitar las interrupciones del temporizador.
	EstablecerVectorInt(); // Habilitar interrupciones.
	LIMX = 255;
	LIMY = 191;
	X = 127;
	Y = 95;


	while(1){
		if(TeclaDetectada()){ //DEBUG
			iprintf("\x1b[01;00HTecla pulsada: %d",TeclaPulsada());
			iprintf("\x1b[02;00HEstado: %d",ESTADO);
		}
		

		if(ESTADO == INICIO){
			MostrarRomboGrande(1,X,Y);		
		}

		if(ESTADO == JUEGO){
			BorrarRomboGrande(1,X,Y);			 
			if(TeclaDetectada()){
        		if(TeclaPulsada()  == ARRIBA && Y > 0){
            			MostrarArriba(2,X,Y);
        		}
        		else if(TeclaPulsada()== ABAJO && Y < LIMY){
					MostrarAbajo(2,X,Y);
        		}
        		else if(TeclaPulsada()== DERECHA && X < LIMX){
					MostrarDerecha(2,X,Y);        				
				}
        		else if(TeclaPulsada()== IZQUIERDA && X>0){
					MostrarIzquierda(2,X,Y);			        				
				}
    		}		
		}	
	}
}




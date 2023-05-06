

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
int X, LIMX, PX;
int Y, LIMY, PY;
int tecla, ultimaPos;
//int rand;
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
	ultimaPos = -1; //0: ARRIBA, 1: ABAJO, 2: DERECHA, 3:IZQUIERDA
	//r = rand() % 4; // [0,4)

	while(1){
		// if(TeclaDetectada()){ //DEBUG
		// 	iprintf("\x1b[01;00HTecla pulsada: %d",TeclaPulsada());
		// 	iprintf("\x1b[02;00HEstado: %d",ESTADO);
		// }
		
		if(ESTADO == INICIO){
			BorrarPersonaje(2,X,Y);			
			iprintf("\x1b[01;00HESQUIVA LAS BALAS!");
			iprintf("\x1b[02;00HPULSA LA PANTALLA PARA EMPEZAR");
			if(tactilTocada()){
				ESTADO = JUEGO;
				consoleClear();	
				MostrarArriba(2,X,Y);
			}		
		}

		if(ESTADO == JUEGO){
								 
			if(TeclaDetectada()){
        		if(TeclaPulsada() == ARRIBA){
            		MostrarPersonaje(0);
					ultimaPos = 0;
        		}
        		else if(TeclaPulsada() == ABAJO){
					MostrarPersonaje(1);
					ultimaPos = 1;
        		}
        		else if(TeclaPulsada() == DERECHA){
					MostrarPersonaje(2);
					ultimaPos = 2;
				}
        		else if(TeclaPulsada() == IZQUIERDA){
					MostrarPersonaje(3);
					ultimaPos = 3;
				}
				else if(TeclaPulsada() == L){ //POR INTERRUPCION
					ESTADO = PAUSA;			
				}
    		}
		}
		
		if(ESTADO == PAUSA){
			
			iprintf("\x1b[08;00HPAUSA");
			iprintf("\x1b[09;00HPULSA R PARA SEGUIR O START PARA VOLVER AL MENU");
			if(TeclaDetectada()){ //POR INTERRUPCION
				if(TeclaPulsada()==R){ //POR INTERRUPCION
					ESTADO = JUEGO;  //POR INTERRUPCION
					MostrarPersonaje(ultimaPos); //POR INTERRUPCION
					consoleClear(); //POR INTERRUPCION
					} //POR INTERRUPCION
				else if(TeclaPulsada()==START){ //POR INTERRUPCION
					ESTADO = INICIO; //POR INTERRUPCION
					consoleClear(); //POR INTERRUPCION
					} //POR INTERRUPCION					
			}	 //POR INTERRUPCION		
		}
		if (ESTADO == MUERTE)
		{
			iprintf("\x1b[08;00HHAS MUERTO, PULSA START PARA VOLVER AL MENU");
			if (TeclaDetectada()&&TeclaPulsada() == START) //Por interrupcion
			{ //POR INTERRUPCION
				ESTADO = INICIO; //POR INTERRUPCION
				consoleClear(); //POR INTERRUPCION
			} //POR INTERRUPCION
		}
	}
}
void BorrarPersonaje(int num, int posX, int posY){
	BorrarArriba(num,posX,posY);
	BorrarAbajo(num,posX,posY);
	BorrarDerecha(num,posX,posY);
	BorrarIzquierda(num,posX,posY);
}

void MostrarPersonaje(int pos){
	switch (pos)
	{
	case 0:
		MostrarArriba(2,X,Y);
		break;
	
	case 1:
		MostrarAbajo(2,X,Y);
		break;

	case 2:
		MostrarDerecha(2,X,Y);
		break;

	case 3:
		MostrarIzquierda(2,X,Y);
		break;
	}
}







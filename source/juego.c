

#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "rutinas.h"

int tecla, ultimaPos;
int vidasJugador;
struct Bala balas[MAX_BALAS];
int i;
int X,Y;
int puntos = 0;
int cont, tick, dif;
void juego()
{	
	ESTADO=INICIO;
	ConfigurarTeclado(0x430F); // Configurar el teclado.
	ConfigurarTemporizador( 56798,  0x00C1); // Configurar el temporizador.
	HabilitarIntTeclado(); // Habilitar las interrupciones del teclado.
	HabilitarInterrupciones();
	HabilitarIntTempo(); // Habilitar las interrupciones del temporizador.
	EstablecerVectorInt(); // Habilitar interrupciones.
	srand(time(NULL)); //Inicializa la semilla para randomizar las ubicaciones de las balas
	visualizarInicio();
	tecla = 0;
	ultimaPos = -1; //0: ARRIBA, 1: ABAJO, 2: DERECHA, 3:IZQUIERDA
	i = 0;
	while(1){
		//   if(TeclaDetectada()){ //DEBUG
		//   	iprintf("\x1b[05;00HTecla pulsada: %d",TeclaPulsada());
		//   	iprintf("\x1b[06;00HEstado: %d",ESTADO);
		// 	iprintf("\x1b[07;00HUltimaPos: %d",ultimaPos);
		// 	//iprintf("\x1b[04;00HVidas: %d",vidasJugador);
		// 	iprintf("\x1b[08;00HposX: %d, posY: %d",X,Y);
		//   }
		
		
		
		if(ESTADO == INICIO){
			BorrarPersonaje();			
			iprintf("\x1b[01;00HBLOQUEA LOS PROYECTILES!");
			iprintf("\x1b[02;00HPULSA LA PANTALLA PARA EMPEZAR");
	
			
			if(tactilTocada()){
				consoleClear();	
				MostrarPersonaje(ARRIBA);
				vidasJugador = VIDAS;
				iprintf("\x1b[04;00HVidas: %d",vidasJugador);
				iprintf("\x1b[06;07H----CONTROLES----");
				iprintf("\x1b[07;00HTeclas de direccion: dirigir escudo");
				iprintf("\x1b[08;00HL: PAUSA");
				visualizarJuego3();
				cont = tick = dif = 0;
				ESTADO = JUEGO;
			}		
		}

		if(ESTADO == JUEGO){
			//CONTROLES DEL PERSONAJE
			if(TeclaDetectada()){
        		tecla = TeclaPulsada();
				if(TeclaPulsada() == ARRIBA){
            		MostrarPersonaje(ARRIBA);
					ultimaPos = ARRIBA;
        		}
        		else if(TeclaPulsada() == ABAJO){
					MostrarPersonaje(ABAJO);
					ultimaPos = ABAJO;
        		}
        		else if(TeclaPulsada() == DERECHA){
					MostrarPersonaje(DERECHA);
					ultimaPos = DERECHA;
				}
        		else if(TeclaPulsada() == IZQUIERDA){
					MostrarPersonaje(IZQUIERDA);
					ultimaPos = IZQUIERDA;
				}
				else if(TeclaPulsada() == L){ //POR INTERRUPCION
					consoleClear(); //POR INTERRUPCION
					ESTADO = PAUSA;	//POR INTERRUPCION
				} //POR INTERRUPCION
    		}
		}
		
		if(ESTADO == PAUSA){

			iprintf("\x1b[01;00HPAUSA");
			iprintf("\x1b[02;00HPULSA R PARA SEGUIR O START PARA VOLVER AL MENU");
			if(TeclaDetectada()){ //POR INTERRUPCION
				if(TeclaPulsada()==R){ //POR INTERRUPCION
					consoleClear(); //POR INTERRUPCION
					iprintf("\x1b[04;00HVidas: %d",vidasJugador); //POR INTERRUPCION
					iprintf("\x1b[05;05H----CONTROLES----"); //POR INTERRUPCION
					iprintf("\x1b[06;00HTeclas de direccion: dirigir escudo"); //POR INTERRUPCION
					iprintf("\x1b[007;00HL: PAUSA"); //POR INTERRUPCION
					ESTADO = JUEGO;  //POR INTERRUPCION
					} //POR INTERRUPCION
				
				
				else if(TeclaPulsada()==START){ //POR INTERRUPCION
					consoleClear(); //POR INTERRUPCION
					int j; //POR INTERRUPCION
					//RESETEA EL ARRAY DE BALAS
					for (j = 0; j < MAX_BALAS; j++) //POR INTERRUPCION
					{ //POR INTERRUPCION
						balas[j].viva = 0; //POR INTERRUPCION
						if (balas[j].ubi == ARRIBA || balas[j].ubi == ABAJO) //POR INTERRUPCION
						{ //POR INTERRUPCION
							BorrarProyV(j,balas[j].posX,balas[j].posY); //POR INTERRUPCION
						} else{ //POR INTERRUPCION
							BorrarProyH(j,balas[j].posX,balas[j].posY); //POR INTERRUPCION
						} //POR INTERRUPCION
					} //POR INTERRUPCION
					visualizarInicio(); //POR INTERRUPCION
					ESTADO = INICIO; //POR INTERRUPCION
				} //POR INTERRUPCION					
			}	 //POR INTERRUPCION		
		}
		if (ESTADO == MUERTE)
		{
			iprintf("\x1b[01;00HHAS MUERTO");
			iprintf("\x1b[02;00HPULSA START PARA VOLVER AL MENU");
			if (TeclaDetectada()&&TeclaPulsada() == START) //Por interrupcion
			{ //POR INTERRUPCION
				consoleClear(); //POR INTERRUPCION
				visualizarInicio();
				ESTADO = INICIO; //POR INTERRUPCION
			} //POR INTERRUPCION
		}
	}
}








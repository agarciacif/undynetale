

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

	int LRInterr = 0x4300;
	ConfigurarTeclado(LRInterr); // Configurar el teclado.
	int StartInterr = 0x4008;
	
	ConfigurarTeclado(StartInterr);
	ConfigurarTemporizador(56798,  0x00C1); // Configurar el temporizador.
	
	EstablecerVectorInt(); // Habilitar interrupciones.
	
	HabilitarIntTeclado(); // Habilitar las interrupciones del teclado.
	HabilitarIntTempo(); // Habilitar las interrupciones del temporizador.
	
	HabilitarInterrupciones();
	
	srand(time(NULL)); //Inicializa la semilla para randomizar las ubicaciones de las balas
	tecla = i = 0;
	ultimaPos = -1; //0: ARRIBA, 1: ABAJO, 2: DERECHA, 3:IZQUIERDA
	ESTADO=INICIO;
	visualizarInicio();
	
	//Bucle principal del juego
	while(1){

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
				//----------------POR INTERRUPCION-----------------
				else if (TeclaPulsada() == L)
				{
					consoleClear();
					visualizarPausa();
					ESTADO = PAUSA;
				}
				//-------------------------------------------------
    		}
		}
		
		if(ESTADO == PAUSA){

			iprintf("\x1b[01;00HPAUSA");
			iprintf("\x1b[02;00HPULSA R PARA SEGUIR O START PARA VOLVER AL MENU");
			//----------------POR INTERRUPCION-----------------
			if (TeclaDetectada())
			{
				if (TeclaPulsada()==START)
				{
					consoleClear();
					int j;
					//RESETEA EL ARRAY DE BALAS
					for (j = 0; j < MAX_BALAS; j++)
					{
						balas[j].viva = 0;
						if (balas[j].ubi == ARRIBA || balas[j].ubi == ABAJO)
						{
							BorrarProyV(j,balas[j].posX,balas[j].posY);
						} else{
							BorrarProyH(j,balas[j].posX,balas[j].posY);
						}
					}	
					visualizarInicio();
					ESTADO = INICIO;
				}

				else if (TeclaPulsada()==R)
				{
					consoleClear();
					iprintf("\x1b[04;00HVidas: %d",vidasJugador);
					iprintf("\x1b[05;05H----CONTROLES----");
					iprintf("\x1b[06;00HTeclas de direccion: dirigir escudo");
					iprintf("\x1b[007;00HL: PAUSA");
					cambiarFondo();
					ESTADO = JUEGO;
				}
			}
			//-------------------------------------------------
		}
		if (ESTADO == MUERTE)
		{
			iprintf("\x1b[01;00HHAS MUERTO");
			iprintf("\x1b[02;00HPULSA START PARA VOLVER AL MENU");
			//----------------POR INTERRUPCION-----------------
			if (TeclaDetectada()&&TeclaPulsada()==START)
			{
				consoleClear();
				visualizarInicio();
				ESTADO = INICIO;
			}
			//-------------------------------------------------
		}
	}
}








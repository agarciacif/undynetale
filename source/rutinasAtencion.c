/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int ESTADO;
struct Bala balas[MAX_BALAS];
int vidasJugador;
int tick;
int cont;
int dif;
void RutAtencionTeclado ()
{	
	int tecla = TeclaPulsada();
	switch (tecla)
	{
	case START:
		if (ESTADO == PAUSA) 
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
		} else if(ESTADO == MUERTE){
			consoleClear();
			visualizarInicio();
			ESTADO = INICIO;
		} break;
	
	case L:
		if (ESTADO == JUEGO)
		{
			consoleClear();
			iprintf("\x1b[01;00HPAUSA");
			iprintf("\x1b[02;00HPULSA R PARA SEGUIR O START PARA VOLVER AL MENU");
			visualizarPausa();
			ESTADO = PAUSA;
		} 
		break;
	
	case R:
		if (ESTADO == PAUSA)
		{
			consoleClear();
			iprintf("\x1b[04;00HVidas: %d",vidasJugador);
			iprintf("\x1b[05;05H----CONTROLES----");
			iprintf("\x1b[06;00HTeclas de direccion: dirigir escudo");
			iprintf("\x1b[007;00HL: PAUSA");
			cambiarFondo();
			ESTADO = JUEGO;
		} break;
	}
}


void RutAtencionTempo()
{
	int i, puntos;
	
	if (ESTADO==JUEGO)
	{
		tick++;
		
		if (tick%(50-dif)==0) //La frecuencia de aparición de balas
		{
			dispararBala();
			cont++;
		}
		if (cont == 10) //Cada 50*10 ticks, se disminuye en 1 los ticks de frecuencia de aparición, aumentando así la dificultad del juego progresivamente
		{
			cont = 0;
			dif++;
		}
		

		//iprintf("\x1b[01;00HPuntuacion=%d",tick);

		for(i = 0; i<MAX_BALAS; i++)
		{
			if (balas[i].viva)
			{
				if (balas[i].ubi==ARRIBA) //ARRIBA -> y++
				{
					if (ultimaPos==ARRIBA && balas[i].posY==70) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=ARRIBA && balas[i].posY > 70) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
						cambiarFondo();
					}
					else //La bala sigue su recorrido
					{
						balas[i].posY++;
						MostrarProyV(i,balas[i].posX,balas[i].posY);	
					}
				}
				if (balas[i].ubi==ABAJO) //ABAJO -> y--
				{
					if (ultimaPos==ABAJO && balas[i].posY==105) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;	
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=ABAJO && balas[i].posY < 105) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
						cambiarFondo();
					}
					else //La bala sigue su recorrido
					{
						balas[i].posY--;
						MostrarProyV(i,balas[i].posX,balas[i].posY);	
					}
				}
				if (balas[i].ubi==DERECHA) //DERECHA -> x--
				{

					if (ultimaPos==DERECHA && balas[i].posX==137) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;	
						BorrarProyH(i,balas[i].posX,balas[i].posY);
						cambiarFondo();
					}
					else if (ultimaPos!=DERECHA && balas[i].posX < 137) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
						cambiarFondo();
					}
					else //La bala sigue su recorrido
					{
						balas[i].posX--;
						MostrarProyH(i,balas[i].posX,balas[i].posY);
					}
					
				}
				if (balas[i].ubi==IZQUIERDA) //IZQUIERDA -> x++
				{
					if (ultimaPos==IZQUIERDA && balas[i].posX==103) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						puntos++;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=IZQUIERDA && balas[i].posX > 103) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
						cambiarFondo();
					}
					else //La bala sigue su recorrido
					{
						balas[i].posX++;
						MostrarProyH(i,balas[i].posX,balas[i].posY);
					}
					
				}
				iprintf("\x1b[04;00HVidas: %d",vidasJugador);
				if (vidasJugador <= 0)
				{
					int j;
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
					consoleClear();
					visualizarMuerte();
					ESTADO = MUERTE;
				}
					
			}
		}
	}
}

void EstablecerVectorInt()
{
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	
}


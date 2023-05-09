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
int seg3;
extern struct Bala balas[30];
void RutAtencionTeclado ()
{	

	if (ESTADO == PAUSA)
	{
		if(TeclaPulsada()==R){
			ESTADO = JUEGO;
			MostrarPersonaje(ultimaPos);
			consoleClear();
		}
		else if(TeclaPulsada()==START){
			ESTADO = INICIO;
			consoleClear();
		}
	}
	

	if (TeclaPulsada() == L && ESTADO == JUEGO)
	{
		ESTADO = PAUSA;
	}
	
	if (TeclaPulsada() == START && ESTADO == MUERTE)
	{
		ESTADO = INICIO;
		consoleClear();
	}
}


void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	int i = 0;
	if (ESTADO==JUEGO)
	{
		tick++; 
		if (tick==5)
		{
			seg++;
			iprintf("\x1b[15;0HTiempo transcurrido=%d", seg);
			tick=0;
		}
		if (seg%6==0)
		{
		while(i<30)
		{
			if (balas[i].viva)
			{
				if (balas[i].ubi==0) //ARRIBA -> y++
				{
					if (ultimaPos==0 && balas[i].posY==95) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=0 && balas[i].posY>=95) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posY--;
						MostrarProyV(i,balas[i].posX,balas[i].posY);	
					}
				}

				if (balas[i].ubi==1) //ABAJO -> y--
				{
					if (ultimaPos==1 && balas[i].posY==98) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=1 && balas[i].posY<=97) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posY++;
						MostrarProyV(i,balas[i].posX,balas[i].posY);	
					}
				}


				if (balas[i].ubi==2) //DERECHA -> x--
				{

					if (ultimaPos==2 && balas[i].posX==129) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=2 && balas[i].posX<=128) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posX--;
						MostrarProyH(i,balas[i].posX,balas[i].posY);
					}
					
				}
				if (balas[i].ubi==3) //IZQUIERDA -> x++
				{
					if (ultimaPos==3 && balas[i].posX==125) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=3 && balas[i].posX >=126) //La bala le ha dado al jugador===No estaba bloqueandola
					{
						vidasJugador--;
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else //La bala sigue su recorrido
					{
						balas[i].posX++;
						MostrarProyH(i,balas[i].posX,balas[i].posY);
					}
					
				}
				
				
			}
			
		}
		i++;
	}

	}
}

void EstablecerVectorInt()
{
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	
}


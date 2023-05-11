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
struct Bala balas[MAX_BALAS];
int vidasJugador;
void RutAtencionTeclado ()
{	
	MostrarRomboGrande(6,30,30);
	// if (ESTADO == PAUSA)
	// {
	// 	if(TeclaPulsada()==R){
	// 		ESTADO = JUEGO;
	// 		MostrarPersonaje(ultimaPos);
	// 		consoleClear();
	// 	}
	// 	else if(TeclaPulsada()==START){
	// 		ESTADO = INICIO;
	// 		consoleClear();
	// 	}
	// }
	

	// if (TeclaPulsada() == L && ESTADO == JUEGO)
	// {
	// 	ESTADO = PAUSA;
	// }
	
	// if (TeclaPulsada() == START && ESTADO == MUERTE)
	// {
	// 	ESTADO = INICIO;
	// 	consoleClear();
	// }

}


void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	int i;
	
	
	if (ESTADO==JUEGO)
	{
		tick++; 
		if (tick==5)
		{
			seg++;
			//iprintf("\x1b[15;0HTiempo transcurrido=%d", seg);
			tick=0;
		}
		if (seg==20)
		{
		seg = 0;
		
		dispararBala();
		}
		for(i = 0; i<MAX_BALAS; i++)
		{
			if (balas[i].viva)
			{
				if (balas[i].ubi==ARRIBA) //ARRIBA -> y++
				{
					if (ultimaPos==ARRIBA && balas[i].posY==90) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=ARRIBA && balas[i].posY>=90) //La bala le ha dado al jugador===No estaba bloqueandola
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
				if (balas[i].ubi==ABAJO) //ABAJO -> y--
				{
					if (ultimaPos==ABAJO && balas[i].posY==101) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyV(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=ABAJO && balas[i].posY<=101) //La bala le ha dado al jugador===No estaba bloqueandola
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
				if (balas[i].ubi==DERECHA) //DERECHA -> x--
				{

					if (ultimaPos==DERECHA && balas[i].posX==132) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=DERECHA && balas[i].posX<=132) //La bala le ha dado al jugador===No estaba bloqueandola
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
				if (balas[i].ubi==IZQUIERDA) //IZQUIERDA -> x++
				{
					if (ultimaPos==IZQUIERDA && balas[i].posX==120) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
						BorrarProyH(i,balas[i].posX,balas[i].posY);
					}
					else if (ultimaPos!=IZQUIERDA && balas[i].posX >=120) //La bala le ha dado al jugador===No estaba bloqueandola
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
	}
}

void EstablecerVectorInt()
{
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	
}


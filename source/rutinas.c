
#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
int X,Y, puntos;

struct Bala balas[MAX_BALAS];
void BorrarPersonaje(){
	BorrarArriba(PlayerID,X,Y);
	BorrarAbajo(PlayerID,X,Y);
	BorrarDerecha(PlayerID,X,Y);
	BorrarIzquierda(PlayerID,X,Y);
}

void MostrarPersonaje(int pos){
	switch (pos)
	{
	case ARRIBA:
		MostrarArriba(PlayerID, X, Y);
		break;
	
	case ABAJO:
		MostrarAbajo(PlayerID, X, Y);
		break;

	case DERECHA:
		MostrarDerecha(PlayerID, X, Y);
		break;

	case IZQUIERDA:
		MostrarIzquierda(PlayerID, X, Y);
		break;
	}
}

void vaciarArrayBalas(){
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

}

void dispararBala(){
	//crea nueva bala en una posición libre
	int i = 0;
	int j = 0;	
	
	int r = rand() % 4;
	while (j < 30)
		{
			if (!balas[j].viva)
			{
				i = j;
				break;
			}
			j++;
		}
	
	//elige la ubicación de la nueva bala

	int random = r+4;
	balas[i].ubi=random;
	switch (random)
		{
			case ARRIBA: //Bala arriba
				balas[i].posX = 120;
				balas[i].posY = 0;
				MostrarProyV(i,balas[i].posX,balas[i].posY);
				break;
			case ABAJO: //Bala abajo
				balas[i].posX = 120;
				balas[i].posY = 191;
				MostrarProyV(i,balas[i].posX,balas[i].posY);
				break;
			case DERECHA: //Bala derecha
				balas[i].posX = 255;
				balas[i].posY = 88;
				MostrarProyH(i,balas[i].posX,balas[i].posY);
				break;
			case IZQUIERDA: //Bala izquierda
				balas[i].posX = 0;
				balas[i].posY = 88;
				MostrarProyH(i,balas[i].posX,balas[i].posY);
				break;
			default:
				break;
		}
	balas[i].viva = 1;
		
}

void moverBalas(){
	int i;
	for(i = 0; i<MAX_BALAS; i++)
		{
			if (balas[i].viva)
			{
				if (balas[i].ubi==ARRIBA) //ARRIBA -> y++
				{
					if (ultimaPos==ARRIBA && balas[i].posY==70) //el jugador ha bloqueado el proyectil
					{
						balas[i].viva = 0;
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
				if (vidasJugador <= 0) //El jugador ha perdido la partida
				{
					vaciarArrayBalas();
					consoleClear();
					visualizarMuerte();
					ESTADO = MUERTE;
				}
					
			}
		}
	
}

void cambiarFondo(){ 
	switch (vidasJugador)
		{
		case 3:
			visualizarJuego3();
			break;
		case 2:
			visualizarJuego2(); 
			break;
		case 1: 
			visualizarJuego1();
			break;
		default:
			break;
		}
}
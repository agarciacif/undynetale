
#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto
	
#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
int X,Y;

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

	int random = r+4; //TODO: RAND(4) + 4
	balas[i].ubi=random;
	switch (random)
		{
			case ARRIBA: //Bala arriba
				balas[i].posX = 127;
				balas[i].posY = 0;
				MostrarProyV(i,balas[i].posX,balas[i].posY);
				break;
			case ABAJO: //Bala abajo
				balas[i].posX = 127;
				balas[i].posY = 191;
				MostrarProyV(i,balas[i].posX,balas[i].posY);
				break;
			case DERECHA: //Bala derecha
				balas[i].posX = 255;
				balas[i].posY = 95;
				MostrarProyH(i,balas[i].posX,balas[i].posY);
				break;
			case IZQUIERDA: //Bala izquierda
				balas[i].posX = 0;
				balas[i].posY = 95;
				MostrarProyH(i,balas[i].posX,balas[i].posY);
				break;
			default:
				break;
		}
	balas[i].viva = 1;
		
}

void visualizarVidas(){ //TODO: implementar
	int vx, vy, i;
	vx = 10;
	vy = 170;
	 
	for (i = 0; i < vidasJugador; i++)
	{
	 	MostrarVida(i,vx,vy);
		vx+=20;
	}
	


}
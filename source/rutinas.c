
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
		MostrarArriba(2, X, Y);
		break;
	
	case 1:
		MostrarAbajo(2, X, Y);
		break;

	case 2:
		MostrarDerecha(2, X, Y);
		break;

	case 3:
		MostrarIzquierda(2, X, Y);
		break;
	}
}

void dispararBala(){
	//crea nueva bala en una posición libre
	int i = 0;
	int j = 0;	
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
	int random = 0; //TODO: RAND(4)
	balas[i].ubi=random;
	switch (random)
		{
			case 0: //Bala arriba
				balas[i].posX = 127;
				balas[i].posY = 0;
				MostrarProyV(i,balas[i].posX,balas[i].posY);
				break;
			case 1: //Bala abajo
				balas[i].posX = 127;
				balas[i].posY = 191;
				MostrarProyV(i,balas[i].posX,balas[i].posY);
				break;
			case 2: //Bala derecha
				balas[i].posX = 255;
				balas[i].posY = 95;
				MostrarProyH(i,balas[i].posX,balas[i].posY);
				break;
			case 3: //Bala izquierda
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
	int vx, vy;
	vx = 10;
	vy = 170;
	for (int i = 0; i < vidasJugador; i++)
	{
		MostrarVida(i,vx,vy);
		vx+=20;

	}
	


}
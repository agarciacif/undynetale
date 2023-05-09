/*---------------------------------------------------------------------------------
Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
y en otro ejemplo de Jaeden Ameronen
---------------------------------------------------------------------------------*/

#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estandar de C
#include <stdlib.h>		//librería estandar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "graficos.h"		
#include "definiciones.h"
#include "sprites.h"
#include "juego.h"

int X,Y;
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	EstablecerPaletaPrincipal();
	inicializarGraficosSprites();
	HabilitarInterrupciones();
	X = 127;
	Y = 95;
	// llamada al juego que vosotros programaréis
	juego();

	return(0);

}

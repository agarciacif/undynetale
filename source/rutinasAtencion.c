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

void RutAtencionTeclado ()
{
	if (TeclaPulsada() == START && ESTADO == INICIO)
	{
		ESTADO = JUEGO;
	}
	if (TeclaPulsada() == SELECT && ESTADO == JUEGO)
	{
		ESTADO = INICIO;
	}
	
	
	


}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;

	if (ESTADO==JUEGO)
	{
		tick++; 
		if (tick==5)
		{
			seg++;
			iprintf("\x1b[13;5HTiempo transcurrido=%d", seg);
			tick=0;
		}
	}
	
	
}

void EstablecerVectorInt()
{
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	
}


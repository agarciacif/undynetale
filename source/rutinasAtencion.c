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
			vaciarArrayBalas();
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
		moverBalas();
	}
}

void EstablecerVectorInt()
{
	irqSet(IRQ_TIMER0, RutAtencionTempo);
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	
}


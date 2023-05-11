/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; //variable para guardar la tecla pulsada



int TeclaDetectada() 
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int TeclaPulsada() 
{
if ((~TECLAS_DAT & 0x0001)!=0){return A;
}else if((~TECLAS_DAT & 0x0002)!=0){return B;
}else if((~TECLAS_DAT & 0x0004)!=0){return SELECT;

}else if((~TECLAS_DAT & 0x0008)!=0){return START;
}else if((~TECLAS_DAT & 0x0010)!=0){return DERECHA;
}else if((~TECLAS_DAT & 0x0020)!=0){return IZQUIERDA;
}else if((~TECLAS_DAT & 0x0040)!=0){return ARRIBA;
}else if((~TECLAS_DAT & 0x0080)!=0){return ABAJO;
}else if((~TECLAS_DAT & 0x0100)!=0){return R;
}else if((~TECLAS_DAT & 0x0200)!=0){return L;
}

}

void ConfigurarTeclado(int Conf_Tec)
{
	//Configuración del teclado. Modificar su registro de control en base a los bits
        //activados en el parametro Conf_Tec
	TECLAS_CNT|=Conf_Tec;
}

void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{
	//Configuración del temporizador. El latch es el valor del registro de datos del temporizador
        //Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo
	TIMER0_DAT=Latch;
	TIMER0_CNT|=Conf_Tempo;
	
}

void HabilitarIntTeclado()
{
	//Habilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
        //ESCRIBIR AQUÍ VUESTRO CÓDIGO
	IE|=0x00001000;
	IME=1;
}

void InhibirIntTeclado()
{

	//Deshabilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 

	IME=0;
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO	
	IE &=0xFFFFEFFF;
	IME=1;
}  

void HabilitarIntTempo()
{


	//Habilitar las interrupciones del temporizador (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO
	IE|=0x00000008;
	IME=1;
}

void InhibirIntTempo()
{

	//Deshabilitar las interrupciones del temporizado (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
	
	IE&=0xFFFFFFF7;
	IME=1;

}

void PonerEnMarchaTempo()
{
	TIMER0_CNT|=0x0080;
	
}

void PararTempo()
{
	TIMER0_CNT&=0xFF7F;
	
}
int tactilTocada(){
	touchPosition pos_Pantalla;
	touchRead(&pos_Pantalla);
	return !(pos_Pantalla.px==0 && pos_Pantalla.py==0);
}

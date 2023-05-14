
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "fondos.h"
#include "graficos.h"
#include "Puerta.h"
#include "PuertaAbierta.h"
#include "Inicio.h"
#include "Juego1.h"
#include "Juego2.h"
#include "Juego3.h"
#include "Muerte.h"
#include "Pausa.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarPuerta() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPuertaAbierta() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaAbiertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaAbiertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarInicio() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     InicioBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     InicioBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
void visualizarJuego1(){
    dmaCopyHalfWords(DMA_CHANNEL,
                     Juego1Bitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     Juego1BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
void visualizarJuego2(){ 
    dmaCopyHalfWords(DMA_CHANNEL,
                     Juego2Bitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     Juego2BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */

}
void visualizarJuego3(){
    dmaCopyHalfWords(DMA_CHANNEL,
                     Juego3Bitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     Juego3BitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
void visualizarPausa(){
    dmaCopyHalfWords(DMA_CHANNEL,
                     PausaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PausaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
void visualizarMuerte(){
    dmaCopyHalfWords(DMA_CHANNEL,
                     MuerteBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     MuerteBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}
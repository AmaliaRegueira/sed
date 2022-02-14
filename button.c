/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "def.h"
/*--- variables globales ---*/
int symbol = 0;
/*--- funciones externas ---*/
//extern void D8Led_Symbol(int value);
/*--- declaracion de funciones ---*/
void Eint4567_ISR(void) __attribute__ ((interrupt ("IRQ")));
void Eint4567_init(void);
extern void leds_switch ();
extern void D8Led_symbol(int value);
extern int contador;

/*--- codigo de funciones ---*/
void Eint4567_init(void)
{
	/* Configuracion del controlador de interrupciones */
		// Borra EXTINTPND escribiendo 1s en el propio registro
		rEXTINTPND = 0Xf;
		// Borra INTPND escribiendo 1s en I_ISPC
		rI_ISPC = 0x3ffffff;
		// Configura las lineas como de tipo IRQ mediante INTMOD
		rINTMOD = 0x0;
		// Habilita int. vectorizadas y la linea IRQ (FIQ no) mediante INTCON
		rINTCON = 0x1;
		// Enmascara todas las lineas excepto Eint4567 y el bit global (INTMSK)
		rINTMSK = ~(BIT_EINT4567 | BIT_GLOBAL);
		// Establecer la rutina de servicio para Eint4567
		pISR_EINT4567 = (unsigned)Eint4567_ISR;
	/* Configuracion del puerto G */
		// Establece la funcion de los pines (EINT7-EINT0)
		rPCONG = 0xff3f;
		//Habilita las resistencias de pull-up
		rPUPG = 0x0;
		// Configura las lineas de int. como de flanco de bajada mediante EXTINT
		rEXTINT = 0x22220000;
	/* Por precaucion, se vuelven a borrar los bits de INTPND y EXTINTPND */
		rEXTINTPND = 0xf;
		rI_ISPC = 0x3ffffff;
}
int which_int;
void Eint4567_ISR(void)
{
	which_int = rEXTINTPND;
	leds_off();
	switch (which_int) {
	   case 4 :
		led1_on();
		contador = ( contador + 1 ) % 16 ;
	    break;
	   case 8  :
		   led2_on();
		   contador = (contador -1 ) % 16 ;
	      break;

	}
	D8Led_symbol(contador);
	DelayMs(100);
	rEXTINTPND = 0xC;
	rI_ISPC = BIT_EINT4567;
}

/*COMENTAR PARA LA PARTE DEL 8-SEGMENTOS
DESCOMENTAR PARA LA PRIMERA PARTE CON INTERRUPCIONES



void Eint4567_ISR(void)
{
	if ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) { // comprobamos los botones
		while ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) { // esperamos a que se dejen de pulsar
			DelayMs(100);
		}
		leds_switch();//se cambia el led
		DelayMs(100);
	}
	rEXTINTPND = 0xC;
	rI_ISPC = 0x3ffffff;
}*/

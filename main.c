/* ficheros de cabecera */
#include "44blib.h"
#include "44b.h"
#include "stdio.h"

/* funciones externas */
extern void leds_off();
extern void led1_on();
//extern void leds_switch();
extern void sys_init();
extern void Eint4567_init(void);

int contador;

void buttons_init(){
	rPCONG = rPCONG & ~(0x01<<12);
	rPCONG = rPCONG & ~(0x01<<13);
	rPCONG = rPCONG & ~(0x01<<14);
	rPCONG = rPCONG & ~(0x01<<15);

	rPUPG = 0;
}

/*Apartado 1
void Main(void)
{
	//Inicializar controladores
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	//Establecer valor inicial de los LEDs
	leds_off();
	led1_on();

	buttons_init();
	while (1){
		if ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) { // comprobamos los botones
			while ( (rPDATG & 0x00000040) == 0 || (rPDATG & 0x00000080) == 0) { // esperamos a que se dejen de pulsar
				DelayMs(100);
			}
			leds_switch();//se cambia el led
			DelayMs(100);
		}
	}
}*/

void Main(void)
{
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	buttons_init(); // Inicializar botones
	Eint4567_init();
	leds_off();
	led1_on();
	while (1){}
}
/*
void Main(void)
{
	 Inicializar controladores
	contador = 0;
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	D8Led_init();
	buttons_init(); // Inicializar botones
	Eint4567_init();
	 Establecer valor inicial de los LEDs
	leds_off();
	while (1){}
}*/

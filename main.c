/*--- ficheros de cabecera ---*/
#include "44blib.h"
#include "44b.h"
#include "stdio.h"
/*--- funciones externas ---*/
extern void leds_off();
extern void led1_on();
extern void leds_switch();
extern void Eint4567_init(void);
//extern void sys_init();
/*--- declaracion de funciones ---*/
//void Main(void);
void buttons_init(){
	int desp1 = 6*2; // Son seis pares de bits para el PIN6
	int desp2 = 7*2; // Son siete pares de bits para el PIN7

	rPCONG =~(0xf<<desp1); // Inicializamos los pines 6 y 7

	rPUPG &= ~(0x1 <<6); //activamos las seniales de eint6
	rPUPG &= ~(0x1 <<7); //activamos las seniales de eint7
}

/*--- codigo de funciones ---*/
void Main(void)
{
	/* Inicializar controladores */
	sys_init(); // Inicializacion de la placa, interrupciones y puertos
	/* Establecer valor inicial de los LEDs */
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
}

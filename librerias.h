#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

extern unsigned char contador;
extern unsigned char DISPLAY[];
extern unsigned char sumaADC;
extern char DisplayLow_ADC;
extern char DisplayHigh_ADC;
extern char ANTIREBOTE_CONTADOR1;
extern char ANTIREBOTE_CONTADOR2;
extern unsigned char Low_ADC;
extern unsigned char High_ADC;
extern unsigned char Resultado_ADC;

void InterruptADC(char* DisplayLow_ADC, char* DisplayHigh_ADC);
void InterruptPortB();
void InterruptTMR0(char DisplayLow_ADC, char DisplayHigh_ADC);

#endif

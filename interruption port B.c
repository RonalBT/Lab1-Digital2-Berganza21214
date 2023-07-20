/*
 * File:   interruption port B.c
 * Author: Ronal
 *
 * Created on 18 de julio de 2023, 12:50 PM
 */

#include <stdint.h>
#include <xc.h>
#include "librerias.h"

char ANTIREBOTE_CONTADOR1 = 0x00;
char ANTIREBOTE_CONTADOR2 = 0x00;
unsigned char Low_ADC;
unsigned char High_ADC;
unsigned char Resultado_ADC;
char DisplayLow_ADC;
char DisplayHigh_ADC;

unsigned char contador = 0x00;
unsigned char sumaADC;

unsigned char DISPLAY[0b00010000] = {
    0b1000000,//0
    0b1111001,//1
    0b0100100,//2
    0b0110000,//3
    0b0011001,//4
    0b0010010,//5
    0b0000010,//6
    0b1111000,//7
    0b0000000,//8
    0b0010000,//9
    0b0001000,//A
    0b0000011,//B
    0b1000110,//C
    0b0100001,//D
    0b0000110,//E
    0b0001110,};

void InterruptTMR0(char DisplayLow_ADC, char DisplayHigh_ADC){
    if(TMR0IF){
        TMR0 = 6;
        contador = !contador;
        
        if (contador == 0x01){
            RE1 = 0;
            RE0 = 1;
            PORTD = DISPLAY[DisplayLow_ADC];
        }
        if (contador == 0x00){
            RE0 = 0;
            RE1 = 1;
            PORTD = DISPLAY[DisplayHigh_ADC];
        }
        sumaADC = (DisplayHigh_ADC << 4) + DisplayLow_ADC;
        
        if (PORTC < sumaADC){
            RA0 = 0;
        }
        TMR0IF = 0;
    }
}


void InterruptADC(char* DisplayLow_ADC, char* DisplayHigh_ADC){
    if (ADIF == 1){
        ADIF = 0;
        High_ADC = ADRESH;
        High_ADC = High_ADC <<6; 
        
        Low_ADC = ADRESL;
        Low_ADC = (Low_ADC & 0b11111100) >> 2; 
        
        Resultado_ADC = High_ADC + Low_ADC; 
        *DisplayLow_ADC = Resultado_ADC & 0b00001111;
        *DisplayHigh_ADC = (Resultado_ADC & 0b11110000)>>4;
    }
}

void InterruptPortB(){
    if (RBIF == 1){
        if(RB0 == 1){
            ANTIREBOTE_CONTADOR1 = 0x01;
        }
        if (ANTIREBOTE_CONTADOR1 == 0x01 && RB0 == 0){
            PORTC = PORTC +1;
            ANTIREBOTE_CONTADOR1 = 0x00;
        }
        if(RB1 == 1){
            ANTIREBOTE_CONTADOR2 = 0x01;
        }
        if (ANTIREBOTE_CONTADOR2 == 0x01 && RB1 == 0){
            PORTC = PORTC - 1;
            ANTIREBOTE_CONTADOR2 = 0x00;
        }
        RBIF = 0;
    }
}

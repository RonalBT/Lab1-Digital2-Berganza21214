/*
 * File:   Laboratorio1Digital2.c
 * Author: Ronal
 *
 * Created on 18 de julio de 2023, 12:41 PM
 */

// CONFIG1
#pragma config FOSC = XT //INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "librerias.h"

// Establecemos los prototipos de funciones
void Setup(void);
void delay(char n);
void InterruptTMR0(char DisplayLow_ADC, char DisplayHigh_ADC);
void InterruptADC(char* DisplayLow_ADC, char* DisplayHigh_ADC);
void InterruptPortB();
//Definimos variables a utilizar
unsigned char Low_ADC;
unsigned char High_ADC;
unsigned char Resultado_ADC;
unsigned char sumaADC;
char DisplayLow_ADC;
char DisplayHigh_ADC;

//Array para mostrar los valores en los DIsplays 

unsigned char DISPLAY[0b00010000] ={
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

char ANTIREBOTE_CONTADOR1 = 0X00;
char ANTIREBOTE_CONTADOR2= 0X00;
unsigned char contador;

//Vector de Interrupción
void __interrupt() ISR(void){
    //Interrupción ADC
    InterruptADC(&DisplayLow_ADC, &DisplayHigh_ADC);
    //Interrupción TMR0
    InterruptTMR0(DisplayLow_ADC, DisplayHigh_ADC);
    //Interrupción del puerto B
    InterruptPortB();
}

//Loop Principal
void main(void){
    Setup();
    while(1){
        GO = 1;
        while(GO==1);
        delay(10);
    }
}

//Configuración
void Setup(void){
    PORTA= 0;
    PORTC= 0;
    PORTE= 0;
    PORTD= 0;
    TRISA= 0;
    TRISC= 0;
    TRISD= 0;
    TRISE= 0;
    contador = 0x00;
    
    TRISB = 0xFF;
    PORTB= 0;
    
    ANS11 = 1; 
    ANS10 = 0;
    ANS12 = 0;
    
    ADCON0 = 0xAD;
    ADCON1 = 0x80;
    
    ADIF = 0; //interrupciones del ADC
    ADIE = 1;
    PEIE = 1;
    
    IOCB0 = 1;
    IOCB1= 1;
    RBIE = 1;
    RBIF= 0;
    
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 6;  // prescaler 64
    T0IE = 1; //interrupciones TMR0
    T0IF = 1;
    TMR0 = 6; //desborde de 8ms
    
    GIE = 1; 
    IRCF0 = 1; //Oscilador 8MHz
    IRCF1 = 1;
    IRCF2 = 1;
    SCS = 1;
}
//delay
void delay(char n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 255; j++){
        }
    }
}

    

/* 
 * File:   transmitter_header.h
 * Author: AD
 *
 * Created on June 16, 2021, 8:46 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
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


#ifndef TRANSMITTER_MODULE
#define TRANSMITTER_MODULE

#include <xc.h>
#include <stdio.h>
#include <stdint.h>

#endif

#define _XTAL_FREQ 4000000 // HS = 4MHz

#define EUSART_SLAVE   // define EUSART_SLAVE to build SLAVE's HEX file 

/*  Function Prototype  */
void Setup_Interrupt( void );
void Setup_PORT( void );
void Setup_TMR0( void );

//
uint16_t Read_from_slave( void );
void Write_to_slave( uint8_t );

//
void EUSART_Initialize( void );
uint8_t EUSART_Read( void );
void EUSART_Write( uint8_t );

/*  External variable Declaration  */

// Declare bit-field type
typedef struct 
{
    unsigned Bit0 : 1;
    unsigned Bit1 : 1;
    unsigned Bit2 : 1;
    unsigned Bit3 : 1; 
    unsigned Bit4 : 1;
    unsigned Bit5 : 1;
    unsigned Bit6 : 1;
    unsigned Bit7 : 1;     
} bitfield_t;

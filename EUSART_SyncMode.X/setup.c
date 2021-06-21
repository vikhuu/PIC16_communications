#ifndef SETUP_H
#define SETUP_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#endif


void Setup_Interrupt( void )
{
    /* SETUP INTCON
     -   GIE   (1) Enable: Global Interrupt            
     -   PEIE  (1) Enable: Peripheral Interrupt         
     -   T0IE  (1) Enable: TMR0 overflow Interrupt    
     -   INTE  (0) Disable: External Interrupt         
     -   RBIE  (0) Disable: PORTB change Interrupt     
     -   T0IF  (0) Clear: TMR0 overflow Interrupt flag 
     -   INTF  (0) Clear: External Interrupt flag      
     -   RBIF  (0) Clear: PORTB change Interrupt flag  
    */
    INTCON = 0xE0; 
    
    //  EUSART Receive Interrupt Enable
    PIE1bits.RCIE = 1;
    
}

void Setup_PORT( void )
{
    /*  SETUP PORT  */
    
    //Set all pins as digital I/O
    ANSEL = ANSELH = 0; 
    
    //Clear PORTD & Setup all PORTD as outputs
    PORTD = 0x00;   
    TRISD = 0x00;
    
    //Clear PORTB & Setup all PORTB as inputs
    PORTB = 0x00;
    TRISB = 0x00;
    
}

void Setup_TMR0( void )
{
    /* SETUP TMR0  */
    /*   SETUP OPTION_REG
     -   nRBPU   (1)   : PORTB Pull-up resistor  
     -   INTEDG  (0)   : Interrupt Edge select  
     -   T0CS    (0)   : Internal Cycle Clock (Fosc/4)
     -   T0SE    (0)   : TMR0 Counter Edge select 
     -   PSA     (0)   : Pre-scaler is assigned to TMR0   
     -   PS      (001) : Pre-scaler = 1:4                     
    */
    OPTION_REG = 0x81;                       //0b10000001
    
    /*   Calculate the initial value that load into TMR0
         We need overflow after 1ms ( Fosc = 4Mhz, prescaler = 1:4)
         Ti = 2^8 - (overflow time us)/(Tosc*4*Prescaler)   
            = 2^8 - (1 * 10^3) / (0.25 * 4 * 4) = 6      */
    TMR0 = 6;  
}
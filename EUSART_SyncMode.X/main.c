/*
 * File:   transmitter_main.c
 * Author: AD
 *
 * Created on June 16, 2021, 8:46 PM
 */


#include "main_header.h"
#define EUSART_MASTER       // Undefine if use as SLAVE unit

/*  Define External Variables  */
volatile uint16_t counterTMR0 = 0; // A global variable to store the time 
                                   // that has elapse

void main(void)
{
    Setup_Interrupt();
    Setup_PORT();
    Setup_TMR0();
    
    while(1)
    {
        
    }
}


/*  Define Interrupt Service Routine  */
void __interrupt() isr()
{
#ifdef EUSART_MASTER
    // Process Interrupt of TMR0
    if( INTCONbits.T0IE && INTCONbits.T0IF )
    {
        INTCONbits.T0IF = 0;
        _delay(1);
        TMR0 = 13;
        counterTMR0++;
    }
#endif  
}

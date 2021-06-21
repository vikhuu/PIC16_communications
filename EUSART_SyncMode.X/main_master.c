/*
 * File:   transmitter_main.c
 * Author: AD
 *
 * Created on June 16, 2021, 8:46 PM
 */

#include "main_header.h"

#ifndef EUSART_SLAVE

/*  Define External Variables  */
volatile uint16_t counterTMR0 = 0; // A global variable to store the time 
                                   // that has elapse
uint8_t rx_buffer = 0;

/*  Declare Prototype   */


void main(void)
{
    Setup_PORT();
    Setup_Interrupt();  
    Setup_TMR0();
   
    uint16_t temp_tmr0 = 0;
    
    while(1)
    {
        if( (counterTMR0 - temp_tmr0) >= 100 )  // Every 100ms do...
        {
            temp_tmr0 = counterTMR0;
            //
            
            
            
        }
    }
}


/*  Define Interrupt Service Routine  */
void __interrupt() isr()
{
    // Process Interrupt of TMR0
    if( INTCONbits.T0IE && INTCONbits.T0IF )
    {
        INTCONbits.T0IF = 0;
        _delay(1);
        TMR0 = 13;
        counterTMR0++;
    }
}

/*  Define Functions   */
uint16_t Read_from_slave( void )
{
    
}

void Write_to_slave( uint8_t )
{
    
}

#endif

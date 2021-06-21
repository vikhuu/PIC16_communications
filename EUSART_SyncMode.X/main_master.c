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

/*  Declare Prototype   */


void main(void)
{
    Setup_PORT();
    Setup_Interrupt();  
    Setup_TMR0();
    
    EUSART_Initialize();
            
    uint16_t temp_tmr0 = 0;
    
    while(1)
    {
        if( (counterTMR0 - temp_tmr0) >= 100 )  // Every 100ms do...
        {
            temp_tmr0 = counterTMR0;
            //
            PORTD = Read_from_slave;
            //
            Write_to_slave( PORTB );            
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
    uint8_t buffer = 0;
    
    TXSTAbits.TX9D = 1; // read 
   
    _delay( 1 );
    EUSART_Write(0x00);
    
    // wait
    SREN = 1; // single-character received
    buffer = EUSART_Read();
    
    return buffer;
}

void Write_to_slave( uint8_t tx_data )
{
    TXSTAbits.TX9D = 0; // write
    
    _delay( 1 );
    EUSART_Write( tx_data );
}

#endif

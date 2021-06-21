/*
 * File:   main_slave.c
 * Author: AD
 *
 * Created on Ngày 21 tháng 6 n?m 2021, 17:05
 */


#include "main_header.h"

#ifdef EUSART_SLAVE

void main(void)
{
    
    EUSART_Initialize();
    Setup_PORT();
    
    uint8_t rx_buffer = 0;
            
    while( 1 )
    {
        rx_buffer = EUSART_Read;
        
        if( RCSTAbits.RX9D ) // Master read from
        {
            CREN = 0;   // Transmit
            EUSART_Write( PORTB );
        }
        else    // Master write to
        {
            PORTD = rx_buffer;
        }
        
        CREN = 1; // Receive
        rx_buffer = NULL;
    }
}
#endif

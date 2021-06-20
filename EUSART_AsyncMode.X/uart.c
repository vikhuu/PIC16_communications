#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdbool.h>
#include <stdint.h>

#endif


enum { FALSE, TRUE };


void UART_Initialize( void )
{
    /*  Setup the EUSART module   */
    
    // ABDOVF no_overflow; RCIDL idle; BRG16 8-bit; ABDEN disable
    BAUDCTL = 0x40;
    
    // SPEN enable; RX9 8-bit; CREN enable; ADDEN disable; OERR no_error
    RCSTA = 0x90;
    
    // TX9 8-bit; TXEN enable; SYNC asyn_mode; BRGH high_speed; TRMT empty
    TXSTA = 0x26;
    
    // Baud rate = 9600; SPBRG = 25; %error 0.16; Fosc = 4Mhz
    SPBRG = 0x19;
    
}

uint8_t UART_Read( void )
{
    while( PIR1bits.RCIF == 0 )    // if RCREG (rxData) is empty,
    ;                              // wait to receiving
    
    if( RCSTAbits.OERR == 1 )   // EUSART error
    {                           // Clear the Over-run error
        RCSTAbits.CREN = 0;
        _delay(1);
        RCSTAbits.CREN = 1;
    }
    
    return RCREG;
}

void UART_Write( uint8_t txData )
{
    while( PIR1bits.TXIF == 0 ) // TSR are busying 
    ;                           // wait to ready
       
    TXREG = txData;
}

/* 
     End of File
 */
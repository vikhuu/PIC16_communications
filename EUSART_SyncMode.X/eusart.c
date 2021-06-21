
#ifndef EUSART_H
#define EUSART_H

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#endif

#define EUSART_SYNC_MODE    // Undefine if use as Asynchronous Mode
#define EUSART_SLAVE      // Undefine if use as MASTER unit

void EUSART_Initialize( void )
{
    /*  Setup the EUSART module   */
    
#ifdef EUSART_SYNC_MODE
    // SCKP non-inverted; BRG16 16-bit
    BAUDCTL = 0x40;    
    
    /*  Setup TXSTA 
    -   CSRC  (/) : Master/Slave mode 
    -   TX9   (/) : 9-bit/8-bit Transmission
    -   TXEN  (1) : Transmit enable
    -   SYNC  (1) : Synchronous Mode
    -   SENDB (0) : Don't care
    -   BRGH  (0) : Unused
    -   TRMT  (0) : TST is empty
    -   TX9D  (0) : 9th bit of Transmit data
     */ 
    #ifndef EUSART_SLAVE
    TXSTA = 0xF0; // 0b11110000
    #else
    TXSTA = 0x30; // 0b00110000
    #endif
    
    /*  Setup RCSTA
    -   SPEN  (1) : Serial Port enable
    -   RX9   (/) : 9-bit/8-bit Reception
    -   SREN  (1) : Enable Single receive
    -   CREN  (/) : Continuous receive
    -   ADDEN (0) : Don't care
    -   FRRR  (0) : Framing error
    -   OERR  (0) : Over-run error
    -   RX9D  (0) : 9th bit of Received data     
     */
    #ifndef EUSART_SLAVE
    RCSTA = 0xA0; // 0b10100000
    #else
    RCSTA = 0xF0; // 0b11110000
    #endif    
    
    // Baud rate = 9600; Sync mode; SPBRG = 103; %error 0.16; Fosc = 4Mhz
    SPBRG = 103;
    
#else
    // ABDOVF no_overflow; RCIDL idle; BRG16 16-bit; ABDEN disable
    BAUDCTL = 0x40;
    
    // SPEN enable; RX9 8-bit; CREN enable; ADDEN disable; OERR no_error
    RCSTA = 0x90;
    
    // TX9 8-bit; TXEN enable; SYNC asyn_mode; BRGH high_speed; TRMT empty
    TXSTA = 0x26;
    
    // Baud rate = 9600; SPBRG = 25; %error 0.16; Fosc = 4Mhz
    SPBRG = 25;
#endif
}

uint8_t EUSART_Read( void )
{
    while( PIR1bits.RCIF == 0 )    // if RCREG (rxData) is empty,
    ;                              // wait to receiving

#ifndef EUSART_SYNC_MODE  
    if( RCSTAbits.OERR == 1 )   // EUSART error
    {                           // Clear the Over-run error
        RCSTAbits.CREN = 0;
        _delay(1);
        RCSTAbits.CREN = 1;
    }
#endif    
    
    return RCREG;
}

void EUSART_Write( uint8_t txData )
{
    while( PIR1bits.TXIF == 0 ) // TSR are busying 
    ;                           // wait to ready
       
    TXREG = txData;
}

/* 
     End of File
 */
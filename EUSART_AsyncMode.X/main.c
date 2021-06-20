/*
 * File:   main.c
 * Author: AD
 *
 * Created on June 14, 2021, 3:35 PM
 */


#include "header.h"

/*  Define Global Variable  */
volatile char rx_Data = NULL;

void main(void)
{
    /*  SETUP PORT  */
    ANSEL = ANSELH = 0; //Set all pins as digital I/O
    PORTD = 0x00;   
    TRISD = 0x00;
    
    /*  SETUP INTERRUPT   */
    Setup_Interrupt();
    
    /*  SETUP ESUART  */
    UART_Initialize();
    
    //
    send_string( "Hello World\r" );
    __delay_ms(500);
    send_string( "The quick brown fox jump over the lazy dog\r\r" );
    __delay_ms(500);
    send_string( "Press number 1 to 8 for toggling PORTD's pin\r\r");
    
    while( 1 )
    {

        // 
        while( rx_Data == NULL)
        ;
                
        // Test case for read data through UART 
        switch ( rx_Data )
        {
            case '1':
                RD0 = ~RD0;
                send_string("~RD0\r");
            break;
            
            case '2':
                RD1 = ~RD1;
                send_string("~RD1\r");
            break;
            
            case '3':
                RD2 = ~RD2;
                send_string("~RD2\r");
            break;
            
            case '4':
                RD3 = ~RD3;
                send_string("~RD3\r");
            break;
            
            case '5':
                RD4 = ~RD4;
                send_string("~RD4\r");
            break;
            
            case '6':
                RD5 = ~RD5;
                send_string("~RD5\r");
            break;
            
            case '7':
                RD6 = ~RD6;
                send_string("~RD6\r");
            break;
            
            case '8':
                RD7 = ~RD7;
                send_string("~RD7\r");
            break;
            
            default:
                send_string("Error\r");
            break;
            
        }
        
        // Clear the receiving buffer
        //
        rx_Data = NULL; 
        
    }
    
}

/*  Define Interrupt Service Routine    */
void __interrupt() isr()
{
    // Process EUSART receiver interrupt
    if( PIE1bits.RCIE && PIR1bits.RCIF )    //  receive new data
    {
        rx_Data = UART_Read();
    }
}


/*  Define Functions   */
void send_string( char *string )
{
    while( *string != NULL )
    {
        UART_Write( *string );
        string++;
    }
}


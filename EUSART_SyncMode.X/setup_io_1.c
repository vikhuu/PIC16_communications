#ifndef SETUP_IO
#define SETUP_IO

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#endif


void Setup_Interrupt( void )
{
        /* SETUP INTCON
     -   GIE  - (1) Enable: Global Interrupt            
     -   PEIE - (1) Enable: Peripheral Interrupt         
     -   T0IE - (0) Disable: TMR0 overflow Interrupt    
     -   INTE - (0) Disable: External Interrupt         
     -   RBIE - (0) Disable: PORTB change Interrupt     
     -   RBIF - (0) Clear: TMR0 overflow Interrupt flag 
     -   INTF - (0) Clear: External Interrupt flag      
     -   RBIF - (0) Clear: PORTB change Interrupt flag  
    */
    INTCON = 0xC0; 
    
    //  EUSART Receive Interrupt Enable
    PIE1bits.RCIE = 1;
    
}
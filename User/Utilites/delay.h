/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/
#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC

/* Exported types ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void delay_us( uint32_t us );
void delay_ms( uint32_t ms );

#endif /* _DELAY_H_ */
/* End of file */

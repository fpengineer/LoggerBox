/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _RELAY_H_
#define _RELAY_H_

#include <stdint.h>


enum relay {
    RELAY_K1,   
    RELAY_K2,   
    RELAY_K3,   // EN pin
    RELAY_K4,   // FB pin
    RELAY_K5,   // BS pin
    RELAY_K6,
    RELAY_K7
};


void InitRelayAll(void);
void RelaySet(enum relay relay);
void RelayClear(enum relay relay);
void RelayClearAll(void);


#endif /* _RELAY_H_ */
/* End of file */

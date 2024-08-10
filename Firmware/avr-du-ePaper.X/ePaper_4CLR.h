#ifndef EPAPER_4CLR_H
#define	EPAPER_4CLR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
    
    //Configure the display
    void EPAPER_4CLR_Initialize(int8_t temp);
        
    //Update the display
    void EPAPER_4CLR_UpdateDisplay(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EPAPER_4CLR_H */


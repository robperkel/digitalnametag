#ifndef EPAPER_3CLR_H
#define	EPAPER_3CLR_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
    
#include "pixelManager.h"
    
//API Built for E2213JS0C1
//Other displays may be compatiable
//https://www.pervasivedisplays.com/product/2-13-e-ink-displays/
    
    //Configure the display
    void EPAPER_3CLR_Initialize(int8_t temp);
        
    //Load the display
    void EPAPER_3CLR_UpdateDisplay(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EPAPER_H */


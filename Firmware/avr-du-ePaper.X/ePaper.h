#ifndef EPAPER_H
#define	EPAPER_H

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
    void EPAPER_Initialize(void);
    
    //Load a test pattern
    void EPAPER_LoadTestPattern(void);
        
    //Load the display
    void EPAPER_UpdateDisplay(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EPAPER_H */


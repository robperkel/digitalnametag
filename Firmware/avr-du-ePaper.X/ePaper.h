#ifndef EPAPER_H
#define	EPAPER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
//2.13" EPAPER Pixel Counts
#define EPAPER_2_13_X 212
#define EPAPER_2_13_Y 104
    
#include <stdint.h>
#include <stdbool.h>
    
    //Initializes the EPAPER Display
    void EPAPER_Initialize(void);
    
    //Updates the display
    void EPAPER_UpdateDisplay(void);
    
    //Returns the temp of the MCU
    int8_t EPAPER_GetTemperature(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EPAPER_COMMON_H */


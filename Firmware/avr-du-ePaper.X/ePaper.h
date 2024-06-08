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
    
    //Sends the register address to the display
    void EPAPER_AddressRegister(uint8_t reg);
    
    //Load a test pattern
    void EPAPER_LoadTestPattern(void);
    
    //Writes wVal to [reg] then returns the result
    uint8_t EPAPER_ExchangeRegister8(uint8_t reg, uint8_t wVal);
    
    //Writes wVals to [reg] then returns the results
    void EPAPER_ExchangeRegister16(uint8_t reg, uint8_t* wVal, uint8_t* rVal, uint8_t len);
    
    //Load the display
    void EPAPER_UpdateDisplay(void);

#ifdef	__cplusplus
}
#endif

#endif	/* EPAPER_H */


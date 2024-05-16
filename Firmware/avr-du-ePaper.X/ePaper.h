#ifndef EPAPER_H
#define	EPAPER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
    
//API Built for E2213JS0C1
//Other displays may be compatiable
//https://www.pervasivedisplays.com/product/2-13-e-ink-displays/
    
#define PANEL_PIXEL_X 152UL
#define PANEL_PIXEL_Y 296UL
    
#define PANEL_COLUMNS (PANEL_PIXEL_X >> 3)
#define PANEL_ROWS PANEL_PIXEL_Y
    
    typedef uint8_t pixel_array_t[PANEL_ROWS][PANEL_COLUMNS];
    
    typedef enum {
        WHITE = 0, BLACK, RED
    } color_t;
    
    //Configure the display
    void EPAPER_Initialize(void);
    
    //Sends the register address to the display
    void EPAPER_AddressRegister(uint8_t reg);
    
    //Returns a pointer to the pixel array for BW
    pixel_array_t* EPAPER_GetPixelPointerBW(void);
    
    //Returns a pointer to the pixel array for R
    pixel_array_t* EPAPER_GetPixelPointerR(void);
    
    //Sets a pixel to the specified color
    void EPAPER_SetPixel(uint16_t x, uint16_t y, color_t color);
    
    //Clears the display
    void EPAPER_ClearDisplayBuffer(color_t fill);
    
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


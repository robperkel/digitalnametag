#ifndef PIXELMANAGER_H
#define	PIXELMANAGER_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
    
    typedef enum {
        WHITE = 0, BLACK, RED, YELLOW
    } color_t;
    
    typedef enum {
        BW = 0, BWR, BWRY
    } color_mode_t;
    
    //Rotation mode for pixel data
    typedef enum {
        LANDSCAPE_STANDARD, LANDSCAPE_FLIPPED, PORTRAIT_STANDARD, PORTRAIT_FLIPPED
    } screen_orientation_t;
    
#define DEFAULT_PANEL_X 104UL
#define DEFAULT_PANEL_Y 212UL
#define DEFAULT_PANEL_COLOR BWR
#define DEFAULT_ORIENTATION LANDSCAPE_STANDARD
    
//Size of the internal memory buffer
#define PIXEL_MEMORY_BUFFER_SIZE 5512UL
    
    //Init internal variables
    void PixelManager_Initialize(void);
    
    //Set display properties
    void PixelManager_SetDisplayWidth(uint16_t width);
    void PixelManager_SetDisplayHeight(uint16_t height);
    void PixelManager_SetDisplayColors(color_mode_t mode);
    void PixelManager_SetRotationMode(screen_orientation_t position);
    
    //Get display properties
    uint16_t PixelManager_GetDisplayWidth(void);
    uint16_t PixelManager_GetDisplayHeight(void);
    color_mode_t PixelManager_GetDisplayColors(void);
    screen_orientation_t PixelManager_GetRotationMode(void);
    
    //Get data byte for image loading
    uint8_t PixelManager_GetBWByte(uint16_t x, uint16_t y);
    uint8_t PixelManager_GetRByte(uint16_t x, uint16_t y);
    
    //Starts a new image stream
    void PixelManager_ResetSeqPixelPointers(void);
    
    //Loads data into buffer
    void PixelManager_LoadImage(color_t clr);
    
    //Sets a pixel to the specified color
    void PixelManager_SetPixel(uint16_t x, uint16_t y, color_t color);
    
#ifdef	__cplusplus
}
#endif

#endif	/* PIXELMANAGER_H */


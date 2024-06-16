#include "pixelManager.h"

#include <stdint.h>
#include <stdbool.h>

//Display Properties
static uint16_t dispWidth, dispHeight;
static color_mode_t colorMode;
static screen_orientation_t screenPos;

//Pixel Buffer
static uint8_t pixels[PIXEL_MEMORY_BUFFER_SIZE];

//Loader data
static uint16_t indexX, indexY;

//Init internal variables
void PixelManager_Initialize(void)
{
    dispWidth = DEFAULT_PANEL_X;
    dispHeight = DEFAULT_PANEL_Y;
    colorMode = DEFAULT_PANEL_COLOR;
    screenPos = DEFAULT_ORIENTATION;
}

void PixelManager_SetDisplayWidth(uint16_t width)
{
    dispWidth = width;
    PixelManager_ResetSeqPixelPointers();
}

void PixelManager_SetDisplayHeight(uint16_t height)
{
    dispHeight = height;
    PixelManager_ResetSeqPixelPointers();
}

void PixelManager_SetDisplayColors(color_mode_t mode)
{
    colorMode = mode;
}

void PixelManager_SetRotationMode(screen_orientation_t position)
{
    screenPos = position;
    PixelManager_ResetSeqPixelPointers();
}

uint16_t PixelManager_GetDisplayWidth(void)
{
    return dispWidth;
}

uint16_t PixelManager_GetDisplayHeight(void)
{
    return dispHeight;
}

color_mode_t PixelManager_GetDisplayColors(void)
{
    return colorMode;
}

screen_orientation_t PixelManager_GetRotationMode(void)
{
    return screenPos;
}

uint8_t PixelManager_GetBWByte(uint16_t x, uint16_t y)
{
    uint16_t bwIndex;
    bwIndex = (y * (dispWidth >> 3)) + (x);
    return pixels[bwIndex];
}

uint8_t PixelManager_GetRByte(uint16_t x, uint16_t y)
{
    uint16_t bwIndex, rIndex;
    bwIndex = (y * (dispWidth >> 3)) + (x);
    rIndex = bwIndex + ((dispWidth >> 3) * dispHeight);
    return pixels[rIndex];
}

uint8_t PixelManager_GetBWRYByte(uint16_t x, uint16_t y)
{
    uint16_t index;
    index = (y * (dispWidth >> 2)) + (x);
    return pixels[index];
}

//Starts a new image stream
void PixelManager_ResetSeqPixelPointers(void)
{
    switch (screenPos)
    {
        case LANDSCAPE_STANDARD:
        {
            indexX = 0;
            indexY = dispHeight - 1;
            break;
        }
        case LANDSCAPE_FLIPPED:
        {
            indexX = dispWidth - 1;
            indexY = dispHeight - 1;
            break;
        }
        case PORTRAIT_STANDARD:
        {
            indexX = 0;
            indexY = 0;
            break;
        }
        case PORTRAIT_FLIPPED:
        {
            indexY = dispHeight - 1;
            indexX = dispWidth - 1;
            break;
        }
        default:
        {
            indexX = 0;
            indexY = 0;
        }
    }
}

//Loads data into buffer
void PixelManager_LoadPixelStream(color_t clr)
{
    if ((clr == YELLOW) && (colorMode != BWRY))
    {
        //Not supported on current panel - convert to White
        clr = WHITE;
    }
    else if ((clr == RED) && (colorMode == BW))
    {
        //Not supported on current panel - convert to Black
        clr = BLACK;
    }
    
    PixelManager_SetPixel(indexX, indexY, clr);
    
    //Update image direction data
    switch (screenPos)
    {
        case LANDSCAPE_STANDARD:
        {
            if (indexY == 0)
            {
                indexY = dispHeight - 1;
                if (indexX != dispWidth)
                {
                    indexX++;
                }
            }
            else
            {
                indexY--;
            }
            break;
        }
        case LANDSCAPE_FLIPPED:
        {
            if (indexY == (dispHeight - 1))
            {
                indexY = 0;
                if (indexX != 0)
                {
                    indexX--;
                }
            }
            else
            {
                indexY++;
            }

            break;
        }
        case PORTRAIT_STANDARD:
        {
            if (indexX == (dispWidth - 1))
            {
                indexX = 0;
                if (indexY != (dispHeight - 1))
                {
                    indexY++;
                }
            }
            else
            {
                indexX++;
            }
            break;
        }
        case PORTRAIT_FLIPPED:
        {
            if (indexX == 0)
            {
                indexX = dispWidth - 1;
                if (indexY != 0)
                {
                    indexY--;
                }
            }
            else
            {
                indexX--;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

//Sets a pixel to the specified color
void PixelManager_SetPixel(uint16_t x, uint16_t y, color_t color)
{
    //Find the byte
    uint8_t bIndex = x >> 3;
    uint8_t mask = 0b1 << (7 - (x & 0b111));
    
    //Check display mode
    if (colorMode == BW)
    {
        //Compute memory addresses
        uint16_t bwIndex;
        bwIndex = (y * (dispWidth >> 3)) + bIndex;

        if (color == WHITE)
        {
            //White
            //Bits should be cleared
            pixels[bwIndex] &= ~mask;
        }
        else if (color == BLACK)
        {
            //Black
            pixels[bwIndex] |= mask;
        }
        else if (color == RED)
        {
            //Red (INVALID!)
            //Map to Black
            
            pixels[bwIndex] |= mask;
        }
        else if (color == YELLOW)
        {
            //Yellow (INVALID!)
            //Map to White

            pixels[bwIndex] &= ~mask;
        }
    }
    else if (colorMode == BWR)
    {
        //Compute memory addresses
        uint16_t bwIndex, rIndex;
        bwIndex = (y * (dispWidth >> 3)) + bIndex;
        rIndex = bwIndex + ((dispWidth >> 3) * dispHeight);

        if (color == WHITE)
        {
            //White
            //Bits should be cleared
            pixels[bwIndex] &= ~mask;
            pixels[rIndex] &= ~mask;
        }
        else if (color == BLACK)
        {
            //Black
            pixels[bwIndex] |= mask;
            pixels[rIndex] &= ~mask;
        }
        else if (color == RED)
        {
            //Red
            pixels[bwIndex] &= ~mask;
            pixels[rIndex] |= mask;
        }
        else if (color == YELLOW)
        {
            //Yellow (INVALID!)
            //Map to White

            pixels[bwIndex] &= ~mask;
            pixels[rIndex] &= ~mask;
        }
    }
    else if (colorMode == BWRY)
    {
        //BWRY
        bIndex = x >> 2;
        
        //00112233 <- Pixel Order
        uint8_t shift = ((3 - (x & 0b11)) << 1);
        mask = ~(0xFF << shift);
        
        //Compute memory addresses
        uint16_t pixelIndex;
        pixelIndex = (y * (dispWidth >> 2)) + bIndex;

        if (color == WHITE)
        {
            //White (0b01)
            pixels[pixelIndex] &= mask;
            pixels[pixelIndex] |= (0b01 << shift);
        }
        else if (color == BLACK)
        {
            //Black (0b00)
            pixels[pixelIndex] &= mask;
        }
        else if (color == RED)
        {
            //Red (0b11)
            pixels[pixelIndex] &= mask;
            pixels[pixelIndex] |= (0b11 << shift);
        }
        else if (color == YELLOW)
        {
            //Yellow (0b10)
            pixels[pixelIndex] &= ~mask;
            pixels[pixelIndex] |= (0b10 << shift);
        }
    }
}
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
        default:
        {
            indexX = 0;
            indexY = dispHeight - 1;
        }
    }
}

//Loads data into buffer
void PixelManager_LoadImage(color_t clr)
{
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
        //Yellow
        
        //TODO
    }
}
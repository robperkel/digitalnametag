#include "ePaper.h"
#include "pixelManager.h"
#include "./ePaper_3CLR.h"
#include "mcc_generated_files/system/system.h"

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

#define SCALING_FACTOR 1024

static uint16_t panelW = DEFAULT_PANEL_X, panelH = DEFAULT_PANEL_Y;
static color_mode_t mode = BWR;

void EPAPER_Initialize(void)
{
    //Get panel info
    panelW = PixelManager_GetDisplayWidth();
    panelH = PixelManager_GetDisplayHeight();
    mode = PixelManager_GetDisplayColors();
    
    int8_t dieTemp = EPAPER_GetTemperature();
    
    switch (mode)
    {
        case BW:
        {
            break;
        }
        case BWR:
        {
            EPAPER_3CLR_Initialize(dieTemp);
            break;
        }
        case BWRY:
        {
            break;
        }
        default:
        {
            //Unknown!
        }
    }
    
}

void EPAPER_UpdateDisplay(void)
{
    switch (mode)
    {
        case BW:
        {
            break;
        }
        case BWR:
        {
            EPAPER_3CLR_UpdateDisplay();
            break;
        }
        case BWRY:
        {
            break;
        }
        default:
        {
            //Unknown!
        }
    }
}

//Returns the temp of the MCU
int8_t EPAPER_GetTemperature(void)
{
    uint16_t adcResult = ADC0_GetConversion(ADC_MUXPOS_TEMPSENSE_gc);
    uint16_t sigrow_offset, sigrow_slope;
    sigrow_offset = SIGROW.TEMPSENSE1;
    sigrow_slope = SIGROW.TEMPSENSE0;
    
    volatile uint32_t temp = sigrow_offset - adcResult;
    temp *= sigrow_slope;
    temp += 512;
    temp /= SCALING_FACTOR;
    
    int16_t tempC = temp - 273;
    
    return (int8_t)(tempC & 0xFF);
}
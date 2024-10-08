#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "ePaper_3CLR.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "pixelManager.h"
#include "ePaper_SPI.h"

//Configure the display
void EPAPER_3CLR_Initialize(int8_t temp)
{
    /* POR Sequence:
     * 1. Power on VCC/VDD
     * 2. Wait 5 ms
     * 3. RESET = 1
     * 4. Wait 5 ms
     * 5. RESET = 0
     * 6. Wait 10 ms
     * 7. RESET = 1
     * 8. Wait 5 ms
     * 9. Soft Start (0x00, 0x0E)
     * 10. Wait 5 ms
     */
    
    //Power-Up Sequencing
    DELAY_milliseconds(5);
    DISP_RESET_SetHigh();
    DELAY_milliseconds(5);
    DISP_RESET_SetLow();
    DELAY_milliseconds(10);
    DISP_RESET_SetHigh();
    DELAY_milliseconds(5);
    EPAPER_SPI_WriteByte(0x00, 0x0E);
    DELAY_milliseconds(5);
    
    /* Set Temperature
     * 1. Input Temperature (0xE5, TSSET)
     * 2. Active Temperature (0xE0, 0x02)
     * 3. Panel Settings for 2.13" (0x00, 0xCF, 0x89)
     */
    
    uint8_t buffer[2] = {0xCF, 0x89};
    //NOTE: FOR OTHER PANEL SIZES, 3.7"/4.2"/4.37" (3) = 0x0F, 0x89
        
    EPAPER_SPI_WriteByte(0xE5, temp); //0x19 = 25C
    EPAPER_SPI_WriteByte(0xE0, 0x02);
    EPAPER_SPI_WriteBytes(0x00, buffer, 2);
}

////Fill the display with a color
//void EPAPER_ClearDisplayBuffer(color_t fill)
//{
//    uint8_t bwColor = 0x00;
//    uint8_t rColor = 0x00;
//    if (fill == BLACK)
//    {
//        bwColor = 0xFF;
//    }
//    if (fill == RED)
//    {
//        rColor = 0xFF;
//    }
//    
//    for (uint16_t y = 0; y < PANEL_ROWS; y++)
//    {
//        for (uint16_t x = 0; x < PANEL_COLUMNS; x++)
//        {
//            BW_Pixels[y][x] = bwColor;
//            R_Pixels[y][x] = rColor;
//        }
//    }
//}

//Load a test pattern
void EPAPER_LoadTestPattern(void)
{
//    //Stripes
//    uint8_t bwColor = 0x00, rColor = 0x00;
//    color_t nextColor = WHITE;
//    
//    for (uint16_t y = 0; y < PANEL_ROWS; y++)
//    {
//        if ((y & 0x07) == 0)
//        {
//            switch (nextColor)
//            {
//                case WHITE:
//                {
//                    bwColor = 0x00;
//                    rColor = 0x00;
//                    nextColor = BLACK;
//                    break;
//                }
//                case BLACK:
//                {
//                    bwColor = 0xFF;
//                    rColor = 0x00;
//                    nextColor = RED;
//                    break;
//                }
//                case RED:
//                {
//                    bwColor = 0x00;
//                    rColor = 0xFF;
//                    nextColor = WHITE;
//                    break;
//                }
//            }
//        }
//        
//        for (uint16_t x = 0; x < PANEL_COLUMNS; x++)
//        {
//            BW_Pixels[y][x] = bwColor;
//            R_Pixels[y][x] = rColor;
//        }
//    }
}


//Load the display
void EPAPER_3CLR_UpdateDisplay(void)
{
    /* For the 104x212 Display
     * 13 Bytes per Row
     * 212 Rows
     */
    
    /* Sequence to Write:
     * 1. DC = 0
     * 2. CS = 0
     * 3. Write 0x10
     * 4. CS = 1
     * 5. DC = 1
     * 6. CS = 0
     * 7. Pixel Byte (B/W)
     * 8. CS = 1
     * 9. Repeat 6-8 until complete
     * 10. DC = 0
     * 11. CS = 0
     * 12. Write 0x13
     * 13. CS = 1
     * 14. DC = 1
     * 15. CS = 0
     * 16. Pixel Byte (R)
     * 17. CS = 1
     * 18. Repeat 15-17 until complete
     */
    
    //B/W Phase
    
    EPAPER_SPI_AddressRegister(0x10);
    DC_SetHigh();

    uint16_t dispX, dispY;
    dispX = PixelManager_GetDisplayWidth() >> 3;
    dispY = PixelManager_GetDisplayHeight();
    
    for (uint16_t y = 0; y < dispY; y++)
    {
        for (uint16_t x = 0; x < dispX; x++)
        {
            DISP_CS_SetLow();
            SPI0_ByteExchange(PixelManager_GetBWByte(x, y));
            DISP_CS_SetHigh();
        }
    }
    
    //Red Phase
    
    EPAPER_SPI_AddressRegister(0x13);
    DC_SetHigh();

    for (uint16_t y = 0; y < dispY; y++)
    {
        for (uint16_t x = 0; x < dispX; x++)
        {
            DISP_CS_SetLow();
            SPI0_ByteExchange(PixelManager_GetRByte(x, y));
            DISP_CS_SetHigh();
        }
    }
    
    /* Refresh Command
     * 1. Wait for Busy = HIGH
     * 2. Power-On Command (0x04), no data
     * 3. Wait for Busy = HIGH
     * 4. Display Reset Command (0x12), no data
     * 5. Wait for Busy = HIGH
     */
    
    while (!BUSY_GetValue());
    EPAPER_SPI_AddressRegister(0x04);
    while (!BUSY_GetValue());
    EPAPER_SPI_AddressRegister(0x12);
    while (!BUSY_GetValue());
    
    /* Power Down DC-DC
     * 1. Shutdown DC-DC (0x02), no data
     * 2. Wait for BUSY = HIGH
     * 3. Tri-state RESET
     * 4. CS = 0, SDIN = 0, SCLK = 0
     * 5. Cutoff VCC/VDD
     * 6. Set BUSY to OUTPUT
     * 7. Set BUSY = 0
     * 8. Wait 150 ms
     * 9. Set RESET to OUTPUT
     * 10. Set BUSY to INPUT
     */
    
    EPAPER_SPI_AddressRegister(0x02);
    while (!BUSY_GetValue());
    
    //Cutoff power
    
//    DISP_RESET_SetDigitalInput();
//    DISP_CS_SetLow();
//    BUSY_SetDigitalOutput();
//    BUSY_SetLow();
    
    DELAY_milliseconds(150);
    
//    DISP_RESET_SetDigitalOutput();
//    BUSY_SetDigitalInput();
}


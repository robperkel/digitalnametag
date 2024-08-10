#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#include "ePaper_3CLR.h"
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/timer/delay.h"
#include "pixelManager.h"
#include "ePaper_SPI.h"

//Configure the display
void EPAPER_4CLR_Initialize(int8_t temp)
{
    /* POR Sequence:
     * 1. Power on VDD
     * 2. Wait 10ms
     * 3. RES = 1
     * 4. Wait 20ms
     * 5. RES = 0
     * 6. Wait 40ms
     * 7. RES = 1
     * 8. Wait 10ms
     * 9. Wait for Busy to be HIGH
     */
    
    DELAY_milliseconds(10);
    DISP_RESET_SetHigh();
    DELAY_milliseconds(20);
    DISP_RESET_SetLow();
    DELAY_milliseconds(40);
    DISP_RESET_SetHigh();
    DELAY_milliseconds(10);
    
    while (!BUSY_GetValue());
    
    /* COG Initialize
     * 1. Read Chip ID (0x70, id[0], id[2]) - Should be 0x03, 0x02
     * 2. SPI Send 0xA4, 0x15, 0x00, 0x01
     * 3. Wait for BUSY = HIGH
     * 4. Read OTP (0xA1, 1 dummy byte + 48 Bytes). Remove dummy byte from later math
     * 5. RES = 0
     * 6. Wait 40ms
     * 7. RES = 1
     * 8. Wait 10ms
     * 9. Wait for BUSY = HIGH
     * 10. Send PWR CMD (0x01, OTP[16])
     * 11. Send PSR CMD (0x00, OTP[17], OTP[18])
     * 12. Send PFS CMD (0x03, OTP[30], OTP[31], OTP[32])
     * 13. Send BTST CMD (0x06, OPT[23] -> OTP[29])
     * 14. Send CDI CMD (0x05, OTP[39])
     * 15. Send TCON CMD (0x60, OTP[40], OTP[41])
     * 16. Send TRES CMD (0x61, OTP[19] -> OTP[22])
     * 17. Send 0xE7, OTP[33]
     * 18. Send PWS CMD (0xE3, OTP[42])
     * 19. Send 0x4D, OTP[43]
     * 20. Send 0xB4, OTP[44]
     * 21. Send 0xB5, OTP[45]
     * 22. Send 0xE9, 0x01
     * 23. Send 0x30, 0x08
     */
    
    uint8_t data[49];
    uint8_t id[2];
    uint8_t buffer[7];
    
    //Read Chip ID
    EPAPER_SPI_ReadBytes(0x70, id, 2);
    
    //SPI Send 0xA4, 0x15, 0x00, 0x01
    buffer[0] = 0x15;
    buffer[1] = 0x00;
    buffer[2] = 0x01;
    EPAPER_SPI_WriteBytes(0xA4, buffer, 3);
    
    //Wait for BUSY
    while (!BUSY_GetValue());
    
    //Read OTP
    
}

//Update the display
void EPAPER_4CLR_UpdateDisplay(void)
{
    
}
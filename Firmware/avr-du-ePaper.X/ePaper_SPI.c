#include "ePaper.h"

#include <stdint.h>
#include <stdbool.h>

#include "mcc_generated_files/system/system.h"

//Reads LEN bytes from the ePaper
void EPAPER_SPI_ReadBytes(uint8_t reg, uint8_t* data, uint16_t len)
{
    //Reset Direction Control
    DISP_MOSI_EN_SetHigh();
    
    //Command Mode
    DC_SetLow();
    
    DISP_CS_SetLow();
    SPI0_ByteExchange(reg);
    DISP_CS_SetHigh();
    
    //Data Mode
    DC_SetHigh();
    
    //Disable MCU SDO
    DISP_MOSI_EN_SetLow();
    
    for (uint16_t i = 0; i < len; i++)
    {
        DISP_CS_SetLow();
        data[i] = SPI0_ByteExchange(0xFF);
        DISP_CS_SetHigh();
    }
    
    //Re-enable SDO
    DISP_MOSI_EN_SetHigh();
}

//Writes a register with data
void EPAPER_SPI_WriteByte(uint8_t reg, uint8_t data)
{
    /* Steps to set a register:
     * 1. DC = 0
     * 2. CS = 0
     * 3. Register ADDR
     * 4. CS = 1
     * 5. DC = 1
     * 6. CS = 0
     * 7. Send Byte
     * 8. CS = 1
     * 9. <Repeat 6-8 as needed>
     */
    
    //Ensure SDO is enabled
    DISP_MOSI_EN_SetHigh();
    
    //Command Mode
    DC_SetLow();
    
    DISP_CS_SetLow();
    SPI0_ByteExchange(reg);
    DISP_CS_SetHigh();
    
    //Data Mode
    DC_SetHigh();
    
    //Write Byte
    DISP_CS_SetLow();
    SPI0_ByteExchange(data);
    DISP_CS_SetHigh();
}

//Writes a register with data
void EPAPER_SPI_WriteBytes(uint8_t reg, uint8_t* data, uint16_t len)
{
    /* Steps to set a register:
     * 1. DC = 0
     * 2. CS = 0
     * 3. Register ADDR
     * 4. CS = 1
     * 5. DC = 1
     * 6. CS = 0
     * 7. Send Byte
     * 8. CS = 1
     * 9. <Repeat 6-8 as needed>
     */

    
    //Ensure SDO is enabled
    DISP_MOSI_EN_SetHigh();
    
    //Command Mode
    DC_SetLow();
    
    DISP_CS_SetLow();
    SPI0_ByteExchange(reg);
    DISP_CS_SetHigh();
    
    //Data Mode
    DC_SetHigh();
    
    for (uint16_t i = 0; i < len; i++)
    {
        //Write Byte
        DISP_CS_SetLow();
        SPI0_ByteExchange(data[i]);
        DISP_CS_SetHigh();
    }
}

//Select a register
void EPAPER_SPI_AddressRegister(uint8_t reg)
{
    /* Steps to set a register:
     * 1. DC = 0
     * 2. CS = 0
     * 3. Register ADDR
     * 4. CS = 1
     */
    
    //Ensure SDO is enabled
    DISP_MOSI_EN_SetHigh();
    
    //Command Mode
    DC_SetLow();
    
    //Write Byte
    DISP_CS_SetLow();
    SPI0_ByteExchange(reg);
    DISP_CS_SetHigh();
}
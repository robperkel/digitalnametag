#ifndef EPAPER_SPI_H
#define	EPAPER_SPI_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <stdint.h>
#include <stdbool.h>
    
    //Reads LEN bytes from the ePaper
    void EPAPER_SPI_ReadBytes(uint8_t reg, uint8_t* data, uint16_t len);
    
    //Writes a register with data
    void EPAPER_SPI_WriteByte(uint8_t reg, uint8_t data);
    
    //Writes a register with data
    void EPAPER_SPI_WriteBytes(uint8_t reg, uint8_t* data, uint16_t len);
    
    //Select a register
    void EPAPER_SPI_AddressRegister(uint8_t reg);

#ifdef	__cplusplus
}
#endif

#endif	/* EPAPER_SPI_H */


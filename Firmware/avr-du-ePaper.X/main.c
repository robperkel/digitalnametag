 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "ePaper_3CLR.h"
#include "mcc_generated_files/timer/delay.h"
#include "usb_cdc_virtual_serial_port.h"
#include "ringBuffer.h"
#include "pixelManager.h"
#include "Application.h"
#include "textQueue.h"

#include <stdint.h>
#include <stdbool.h>

#define TX_BUFFER_SIZE 32

int main(void)
{
    SYSTEM_Initialize();
    SPI0_Host_Open(HOST_CONFIG);

    TextQueue_Initialize();
    Application_Initialize();
    PixelManager_Initialize();
    
    USB_Stop();
    
    //Enumerate USB
    if (USB_Start() == SUCCESS)
    {
        LED_USB_SetHigh();
    }
        
    //Enable Interrupts
    sei();
        
    uint8_t data = 0x00;
        
    while(1)
    {
        USB_CDCVirtualSerialPortHandler();
        USBDevice_Handle();
        
        //Handle any input data
        while (USB_CDCRead(&data) == CDC_SUCCESS)
        {
            Application_AcceptData(data);
        }
        
        //Process data
        Application_HandleUSBInput();
        
        //Send Queued Text
        TextQueue_LoadUSB();
        
    }    
}
#include "textQueue.h"

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/usb/usb_device.h"
#include "mcc_generated_files/usb/usb_cdc/usb_cdc_virtual_serial_port.h"
#include "ringBuffer.h"

#include <stdint.h>
#include <stdbool.h>

static RingBuffer buffer;
static char txQueue[TX_QUEUE_SIZE];

//Initialize Text
void TextQueue_Initialize(void)
{
    ringBuffer_createBuffer(&buffer, txQueue, TX_QUEUE_SIZE);
}

//Load Text
void TextQueue_LoadText(const char* str)
{
    ringBuffer_loadString(&buffer, str);
}

//Load data into the USB report
void TextQueue_LoadUSB(void)
{
    //Nothing to send!
    if (ringBuffer_isEmpty(&buffer))
    {
        return;
    }
    
    char c;
    bool done = false;
    
    do
    {
        c = ringBuffer_peekChar(&buffer);
        if (USB_CDCWrite(c) == CDC_SUCCESS)
        {
            ringBuffer_incrementReadIndex(&buffer);
            if (ringBuffer_isEmpty(&buffer))
            {
                //No more text to transmit
                done = true;
            }
        }
        else
        {
            //Error!
            done = true;
        }
        
    } while (!done);
}
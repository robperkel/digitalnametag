#include "Application.h"
#include "ringBuffer.h"

#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/usb/usb0.h"
#include "mcc_generated_files/usb/usb_cdc/usb_cdc.h"
#include "mcc_generated_files/usb/usb_cdc/usb_cdc_virtual_serial_port.h"

#include "pixelManager.h"
#include "ePaper.h"
#include "textQueue.h"

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    COMMAND_STATE = 0, IMAGE_RENDER
} application_state_t;

typedef enum {
    TEXT_WAIT = 0, TEXT_COMMAND, TEXT_IMG
} text_state_t;

static application_state_t appState = COMMAND_STATE;
static text_state_t textState = TEXT_WAIT;

static char rxCharBuffer[RX_BUFFER_SIZE];
static RingBuffer rxBuffer;
static bool newData = false;

//Init the Application
void Application_Initialize(void)
{
    ringBuffer_createBuffer(&rxBuffer, rxCharBuffer, RX_BUFFER_SIZE);
}

//Add data to the queue
void Application_AcceptData(char c)
{
    //Make everything capitalized
    if ((c >= 'a') && (c <= 'z'))
    {
        c = 'A' + (c - 'a');
    }
    
    switch (textState)
    {
        case TEXT_WAIT:
        {
            if (c == ':')
            {
                textState = TEXT_COMMAND;
                newData = false;
            }
            else
            {
                if (c == 'R')
                {
                    PixelManager_LoadPixelStream(RED);
                }
                else if (c == 'W')
                {
                    PixelManager_LoadPixelStream(WHITE);
                }
                else if (c == 'B')
                {
                    PixelManager_LoadPixelStream(BLACK);
                }
                else if (c == 'Y')
                {
                    PixelManager_LoadPixelStream(YELLOW);
                }
                else if (c == '#')
                {
                    appState = IMAGE_RENDER;
                }
                else if (c == ' ')
                {
                    PixelManager_ResetSeqPixelPointers();
                }
            }
            break;
        }
        case TEXT_COMMAND:
        {
            if (c == '\n')
            {
                newData = true;
                textState = TEXT_WAIT;
            }
            else
            {
                ringBuffer_loadCharacter(&rxBuffer, c);
            }
            break;
        }
        case TEXT_IMG:
        {
            newData = true;
            ringBuffer_loadCharacter(&rxBuffer, c);
            break;
        }
    }
    
}

//Handle any USB input data
void Application_HandleUSBInput(void)
{        
    switch (appState)
    {
        case COMMAND_STATE:
        {
            if (!newData)
            {
                return;
            }
            
            if (ringBuffer_find(&rxBuffer, "ID"))
            {
                //Hello
                TextQueue_LoadText("OK\r\n");
            }
            if (ringBuffer_find(&rxBuffer, "MODE"))
            {
                //Color Mode
            }
            else if (ringBuffer_find(&rxBuffer, "SIZE"))
            {
                //Panel Size
            }
            
            //Clear buffer
            ringBuffer_flushReadBuffer(&rxBuffer);
            
            break;
        }
        case IMAGE_RENDER:
        {
            LED_DISP_SetHigh();
            USB_Stop();
            EPAPER_Initialize();

            EPAPER_UpdateDisplay();
            USB_Start();
            LED_DISP_SetLow();
            
            appState = COMMAND_STATE;

            break;
        }
    }
}
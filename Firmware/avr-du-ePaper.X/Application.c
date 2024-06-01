#include "Application.h"
#include "ringBuffer.h"

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    COMMAND_STATE = 0, IMAGE_LOAD_STATE
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
void Application_LoadData(char c)
{
    switch (textState)
    {
        case TEXT_WAIT:
        {
            if (c == ':')
            {
                textState = TEXT_COMMAND;
            }
            break;
        }
        case TEXT_COMMAND:
        {
            if (c == '\n')
            {
                newData = true;
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
    if (!newData)
    {
        return;
    }
    
    switch (appState)
    {
        case COMMAND_STATE:
        {
            break;
        }
        case IMAGE_LOAD_STATE:
        {
            
            break;
        }
    }
}
/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.1.0
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

#include "../pins.h"

static void (*MISO_InterruptHandler)(void);
static void (*MOSI_InterruptHandler)(void);
static void (*SCLK_InterruptHandler)(void);
static void (*BUSY_InterruptHandler)(void);
static void (*DC_InterruptHandler)(void);
static void (*DISP_RESET_InterruptHandler)(void);
static void (*DISP_CS_InterruptHandler)(void);
static void (*FLASH_CS_InterruptHandler)(void);
static void (*SIZE0_InterruptHandler)(void);
static void (*SIZE1_InterruptHandler)(void);
static void (*SIZE2_InterruptHandler)(void);
static void (*SIZE3_InterruptHandler)(void);
static void (*IO_PD3_InterruptHandler)(void);
static void (*CLR0_InterruptHandler)(void);
static void (*CLR1_InterruptHandler)(void);
static void (*CLR2_InterruptHandler)(void);
static void (*TEMP_IN_InterruptHandler)(void);
static void (*LED_USB_InterruptHandler)(void);
static void (*LED_MEM_InterruptHandler)(void);
static void (*LED_DISP_InterruptHandler)(void);
static void (*IO_PF3_InterruptHandler)(void);
static void (*DISP_MISO_EN_InterruptHandler)(void);
static void (*IO_PF5_InterruptHandler)(void);
static void (*SW0_InterruptHandler)(void);
static void (*IO_PF7_InterruptHandler)(void);

void PIN_MANAGER_Initialize()
{

  /* OUT Registers Initialization */
    PORTA.OUT = 0x88;
    PORTC.OUT = 0x0;
    PORTD.OUT = 0x0;
    PORTF.OUT = 0x10;

  /* DIR Registers Initialization */
    PORTA.DIR = 0xDB;
    PORTC.DIR = 0x8;
    PORTD.DIR = 0xFF;
    PORTF.DIR = 0xFF;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x0;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;
    PORTD.PIN0CTRL = 0x0;
    PORTD.PIN1CTRL = 0x0;
    PORTD.PIN2CTRL = 0x0;
    PORTD.PIN3CTRL = 0x0;
    PORTD.PIN4CTRL = 0x0;
    PORTD.PIN5CTRL = 0x0;
    PORTD.PIN6CTRL = 0x0;
    PORTD.PIN7CTRL = 0x0;
    PORTF.PIN0CTRL = 0x0;
    PORTF.PIN1CTRL = 0x0;
    PORTF.PIN2CTRL = 0x0;
    PORTF.PIN3CTRL = 0x0;
    PORTF.PIN4CTRL = 0x80;
    PORTF.PIN5CTRL = 0x0;
    PORTF.PIN6CTRL = 0x88;
    PORTF.PIN7CTRL = 0x0;

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.TWIROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    MISO_SetInterruptHandler(MISO_DefaultInterruptHandler);
    MOSI_SetInterruptHandler(MOSI_DefaultInterruptHandler);
    SCLK_SetInterruptHandler(SCLK_DefaultInterruptHandler);
    BUSY_SetInterruptHandler(BUSY_DefaultInterruptHandler);
    DC_SetInterruptHandler(DC_DefaultInterruptHandler);
    DISP_RESET_SetInterruptHandler(DISP_RESET_DefaultInterruptHandler);
    DISP_CS_SetInterruptHandler(DISP_CS_DefaultInterruptHandler);
    FLASH_CS_SetInterruptHandler(FLASH_CS_DefaultInterruptHandler);
    SIZE0_SetInterruptHandler(SIZE0_DefaultInterruptHandler);
    SIZE1_SetInterruptHandler(SIZE1_DefaultInterruptHandler);
    SIZE2_SetInterruptHandler(SIZE2_DefaultInterruptHandler);
    SIZE3_SetInterruptHandler(SIZE3_DefaultInterruptHandler);
    IO_PD3_SetInterruptHandler(IO_PD3_DefaultInterruptHandler);
    CLR0_SetInterruptHandler(CLR0_DefaultInterruptHandler);
    CLR1_SetInterruptHandler(CLR1_DefaultInterruptHandler);
    CLR2_SetInterruptHandler(CLR2_DefaultInterruptHandler);
    TEMP_IN_SetInterruptHandler(TEMP_IN_DefaultInterruptHandler);
    LED_USB_SetInterruptHandler(LED_USB_DefaultInterruptHandler);
    LED_MEM_SetInterruptHandler(LED_MEM_DefaultInterruptHandler);
    LED_DISP_SetInterruptHandler(LED_DISP_DefaultInterruptHandler);
    IO_PF3_SetInterruptHandler(IO_PF3_DefaultInterruptHandler);
    DISP_MISO_EN_SetInterruptHandler(DISP_MISO_EN_DefaultInterruptHandler);
    IO_PF5_SetInterruptHandler(IO_PF5_DefaultInterruptHandler);
    SW0_SetInterruptHandler(SW0_DefaultInterruptHandler);
    IO_PF7_SetInterruptHandler(IO_PF7_DefaultInterruptHandler);
}

/**
  Allows selecting an interrupt handler for MISO at application runtime
*/
void MISO_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    MISO_InterruptHandler = interruptHandler;
}

void MISO_DefaultInterruptHandler(void)
{
    // add your MISO interrupt custom code
    // or set custom function using MISO_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for MOSI at application runtime
*/
void MOSI_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    MOSI_InterruptHandler = interruptHandler;
}

void MOSI_DefaultInterruptHandler(void)
{
    // add your MOSI interrupt custom code
    // or set custom function using MOSI_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SCLK at application runtime
*/
void SCLK_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SCLK_InterruptHandler = interruptHandler;
}

void SCLK_DefaultInterruptHandler(void)
{
    // add your SCLK interrupt custom code
    // or set custom function using SCLK_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for BUSY at application runtime
*/
void BUSY_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    BUSY_InterruptHandler = interruptHandler;
}

void BUSY_DefaultInterruptHandler(void)
{
    // add your BUSY interrupt custom code
    // or set custom function using BUSY_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DC at application runtime
*/
void DC_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DC_InterruptHandler = interruptHandler;
}

void DC_DefaultInterruptHandler(void)
{
    // add your DC interrupt custom code
    // or set custom function using DC_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DISP_RESET at application runtime
*/
void DISP_RESET_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DISP_RESET_InterruptHandler = interruptHandler;
}

void DISP_RESET_DefaultInterruptHandler(void)
{
    // add your DISP_RESET interrupt custom code
    // or set custom function using DISP_RESET_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DISP_CS at application runtime
*/
void DISP_CS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DISP_CS_InterruptHandler = interruptHandler;
}

void DISP_CS_DefaultInterruptHandler(void)
{
    // add your DISP_CS interrupt custom code
    // or set custom function using DISP_CS_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for FLASH_CS at application runtime
*/
void FLASH_CS_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    FLASH_CS_InterruptHandler = interruptHandler;
}

void FLASH_CS_DefaultInterruptHandler(void)
{
    // add your FLASH_CS interrupt custom code
    // or set custom function using FLASH_CS_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SIZE0 at application runtime
*/
void SIZE0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SIZE0_InterruptHandler = interruptHandler;
}

void SIZE0_DefaultInterruptHandler(void)
{
    // add your SIZE0 interrupt custom code
    // or set custom function using SIZE0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SIZE1 at application runtime
*/
void SIZE1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SIZE1_InterruptHandler = interruptHandler;
}

void SIZE1_DefaultInterruptHandler(void)
{
    // add your SIZE1 interrupt custom code
    // or set custom function using SIZE1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SIZE2 at application runtime
*/
void SIZE2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SIZE2_InterruptHandler = interruptHandler;
}

void SIZE2_DefaultInterruptHandler(void)
{
    // add your SIZE2 interrupt custom code
    // or set custom function using SIZE2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SIZE3 at application runtime
*/
void SIZE3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SIZE3_InterruptHandler = interruptHandler;
}

void SIZE3_DefaultInterruptHandler(void)
{
    // add your SIZE3 interrupt custom code
    // or set custom function using SIZE3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PD3 at application runtime
*/
void IO_PD3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PD3_InterruptHandler = interruptHandler;
}

void IO_PD3_DefaultInterruptHandler(void)
{
    // add your IO_PD3 interrupt custom code
    // or set custom function using IO_PD3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for CLR0 at application runtime
*/
void CLR0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    CLR0_InterruptHandler = interruptHandler;
}

void CLR0_DefaultInterruptHandler(void)
{
    // add your CLR0 interrupt custom code
    // or set custom function using CLR0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for CLR1 at application runtime
*/
void CLR1_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    CLR1_InterruptHandler = interruptHandler;
}

void CLR1_DefaultInterruptHandler(void)
{
    // add your CLR1 interrupt custom code
    // or set custom function using CLR1_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for CLR2 at application runtime
*/
void CLR2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    CLR2_InterruptHandler = interruptHandler;
}

void CLR2_DefaultInterruptHandler(void)
{
    // add your CLR2 interrupt custom code
    // or set custom function using CLR2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for TEMP_IN at application runtime
*/
void TEMP_IN_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    TEMP_IN_InterruptHandler = interruptHandler;
}

void TEMP_IN_DefaultInterruptHandler(void)
{
    // add your TEMP_IN interrupt custom code
    // or set custom function using TEMP_IN_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for LED_USB at application runtime
*/
void LED_USB_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LED_USB_InterruptHandler = interruptHandler;
}

void LED_USB_DefaultInterruptHandler(void)
{
    // add your LED_USB interrupt custom code
    // or set custom function using LED_USB_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for LED_MEM at application runtime
*/
void LED_MEM_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LED_MEM_InterruptHandler = interruptHandler;
}

void LED_MEM_DefaultInterruptHandler(void)
{
    // add your LED_MEM interrupt custom code
    // or set custom function using LED_MEM_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for LED_DISP at application runtime
*/
void LED_DISP_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LED_DISP_InterruptHandler = interruptHandler;
}

void LED_DISP_DefaultInterruptHandler(void)
{
    // add your LED_DISP interrupt custom code
    // or set custom function using LED_DISP_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF3 at application runtime
*/
void IO_PF3_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF3_InterruptHandler = interruptHandler;
}

void IO_PF3_DefaultInterruptHandler(void)
{
    // add your IO_PF3 interrupt custom code
    // or set custom function using IO_PF3_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for DISP_MISO_EN at application runtime
*/
void DISP_MISO_EN_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    DISP_MISO_EN_InterruptHandler = interruptHandler;
}

void DISP_MISO_EN_DefaultInterruptHandler(void)
{
    // add your DISP_MISO_EN interrupt custom code
    // or set custom function using DISP_MISO_EN_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF5 at application runtime
*/
void IO_PF5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF5_InterruptHandler = interruptHandler;
}

void IO_PF5_DefaultInterruptHandler(void)
{
    // add your IO_PF5 interrupt custom code
    // or set custom function using IO_PF5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for SW0 at application runtime
*/
void SW0_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    SW0_InterruptHandler = interruptHandler;
}

void SW0_DefaultInterruptHandler(void)
{
    // add your SW0 interrupt custom code
    // or set custom function using SW0_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for IO_PF7 at application runtime
*/
void IO_PF7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    IO_PF7_InterruptHandler = interruptHandler;
}

void IO_PF7_DefaultInterruptHandler(void)
{
    // add your IO_PF7 interrupt custom code
    // or set custom function using IO_PF7_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTA.INTFLAGS & PORT_INT5_bm)
    {
       MISO_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT4_bm)
    {
       MOSI_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT6_bm)
    {
       SCLK_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT2_bm)
    {
       BUSY_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT0_bm)
    {
       DC_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT1_bm)
    {
       DISP_RESET_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT3_bm)
    {
       DISP_CS_InterruptHandler(); 
    }
    if(VPORTA.INTFLAGS & PORT_INT7_bm)
    {
       FLASH_CS_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT3_bm)
    {
       SIZE0_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

ISR(PORTD_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTD.INTFLAGS & PORT_INT0_bm)
    {
       SIZE1_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT1_bm)
    {
       SIZE2_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT2_bm)
    {
       SIZE3_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT3_bm)
    {
       IO_PD3_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT4_bm)
    {
       CLR0_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT5_bm)
    {
       CLR1_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT6_bm)
    {
       CLR2_InterruptHandler(); 
    }
    if(VPORTD.INTFLAGS & PORT_INT7_bm)
    {
       TEMP_IN_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTD.INTFLAGS = 0xff;
}

ISR(PORTF_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTF.INTFLAGS & PORT_INT0_bm)
    {
       LED_USB_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT1_bm)
    {
       LED_MEM_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT2_bm)
    {
       LED_DISP_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT3_bm)
    {
       IO_PF3_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT4_bm)
    {
       DISP_MISO_EN_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT5_bm)
    {
       IO_PF5_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT6_bm)
    {
       SW0_InterruptHandler(); 
    }
    if(VPORTF.INTFLAGS & PORT_INT7_bm)
    {
       IO_PF7_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTF.INTFLAGS = 0xff;
}

/**
 End of File
*/
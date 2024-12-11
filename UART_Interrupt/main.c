/*******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the Empty Application Example
*              for ModusToolbox.
*
* Related Document: See README.md
*
*
********************************************************************************
* Copyright 2021-2023, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Header Files
*******************************************************************************/
#include "cyhal.h"
#include "cybsp.h"

/*******************************************************************************
* Macros
*******************************************************************************/
/* Assign UART interrupt number and priority */
#define UART_INTR_NUM        ((IRQn_Type) scb_5_interrupt_IRQn)
#define UART_INTR_PRIORITY   (7U)
#define BUFFER_SIZE (64UL)
uint8_t buffer[BUFFER_SIZE];

/*******************************************************************************
* Global Variables
*******************************************************************************/
cy_stc_scb_uart_context_t  SCB5_Context;

cy_stc_sysint_t  UartintrConfig={
		.intrSrc 	=UART_INTR_NUM,
		.intrPriority = UART_INTR_PRIORITY

};

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/*******************************************************************************
* Function Definitions
*******************************************************************************/
void  SCB5_ISR(){
	Cy_SCB_UART_Interrupt(SCB5, &SCB5_Context);
}

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
* This is the main function for CPU. It...
*    1.
*    2.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;

#if defined (CY_DEVICE_SECURE)
    cyhal_wdt_t wdt_obj;

    /* Clear watchdog timer so that it doesn't trigger a reset */
    result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
    CY_ASSERT(CY_RSLT_SUCCESS == result);
    cyhal_wdt_free(&wdt_obj);
#endif

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    Cy_SCB_UART_Init(SCB5,&SCB5_config,&SCB5_Context);

//    /* Populate configuration structure */
//    const cy_stc_scb_uart_config_t SCB5_Config =
//    {
//        .uartMode                   = CY_SCB_UART_STANDARD,
//        .oversample                 = 12UL,
//        .enableMsbFirst             = false,
//        .dataWidth                  = 8UL,
//        .parity                     = CY_SCB_UART_PARITY_NONE,
//        .stopBits                   = CY_SCB_UART_STOP_BITS_1,
//    };
//
//    Cy_SCB_UART_Init(SCB5,&SCB5_Config,&SCB5_Context);
//
//    /* Assign pins for UART on SCB5: P5[0], P5[1] */
//    #define UART_PORT       P5_0_PORT
//    #define UART_RX_NUM     P5_0_NUM
//    #define UART_TX_NUM     P5_1_NUM
//    /* Connect SCB5 UART function to pins */
//    Cy_GPIO_SetHSIOM(UART_PORT, UART_RX_NUM, P5_0_SCB5_UART_RX);
//    Cy_GPIO_SetHSIOM(UART_PORT, UART_TX_NUM, P5_1_SCB5_UART_TX);
//    /* Configure pins for UART operation */
//    Cy_GPIO_SetDrivemode(UART_PORT, UART_RX_NUM, CY_GPIO_DM_HIGHZ); // Receiver pin is Input
//    Cy_GPIO_SetDrivemode(UART_PORT, UART_TX_NUM, CY_GPIO_DM_STRONG_IN_OFF);// Transmitter pin is Output

//    /* Assign divider type and number for UART */
//    #define UART_CLK_DIV_TYPE     (CY_SYSCLK_DIV_8_BIT)
//    #define UART_CLK_DIV_NUMBER   (0U)
//    /* Connect assigned divider to be a clock source for UART */
//    Cy_SysClk_PeriphAssignDivider(PCLK_SCB5_CLOCK, UART_CLK_DIV_TYPE, UART_CLK_DIV_NUMBER);
//
//    /* UART desired baud rate is 115200 bps (Standard mode).
//    * The UART baud rate = (clk_scb / Oversample).
//    * For clk_peri = 50 MHz, select divider value 36 and get SCB clock = (50 MHz / 36) = 1,389 MHz.
//    * Select Oversample = 12. These setting results UART data rate = 1,389 MHz / 12 = 115750 bps.
//    */
//    Cy_SysClk_PeriphSetDivider   (UART_CLK_DIV_TYPE, UART_CLK_DIV_NUMBER, 35UL);
//    Cy_SysClk_PeriphEnableDivider(UART_CLK_DIV_TYPE, UART_CLK_DIV_NUMBER);

    (void) Cy_SysInt_Init(&UartintrConfig ,SCB5_ISR);
    NVIC_EnableIRQ(UART_INTR_NUM);

    /* Enable UART to operate */
    Cy_SCB_UART_Enable(SCB5);

    Cy_SCB_UART_Put(SCB5,'s');
    Cy_SCB_UART_Put(SCB5,'i');
    Cy_SCB_UART_Put(SCB5,'d');
    Cy_SCB_UART_Put(SCB5,'r');
    Cy_SCB_UART_Put(SCB5,'a');
    Cy_SCB_UART_Put(SCB5,'m');

    buffer[1]='a';
    buffer[2]='b';
    buffer[3]='c';
    buffer[4]='d';

    /* Transmit data */
    (void) Cy_SCB_UART_Transmit(SCB5, buffer, BUFFER_SIZE, &SCB5_Context);

    for (;;)
    {

    }
}



/* [] END OF FILE */

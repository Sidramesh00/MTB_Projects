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


/*******************************************************************************
* Global Variables
*******************************************************************************/


/*******************************************************************************
* Function Prototypes
*******************************************************************************/
void GPIO_ISR();

/*******************************************************************************
* Function Definitions
*******************************************************************************/


/*******************************************************************************
* Function Name: GPIO_ISR
********************************************************************************
*
* Summary:
*  This function is executed when GPIO interrupt is triggered.
*
*******************************************************************************/
void GPIO_ISR()
{
    /* Clears the triggered pin interrupt */
	Cy_GPIO_ClearInterrupt(CYBSP_USER_BTN_PORT,CYBSP_USER_BTN_NUM);
    // Toggle the LED
    Cy_GPIO_Inv(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN);
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


    // Initialize GPIO for LED (Output)
    Cy_GPIO_Pin_FastInit(CYBSP_USER_LED_PORT, CYBSP_USER_LED_PIN, CY_GPIO_DM_STRONG, 0, HSIOM_SEL_GPIO);

    // Initialize GPIO for Button (Input with pull-up)
 //   Cy_GPIO_Pin_FastInit(CYBSP_USER_BTN_PORT, CYBSP_USER_BTN_NUM, CY_GPIO_DM_PULLUP, 1, HSIOM_SEL_GPIO);

       // Configure the interrupt
       cy_stc_sysint_t gpio_irq_cfg = {
           .intrSrc = CYBSP_USER_BTN_IRQ,
           .intrPriority = 3
       };

       Cy_SysInt_Init(&gpio_irq_cfg, GPIO_ISR); // Initialize interrupt
       NVIC_EnableIRQ(CYBSP_USER_BTN_IRQ);                  // Enable interrupt in NVIC

       // Enable interrupt on falling edge for the button
//       	 Cy_GPIO_SetInterruptEdge(CYBSP_USER_BTN_PORT, CYBSP_USER_BTN_NUM, CY_GPIO_INTR_FALLING);
       Cy_GPIO_SetInterruptMask(CYBSP_USER_BTN_PORT, CYBSP_USER_BTN_NUM, 1);
    for (;;)
    {

    }
}

/* [] END OF FILE */

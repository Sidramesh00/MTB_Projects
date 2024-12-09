# PSoC™ 4: GPIO interrupt

This code example demonstrates the use of a GPIO configured as an input pin to generate interrupts on PSoC™ 4.

## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm&reg; Embedded Compiler v11.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; Compiler v6.16 (`ARM`)
- IAR C/C++ Compiler v9.30.1 (`IAR`)



## Design and implementation
	1. GPIO Pin Initialization
		○ The LED is initialized as an output with Cy_GPIO_Pin_FastInit using strong drive mode (CY_GPIO_DM_STRONG).
		○ The button is initialized as an input with pull-up (CY_GPIO_DM_PULLUP).
	2. Interrupt Configuration
		○ The interrupt is configured for the button pin using Cy_SysInt_Init.
		○ The GPIO_ISR function is registered and enabled using NVIC_EnableIRQ.
		○ Falling-edge detection is correctly set with Cy_GPIO_SetInterruptEdge.
	3. ISR Implementation
		○ The ISR clears the interrupt source with Cy_GPIO_ClearInterrupt.
		○ It toggles the LED using Cy_GPIO_Inv.
	4. Watchdog Timer Handling
		○ The watchdog is correctly disabled in a secure device configuration.
	5. Global Interrupts
Global interrupts are enabled with __enable_irq().

An input pin, externally connected to a switch, is configured to generate an interrupt when the switch is pressed. The interrupt triggers and Executes an ISR.
### Resources and settings

**Table 1. Application resources**
   
Resource	   |   Alias/object	   |   Purpose
 :-------- | :-------------    | :------------
LED (BSP)	|   CYBSP_USER_LED1  |	User LED to show the output
Switch (BSP)|	CYBSP_USER_BTN	User| switch to generate the interrupt


<br />


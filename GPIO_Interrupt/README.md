# PSoC™ 6: GPIO interrupt

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

### The code works as follows

### Button Interrupt Mechanism
**1. Setup and Initialization:**

○ The button (input) is configured in Device Configurator. The button is configured as an input with a pull-up resistor, ensuring it has a default state (logic HIGH) when not pressed.

○ The LED is configured as a strong output, enabling it to drive a load like an LED.

**2. Interrupt Configuration:**

○  An interrupt structure (cy_stc_sysint_t) specifies the interrupt source (button pin) and priority (3 in this case).

○  The interrupt is registered with Cy_SysInt_Init, associating the interrupt with the ISR (GPIO_ISR).

○  The NVIC (Nested Vectored Interrupt Controller) is enabled to handle the interrupt using NVIC_EnableIRQ.

**3. Button Press Triggers Interrupt:**

○  When the button is pressed, the pull-up resistor is overridden, and the pin transitions from HIGH to LOW (falling edge).

○  This state change triggers the GPIO interrupt.

**4. ISR Execution:**

○  The interrupt service routine GPIO_ISR is invoked.

○  Within the ISR:

	○  The interrupt flag for the button is cleared using Cy_GPIO_ClearInterrupt to avoid repeated interrupts from the same event.

	○  The LED toggles its state using Cy_GPIO_Inv, either turning ON (if OFF) or OFF (if ON).

**5. Main Loop:**

The for (;;) infinite loop in main() ensures the microcontroller remains active, continuously waiting for events like button presses.

### Working Flow:
**1. Idle State:**

The button is unpressed, and the system is idle, waiting for an interrupt.

**2. Interrupt Event:**

Button press generates an interrupt. The interrupt controller (NVIC) directs execution to the ISR.

**3. ISR Processing:**

The ISR clears the interrupt and toggles the LED state.

**4. Return to Idle:**

After the ISR finishes, the CPU returns to the main loop.

### Key Concepts:
**1. Interrupts Save Power:**

Instead of constantly polling the button, the microcontroller responds to events (button press) only when they occur.

**2. Non-Blocking Code:**

The infinite loop doesn’t interfere with ISR functionality, allowing the CPU to perform other tasks or remain idle.

By configuring the button and its interrupt in the Device Configurator, the process of associating the interrupt with the button pin and setting up hardware parameters is automated. The runtime behavior remains unchanged, but setup complexity is reduced.

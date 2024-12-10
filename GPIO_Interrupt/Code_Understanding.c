# **Understanding of GPIO  interrupt configuration structure**
/******************************************************************************
 * GPIO  interrupt configuration structure
 *****************************************************************************/
       const cy_stc_sysint_t gpio_irq_cfg = {
           .intrSrc = CYBSP_USER_BTN_IRQ,
           .intrPriority = 3
       };

* Initialization configuration structure for a single interrupt channel
*/
typedef struct {
#if defined (CY_IP_M7CPUSS)
    uint32_t        intrSrc;        /**< Bit 0-15 indicate system interrupt and bit 16-31 will indicate the CPU IRQ */
#else
    IRQn_Type       intrSrc;        /**< Interrupt source */
#endif
#if (CY_CPU_CORTEX_M0P) && defined (CY_IP_M4CPUSS)
    cy_en_intr_t    cm0pSrc;        /**< Maps cm0pSrc device interrupt to intrSrc */
#endif /* CY_CPU_CORTEX_M0P */
    uint32_t        intrPriority;   /**< Interrupt priority number (Refer to __NVIC_PRIO_BITS) */
} cy_stc_sysint_t;

##My understanding code

#include <stdio.h>
typedef struct x{
    int a;
    char b;
}variables_t;

variables_t config={
     .a=1,
     .b='c'};
int main()
{
    printf("%d %c",config.a,config.b);
    return 0;
}
Output= 1 c
  if I give
const variables_t config={
     .a=1,
     .b='c'};
then config variable will be treated as constant, meaning it can't be modified.

Code present in cy8c62axxx.h
/*******************************************************************************
*                         Interrupt Number Definition
*******************************************************************************/

typedef enum {
  /* ARM Cortex-M4 Core Interrupt Numbers */
  Reset_IRQn                        = -15,      /*!< -15 Reset Vector, invoked on Power up and warm reset */
  NonMaskableInt_IRQn               = -14,      /*!< -14 Non maskable Interrupt, cannot be stopped or preempted */
  HardFault_IRQn                    = -13,      /*!< -13 Hard Fault, all classes of Fault */
  MemoryManagement_IRQn             = -12,      /*!< -12 Memory Management, MPU mismatch, including Access Violation and No Match */
  BusFault_IRQn                     = -11,      /*!< -11 Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory related Fault */
  UsageFault_IRQn                   = -10,      /*!< -10 Usage Fault, i.e. Undef Instruction, Illegal State Transition */
  SVCall_IRQn                       =  -5,      /*!<  -5 System Service Call via SVC instruction */
  DebugMonitor_IRQn                 =  -4,      /*!<  -4 Debug Monitor */
  PendSV_IRQn                       =  -2,      /*!<  -2 Pendable request for system service */
  SysTick_IRQn                      =  -1,      /*!<  -1 System Tick Timer */
  /* CY8C624ABZI-S2D44 Peripheral Interrupt Numbers */
  ioss_interrupts_gpio_0_IRQn       =   0,      /*!<   0 [DeepSleep] GPIO Port Interrupt #0 */ (IRQ used in this project)
  ioss_interrupts_gpio_1_IRQn       =   1,      /*!<   1 [DeepSleep] GPIO Port Interrupt #1 */
       .
       .
       .
       .
  sdhc_1_interrupt_general_IRQn     = 167,      /*!< 167 [Active] Consolidated interrupt for mxsdhc for everything else */
  unconnected_IRQn                  =1023       /*!< 1023 Unconnected */
#endif
} IRQn_Type;


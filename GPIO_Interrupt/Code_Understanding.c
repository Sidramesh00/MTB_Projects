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

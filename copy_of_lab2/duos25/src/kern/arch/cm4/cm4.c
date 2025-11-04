// /*
//  * Copyright (c) 2022
//  * Computer Science and Engineering, University of Dhaka
//  * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted provided that the following conditions
//  * are met:
//  * 1. Redistributions of source code must retain the above copyright
//  *    notice, this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright
//  *    notice, this list of conditions and the following disclaimer in the
//  *    documentation and/or other materials provided with the distribution.
//  * 3. Neither the name of the University nor the names of its contributors
//  *    may be used to endorse or promote products derived from this software
//  *    without specific prior written permission.
//  *
//  * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
//  * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
//  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
//  * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
//  * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
//  * SUCH DAMAGE.
//  */

// #include <cm4.h>
// #include <sys_clock.h>
// #include <syscall.h>

// /************************************************************************************
//  * __SysTick_init(uint32_t reload)
//  * Function initialize the SysTick clock. The function with a weak attribute enables
//  * redefining the function to change its characteristics whenever necessary.
//  **************************************************************************************/

// /*
// initializes the ARM Cortex-M processor's SysTick timer to a desired rate,
// typically for generating periodic interrupts.
// */

// static volatile uint32_t __mscount = 0;
// volatile static uint32_t _systick_count = 0;
// volatile static uint32_t _ms_tick = 0;

// void __SysTick_init(uint32_t reload)
// {
//     /*
//     1.
//     Stop the Timer during initialization
//     to prevent unwanted interrupts from occurring
//     while configuring the other registers.
//     */
//     SYSTICK->CTRL &= ~(1 << 0);
//     /*
//     2.
//     Set the Reload Value, period of the timer
//     */
//     SYSTICK->LOAD = (reload - 1) & 0x00FFFFFF;
//     /*
//     3.
//     Clear the Counter:
//     Write to the SysTick CURRENT (or VAL) register
//     to clear the counter and reset it to its initial state
//     */
//     SYSTICK->VAL = 0;

//     /*
//     4.
//     Configure the Control Register:
//     Set the Clock Source.
//     Enable the Interrupt.
//     Enable the Timer
//     */
//     SYSTICK->CTRL |= (1 << 2) | // CLKSOURCE: Use processor clock (AHB)
//                      (1 << 1) | // TICKINT: Enable interrupt
//                      (1 << 0);  // ENABLE: Enable the counter
// }
// void SysTickIntDisable(void) // interrupt disable
// {
//     // if(!(SYSTICK->CTRL & ~(1<<1))){
//     SYSTICK->CTRL &= ~(1 << 1); // Clear the TICKINT bit
//     //}
// }

// void SysTickIntEnable(void)
// {
//     // if((SYSTICK->CTRL & ~(1<<1))){
//     SYSTICK->CTRL |= (1 << 1); // Clear the TICKINT bit
//     //}
// }
// /************************************************************************************
//  * __sysTick_enable(void)
//  * The function enables the SysTick clock if already not enabled.
//  * redefining the function to change its characteristics whenever necessary.
//  **************************************************************************************/
// void __SysTick_enable(void)
// {
//     // if((SYSTICK->CTRL & ~(1<<0))){
//     SYSTICK->CTRL |= (1 << 0); // Clear the TICKINT bit
//     //}
// }
// void __sysTick_disable(void)
// {
//     // if(!(SYSTICK->CTRL & ~(1<<0))){
//     SYSTICK->CTRL &= ~(1 << 0); // Clear the TICKINT bit
//     //}
// }
// uint32_t __getSysTickCount(void)
// {
//     return _systick_count;
// }
// /************************************************************************************
//  * __updateSysTick(uint32_t count)
//  * Function reinitialize the SysTick clock. The function with a weak attribute enables
//  * redefining the function to change its characteristics whenever necessary.
//  **************************************************************************************/

// void __updateSysTick(uint32_t count)
// {
//     __sysTick_disable();
//     __SysTick_init(count);
//     __SysTick_enable();
// }

// /************************************************************************************
//  * __getTime(void)
//  * Function return the SysTick elapsed time from the begining or reinitialing. The function with a weak attribute enables
//  * redefining the function to change its characteristics whenever necessary.
//  **************************************************************************************/

// // uint32_t __getTime(void)
// // {
// //     return _systick_count;
// //    //  return (uint32_t)(_systick_count * SYSTICK->LOAD) + (SYSTICK->LOAD - SYSTICK->VAL);
// // }

// uint32_t __getTime(void)
// {
//     // Total cycles since boot
//     uint32_t cycles = (_systick_count * SYSTICK->LOAD) + (SYSTICK->LOAD - SYSTICK->VAL);
//     // Convert cycles to milliseconds
//     uint32_t ms = cycles / SYSTICK->LOAD;
//     return ms;
// }

// uint32_t __get__Second(void)
// {
//     return _systick_count / 1000;
// }
// uint32_t __get__Minute(void)
// {
//     return __get__Second() / 60;
// }
// uint32_t __get__Hour(void)
// {
//     return __get__Minute() / 60;
// }
// void SysTick_Handler(void)
// {
//     _systick_count++;
// }

// void __enable_fpu()
// {
//     SCB->CPACR |= ((0xFUL << 20));
// }

// uint8_t ms_delay(uint32_t delay)
// {
//     uint32_t start_tick = _systick_count;
//     while ((_systick_count - start_tick) < delay)
//         ;
//     return 0; 
// }

// uint32_t getmsTick(void)
// {
//     return _systick_count;
// }

// uint32_t wait_until(uint32_t delay)
// {
//     // Returns the current tick count after a delay.
//     // This is useful for scheduling events.
//     return _systick_count + delay;
//     /*cg
//      uint32_t target = __mscount + delay;
//     while (__mscount < target)
//         ;
//     return 1;
//     */
// }

// void SYS_SLEEP_WFI(void)
// {
//     __WFI();
// }



/*
 * Copyright (c) 2022
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE UNIVERSITY OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <cm4.h>
#include <sys_clock.h>
#include <syscall.h>
#include <kstdio.h>

/************************************************************************************
 * __SysTick_init(uint32_t reload)
 * Function initialize the SysTick clock. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

/*
initializes the ARM Cortex-M processor's SysTick timer to a desired rate,
typically for generating periodic interrupts.
*/

static volatile uint32_t __mscount = 0;
volatile static uint32_t _systick_count = 0;
volatile static uint32_t _ms_tick = 0;

void __SysTick_init(uint32_t reload)
{
    /*
    1.
    Stop the Timer during initialization
    to prevent unwanted interrupts from occurring
    while configuring the other registers.
    */
    SYSTICK->CTRL &= ~(1 << 0);
    /*
    2.
    Set the Reload Value, period of the timer
    */
    SYSTICK->LOAD = (reload - 1) & 0x00FFFFFF;
    //SYSTICK->LOAD = ;

    /*
    3.
    Clear the Counter:
    Write to the SysTick CURRENT (or VAL) register
    to clear the counter and reset it to its initial state
    */
    SYSTICK->VAL = 0;

    /*
    4.
    Configure the Control Register:
    Set the Clock Source.
    Enable the Interrupt.
    Enable the Timer
    */
    SYSTICK->CTRL |= (1 << 2) | // CLKSOURCE: Use processor clock (AHB)
                     (1 << 1) | // TICKINT: Enable interrupt
                     (1 << 0);  // ENABLE: Enable the counter
}
void SysTickIntDisable(void) // interrupt disable
{
    // if(!(SYSTICK->CTRL & ~(1<<1))){
    SYSTICK->CTRL &= ~(1 << 1); // Clear the TICKINT bit
    //}
}

void SysTickIntEnable(void)
{
    // if((SYSTICK->CTRL & ~(1<<1))){
    SYSTICK->CTRL |= (1 << 1); // Clear the TICKINT bit
    //}
}
/************************************************************************************
 * __sysTick_enable(void)
 * The function enables the SysTick clock if already not enabled.
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/
void __SysTick_enable(void)
{
    // if((SYSTICK->CTRL & ~(1<<0))){
    SYSTICK->CTRL |= (1 << 0); // Clear the TICKINT bit
    //}
}
void __sysTick_disable(void)
{
    // if(!(SYSTICK->CTRL & ~(1<<0))){
    SYSTICK->CTRL &= ~(1 << 0); // Clear the TICKINT bit
    //}
}
uint32_t __getSysTickCount(void)
{
    return _systick_count;
}
/************************************************************************************
 * __updateSysTick(uint32_t count)
 * Function reinitialize the SysTick clock. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

void __updateSysTick(uint32_t count)
{
    __sysTick_disable();
    __SysTick_init(count);
    __SysTick_enable();
}

/************************************************************************************
 * __getTime(void)
 * Function return the SysTick elapsed time from the begining or reinitialing. The function with a weak attribute enables
 * redefining the function to change its characteristics whenever necessary.
 **************************************************************************************/

uint32_t __getTime(void)
{
    //return (_systick_count+(SYSTICK->LOAD-SYSTICK->VAL)/(PLL_N*1000));

     return _systick_count;
    // return (uint32_t)(_systick_count * SYSTICK->LOAD) + (SYSTICK->LOAD - SYSTICK->VAL);
}

uint32_t __get__Second(void)
{
    return _systick_count / 1000;
}
uint32_t __get__Minute(void)
{
    return __get__Second() / 60;
}
uint32_t __get__Hour(void)
{
    return __get__Minute() / 60;
}
void SysTick_Handler(void)
{
    _systick_count++;
   //_systick_count+=(SYSTICK->LOAD)/(PLL_N*1000);
}

void __enable_fpu()
{
    SCB->CPACR |= ((0xFUL << 20));
}

uint8_t ms_delay(uint32_t delay)
{
    uint32_t start_tick = _systick_count;
    while ((_systick_count - start_tick) < delay){
        // __WFI();
    }
        
    return 0; // The return type suggests a status, 0 for success.
}

uint32_t getmsTick(void)
{
    return _systick_count;
}

uint32_t wait_until(uint32_t delay)
{
    // Returns the current tick count after a delay.
    // This is useful for scheduling events.
    return _systick_count + delay;
    /*cg
     uint32_t target = __mscount + delay;
    while (__mscount < target)
        ;
    return 1;
    */
}

void SYS_SLEEP_WFI(void)
{
    __WFI();
}

// extern void syscall(uint16_t callno);

// void __attribute__((naked)) SVCall_Handler(void)
// {
//     __asm volatile(
//         "tst lr, #4\n"        // Test bit 2 of EXC_RETURN
//         "ite eq\n"            // If-Then-Else block
//         "mrseq r0, msp\n"     // If bit 2 is 0, use MSP
//         "mrsne r0, psp\n"     // If bit 2 is 1, use PSP
//         "mov r1,r0\n"      // Move stack pointer to r1
//         "b SVC_Handler_C\n"   // Branch to C handler
//     );
// }


// void __attribute__((naked)) SVC_Handler(void)
// {
//    kprintf("Inside SVC_Handler assembly\n");

//     __asm volatile(
//         "tst lr, #4\n"        
//         "ite eq\n"            
//         "mrseq r7, msp\n"     
//         "mrsne r7, psp\n"     
//         "ldr r8, [r7, #24]\n" // Get PC from stack
//         "ldrb r9, [r8, #-2]\n" // Get SVC number from instruction
//         "push {lr}\n"         // Save lr
//         "bl SVC_Handler_C\n"  
//         "pop {lr}\n"          // Restore lr
//         "bx lr\n"             // Return
//     );
// }

// void SVC_Handler_C(uint32_t *svc_args)
// {
//     // kprintf("inside SVC_Handler_C\n");
//     uint8_t svc_number2 = ((uint8_t *)svc_args[6])[-2];  // Get SVC number
//     uint32_t svc_number = svc_args[0]; 
//     kprintf("SVC_Handler_C: svc_number=%d, r0=%d, r1=%d, r2=%d\n", 
//             svc_number, svc_args[0], svc_args[1], svc_args[2]);
//     // syscall(svc_number);  // Call syscall handler
//     kprintf("svc2: %d\n", svc_number2);
//     syscall((uint16_t)svc_number,svc_args);
     
// }


// svc_args = Stacked registers on exception entry:
//   [0]=r0, [1]=r1, [2]=r2, [3]=r3, [4]=r12, [5]=lr, [6]=pc, [7]=xpsr
// void SVC_Handler_C(unsigned int *svc_args)
// {
//     // Copy stacked regs if you want to inspect them (optional)
//     uint32_t stacked_r0  = svc_args[0];
//     uint32_t stacked_r1  = svc_args[1];
//     uint32_t stacked_r2  = svc_args[2];
//     uint32_t stacked_r3  = svc_args[3];
//     uint32_t stacked_r12 = svc_args[4];  // NOTE: this is r12, not "stack pointer"
//     uint32_t stacked_lr  = svc_args[5];
//     uint32_t stacked_pc  = svc_args[6];
//     uint32_t stacked_xpsr= svc_args[7];

//     // Decode SVC immediate from the instruction that triggered the exception:
//     // pc points to next instruction; SVC immediate is at (pc - 2)
//     uint8_t svc_number = ((uint8_t*)stacked_pc)[-2];

//     // Dispatch. Pass both the call number and the stacked regs.
//     // This function must return the value to go back in r0 (svc_args[0]).
//     // extern uint32_t syscall_dispatch(uint8_t callno, uint32_t *svc_args);

     
//     // Place the return value into stacked r0 so thread mode 
//     // receives it in r0.

//     __asm volatile("PUSH {LR}");
//     // svc_args[0] = ret;

//     syscall((uint16_t)svc_number);


//     __asm volatile("POP {LR}");
// }



// void __attribute__((naked)) SVCall_Handler(void)
// {
//     __asm volatile(
//         "tst lr, #4\n"              // Test bit 2 of EXC_RETURN (which stack was used?)
//         "ite eq\n"                  // If-Then-Else block
//         "mrseq r0, msp\n"           // If bit 2 is 0, use Main Stack Pointer
//         "mrsne r0, psp\n"           // If bit 2 is 1, use Process Stack Pointer
//         "b SVC_Handler_C\n"         // Branch to C handler with stack pointer in r0
//         ::: "r0"
//     );
// }


// void SVC_Handler_C(uint32_t *svc_args)
// {
//     // Extract the SVC number from r3 on the stack
//    // uint16_t svc_number = (uint32_t)svc_args[0];
//     uint8_t svc_number = ((uint8_t *)svc_args[6])[-2];
    
//     kprintf("SVC_Handler_C: svc_number=%d, r0=%d, r1=%d, r2=%d\n", 
//             svc_number, svc_args[0], svc_args[1], svc_args[2]);
    
//     // Call the syscall dispatcher
//     // It will modify svc_args[0] (r0) to set the return value
//     syscall(svc_number, svc_args);
    
//     kprintf("SVC_Handler_C: returning, r0=%d\n", svc_args[0]);
// }

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

// #include <stdint.h>
// #include <syscall_def.h>
// #include "kunistd.h"

// #include <sys_init.h>
// #include <sys/types.h>
// #include <cm4.h>
// #include <kmain.h>
// #include <stdint.h>
// #include <sys_usart.h>
// #include <kstdio.h>
// #include <sys_rtc.h>
// #include <kstring.h>
// #include<unistd.h>

// #ifndef DEBUG
// #define DEBUG 1
// #endif


// extern void main(void);



// void kmain(void)
// {
//     __sys_init();
//     // uint32_t last_ms = 0;
//     // uint32_t timeee = __get__Second();
//     // kprintf("Time passed total: %d seconds\n", timeee);

//    //  main();

//     // while (1)
//     // {   

//     //     // ms_delay(1000);
//     //     // main();
//     //     // ms_delay(1000);
        
//     //    uint32_t now_ms = __getTime();   // returns current time in ms

        

//     //     uint32_t seconds = __get__Second();
//     //     kprintf("Time passed total: %d seconds\n", seconds);
//     //     ms_delay(1000);
       
//     // }


//     // kprintf("User: SVC time test running\n");
    
//     //     uint32_t t = getSysTickTime();
//     //     kprintf("time = %u ms\n", t);
//         // ms_delay(1000);
//         // t = getSysTickTime();
//         // kprintf("time = %u ms\n", t);
// }



// #include <stdint.h>
// #include <syscall_def.h>
// #include "kunistd.h"
// #include <sys_init.h>
// #include <sys/types.h>
// #include <cm4.h>
// #include <kmain.h>
// #include <stdint.h>
// #include <sys_usart.h>
// #include <kstdio.h>
// #include <sys_rtc.h>
// #include <kstring.h>

// extern void main(void);

// void kmain(void)
// {
//     // Initialize system (clocks, USART, SysTick, etc.)
//     __sys_init();
    
//     kprintf("\n");
//     kprintf("======================================\n");
//     kprintf("  Kernel Initialized Successfully\n");
//     kprintf("  SVC-based Syscall System Active\n");
//     kprintf("======================================\n");
//     kprintf("\n");
    
//     // Get initial time from kernel space
//     uint32_t init_time = __get__Second();
//     kprintf("Kernel: Initial time = %d seconds\n\n", init_time);
    
//     // Call user application (which will run in unprivileged mode if configured)
//     kprintf("Kernel: Starting user application...\n\n");
//     main();
    
//     // If main returns (it shouldn't in this case), just loop
//     kprintf("Kernel: User application returned (unexpected)\n");
//     while (1) {
//         ms_delay(1000);
//     }
// }

#include <stdint.h>
#include <syscall_def.h>
#include "kunistd.h"
#include <sys_init.h>
#include <sys/types.h>
#include <cm4.h>
#include <kmain.h>
#include <stdint.h>
#include <sys_usart.h>
#include <kstdio.h>
#include <sys_rtc.h>
#include <kstring.h>

extern void main(void);

void kmain(void)
{
    // Initialize system (clocks, USART, SysTick, etc.)
    __sys_init();
    // ms_delay(5000);
    
    

    // kprintf_mod("%d, ms\n", __getTime());

    kprintf("  Kernel Initialized Successfully\n");
    kprintf("  SVC-based Syscall System\n");
 
    // Check processor mode (privileged or unprivileged)
    uint32_t control_reg;
    __asm volatile ("MRS %0, CONTROL" : "=r" (control_reg));
 
    if (control_reg & 0x01) {
         kprintf("Mode: Unprivileged\n");
    } else {
        // kprintf("Mode: Privileged\n");
 
        // Switch to unprivileged mode
         kprintf("Switching to Unprivileged mode...\n");
        control_reg |= 0x01;  
        __asm volatile ("MSR CONTROL, %0" : : "r" (control_reg));
        __asm volatile ("ISB");  // Instruction Synchronization Barrier
 
        // Verify the mode change
        __asm volatile ("MRS %0, CONTROL" : "=r" (control_reg));
        if (control_reg & 0x01) {
             kprintf("Mode changed to: Unprivileged\n");
        } else {
             kprintf("Mode is still: Privileged\n");
        }

    }
 
        
     kprintf("Kernel: Starting user application...\n\n");

     main();
    
    
}
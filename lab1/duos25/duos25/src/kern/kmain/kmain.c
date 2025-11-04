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

#include <stdint.h>
#include <syscall_def.h>
#include "kunistd.h"


#include <sys/types.h>
#include <cm4.h>
#include <kmain.h>
#include <stdint.h>
#include <sys_usart.h>
#include <kstdio.h>
#include <sys_rtc.h>
#include <kstring.h>
#ifndef DEBUG
#define DEBUG 1
#endif



// void kmain(void)
// {
//     __sys_init();
//     while (1)
//     {
      
//     }
// }

//extern int main(void);  // user entry

// extern int32_t user_read(int fd, void *buf, uint32_t n); // your user wrapper names
// extern int32_t user_write(int fd, const void *buf, uint32_t n);
// extern uint32_t user_getSysTickTime(void);

// void run_as_unprivileged_demo(void) {
//     // Switch to unprivileged Thread mode (CONTROL.nPRIV=1)
//     __set_CONTROL(__get_CONTROL() | 1U);
//     __ISB();

//     const char *msg = "Hello from unprivileged via SVC\n";
//     (void)user_write(STDOUT_FILENO, msg, 31);

//     uint32_t ms = __getSysTickCount();

//     // If you need to go back to privileged:
//     // Only an exception can raise privilege; e.g., trigger PendSV and in the handler
//     // restore a privileged context (or reset CONTROL in a privileged handler).
// }


//void kmain(void)
//{
    //__sys_init();
    //uint32_t last_ms = 0;
    // uint32_t timeee = __get__Second();
    // kprintf("Time passed total: %d seconds\n", timeee);
    // while (1)
    // {
        
    // //    uint32_t now_ms = __getTime();   // returns current time in ms
    // // if (now_ms - last_ms >= 10)      // 30 ms elapsed
    // //{
    //     //last_ms = now_ms;

    //     uint32_t seconds = __get__Second();
    //     kprintf("Time passed total: %d seconds\n", seconds);
    //     ms_delay(1000);
    //     //kprintf("lastms variable %d\n", last_ms++);
    // //}
    // }

    
    // kmain usually never returns
    //for(;;) { /* idle */ }
//}


// void kmain(void) {
//     __sys_init();
//     run_as_unprivileged_demo();
    
// }


/*
 * DUOS kmain.c — minimal kernel bootstrap + user-mode trampoline
 * Runs kernel init, then enters unprivileged Thread mode (PSP) and calls user main().
 * This allows SVC-based syscalls (read/write/getpid/time/exit/yield) to trap into the kernel.
 */

// #include <stdint.h>

// /* ------------------ Optional kernel I/O (provided by kstdio.c) ------------------ */
// //extern int kprintf(const char *fmt, ...);   /* If missing in your tree, change/disable the prints */
// extern void kputs(const char *s);

// /* ------------------ Board/driver initialization (from sys_init.c, etc.) -------- */
// extern void sys_init(void);                 /* Your platform init: clock, GPIO, USART, SysTick, etc. */
// /* If your tree uses different init symbols, declare and call them instead. */

// /* ------------------ User entry provided by userland ----------------------------- */
// extern int main(void);                      /* userland/user/main.c */

// /* ------------------ Tiny intrinsics (no CMSIS required) ------------------------ */
// /* If CMSIS or other headers defined these as macros, undef them so we can
//    provide inline function implementations instead (avoids "expected an identifier"). */
// #ifdef __ISB
// # undef __ISB
// #endif
// #ifdef __DSB
// # undef __DSB
// #endif
// #ifdef __enable_irq
// # undef __enable_irq
// #endif
// #ifdef __disable_irq
// # undef __disable_irq
// #endif
// #ifdef __get_CONTROL
// # undef __get_CONTROL
// #endif
// #ifdef __set_CONTROL
// # undef __set_CONTROL
// #endif
// #ifdef __set_PSP
// # undef __set_PSP
// #endif

// static inline void __ISB(void)                           { __asm volatile("isb" ::: "memory"); }
// static inline void __DSB(void)                           { __asm volatile("dsb" ::: "memory"); }
// static inline void __enable_irq(void)                    { __asm volatile("cpsie i" ::: "memory"); }
// static inline void __disable_irq(void)                   { __asm volatile("cpsid i" ::: "memory"); }
// static inline uint32_t __get_CONTROL(void)               { uint32_t v; __asm volatile("mrs %0, control":"=r"(v)); return v; }
// static inline void __set_CONTROL(uint32_t v)             { __asm volatile("msr control, %0" :: "r"(v) : "memory"); __ISB(); }
// static inline void __set_PSP(uint32_t v)                 { __asm volatile("msr psp, %0" :: "r"(v) : "memory"); }

// /* ------------------ User stack for unprivileged Thread mode -------------------- */
// /* 4 KB user stack (adjust as needed). Must be 8-byte aligned for AAPCS. */
// #define USER_STACK_WORDS   (1024u)
// static uint32_t user_stack[USER_STACK_WORDS] __attribute__((aligned(8)));

// /* ------------------ Trampoline: enter user mode and call user main() ----------- */
// static void start_user(void)
// {
//     /* Use Process Stack Pointer for user code */
//     __set_PSP((uint32_t)(&user_stack[USER_STACK_WORDS]));

//     /* CONTROL bits:
//        bit0 (nPRIV)=1 -> unprivileged Thread mode
//        bit1 (SPSEL)=1 -> use PSP in Thread mode
//        bit2 (FPCA)=0  -> no FP context (enable if you use FPU in userland)
//     */
//     uint32_t ctl = __get_CONTROL();
//     ctl |= (1u << 0);   /* nPRIV = 1 (drop privilege) */
//     ctl |= (1u << 1);   /* SPSEL = 1 (use PSP) */
//     __set_CONTROL(ctl);

//     /* Barrier for safety before jumping into user code */
//     __DSB(); __ISB();

//     /* We are now in unprivileged Thread mode on PSP. Run user program. */
//     (void)main();

//     /* If user main() ever returns (it shouldn't — user exit() should terminate),
//        just park the CPU here. You can replace with a kernel yield or WFI. */
//     for (;;)
//         __asm volatile ("wfi");
// }

// /* ------------------ Kernel entry point ----------------------------------------- */
// void kmain(void)
// {
//     /* Bring up clocks, GPIO, USART, SysTick, etc. */
//    sys_init();

//     /* Optional: say hello from kernel so you can distinguish kernel vs user prints */
//     if (kputs) kputs("[KERNEL] DUOS boot ok. Handing off to user...\r\n");

//     /* Enable interrupts globally (SysTick, PendSV, USART RX, etc.) */
//     __enable_irq();

//     /* Enter user space and start the first (and only) user task: user/main.c::main() */
//     start_user();

//     /* If start_user() ever returns, idle the kernel. In a scheduler this would be idle task. */
//     for (;;)
//         __asm volatile ("wfi");
// }


#include <stdint.h>
#include<stdio.h>

extern void __sys_init(void) __attribute__((weak));


//    provide inline function implementations instead (avoids "expected an identifier"). */
#ifdef __ISB
# undef __ISB
#endif
#ifdef __DSB
# undef __DSB
#endif
#ifdef __enable_irq
# undef __enable_irq
#endif
#ifdef __disable_irq
# undef __disable_irq
#endif
#ifdef __get_CONTROL
# undef __get_CONTROL
#endif
#ifdef __set_CONTROL
# undef __set_CONTROL
#endif
#ifdef __set_PSP
# undef __set_PSP
#endif

/* ---- Minimal intrinsics, no CMSIS ---- */
static inline void __ISB(void)                           { __asm volatile("isb" ::: "memory"); }
static inline void __DSB(void)                           { __asm volatile("dsb" ::: "memory"); }
static inline void __enable_irq(void)                    { __asm volatile("cpsie i" ::: "memory"); }
static inline void __disable_irq(void)                   { __asm volatile("cpsid i" ::: "memory"); }
static inline uint32_t __get_CONTROL(void)               { uint32_t v; __asm volatile("mrs %0, control":"=r"(v)); return v; }
static inline void __set_CONTROL(uint32_t v)             { __asm volatile("msr control, %0" :: "r"(v) : "memory"); __ISB(); }
static inline void __set_PSP(uint32_t v)                 { __asm volatile("msr psp, %0" :: "r"(v) : "memory"); }

/* ---- External kernel stuff ---- */
extern void sys_init(void);          /* may be from asm or C */
// extern int  kprintf(const char*, ...); /* if missing, comment out the call below */

/* ---- User entry ---- */
extern int main(void);

/* ---- If a callee lacks Thumb metadata, call with LSB=1 ---- */
typedef void (*fn0_t)(void);
#define THUMB_CALL(fn_sym) ((fn0_t)((uintptr_t)(fn_sym) | 1u))()

/* ---- User stack ---- */
#define USER_STACK_WORDS 1024u
static uint32_t user_stack[USER_STACK_WORDS] __attribute__((aligned(8)));

#define USER_STACK_WORDS 1024u
static uint32_t user_stack[USER_STACK_WORDS] __attribute__((aligned(8)));

static void start_user(void){
    __set_PSP((uint32_t)&user_stack[USER_STACK_WORDS]);
    uint32_t ctl = __get_CONTROL();
    ctl |= (1u<<0);  /* nPRIV=1 */
    ctl |= (1u<<1);  /* SPSEL=1 (PSP) */
    __set_CONTROL(ctl);
    __DSB(); __ISB();
    (void)main();
    for(;;) __asm volatile("wfi");
}

void kmain(void){
    if (__sys_init) { __sys_init(); }                 // ✅ use the real symbol name
    extern void kprintf(char*, ...) __attribute__((weak));
    if (kprintf)  { kprintf("[KERNEL] DUOS boot ok. Handoff to user...\r\n"); }
    __enable_irq();
    start_user();
    for(;;) __asm volatile("wfi");
}

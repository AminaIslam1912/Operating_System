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
 
#include <unistd.h>
#include <stdint.h>
#include <syscall_def.h>
#include <stddef.h>
#include <cm4.h>
#include <kstdio.h>
#include <syscall.h>

// static inline int32_t svc_call3(uint16_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
// {
//     register uint32_t r0 __asm__("r0") = (uint32_t)svc_id;
//     register uint32_t r1 __asm__("r1") = a0;
//     register uint32_t r2 __asm__("r2") = a1;
//     register uint32_t r3 __asm__("r3") = a2;
//     __asm volatile ("svc 0" : "+r"(r0) : "r"(r1), "r"(r2), "r"(r3) : "memory");

//      kprintf("inside svc_call3, r0=%d\n", r0);
//      return (int32_t)r0;
// }


// static inline __attribute__((always_inline))
// int32_t svc_call3(uint16_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
// {
//     register uint32_t r0 __asm__("r0") = (uint32_t)svc_id;
//     register uint32_t r1 __asm__("r1") = a0;
//     register uint32_t r2 __asm__("r2") = a1;
//     register uint32_t r3 __asm__("r3") = a2;

//     __asm volatile (
//         "svc 0"
//         : "+r"(r0)                    // r0: in = svc_id, out = return value
//         : "r"(r1), "r"(r2), "r"(r3)   // r1–r3: args
//         : "r12", "lr", "memory", "cc" // conservative clobbers
//     );

//     // DO NOT call anything here using r0-bound variable.
//     // If you want to log, copy first:
//     // uint32_t ret = r0;
//     // kprintf("svc ret=%lu\n", (unsigned long)ret);
//     // return (int32_t)ret;

//     return (int32_t)r0;
// }

// static inline __attribute__((always_inline))
// int32_t svc_call3(uint16_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
// {
//     register uint32_t r0 __asm__("r0") = svc_id;
//     register uint32_t r1 __asm__("r1") = a0;
//     register uint32_t r2 __asm__("r2") = a1;
//     register uint32_t r3 __asm__("r3") = a2;

//     kprintf("before svc, svc_id=%d, a0=%d, a1=%d, a2=%d\n", svc_id, a0, a1, a2);

//     __asm volatile (
//         "svc #0\n"
//         : "+r"(r0)              // r0 is input (svc_id) and output (return value)
//         : "r"(r1), "r"(r2), "r"(r3)  // r1-r3 are inputs (arguments)
//         : "memory"
//     );

//     kprintf("after svc, return value=%d\n", r0);

//     return (int32_t)r0;
// }


// static inline __attribute__((always_inline))
// int32_t svc_call3(uint16_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
// {
//     register uint32_t r0 __asm__("r0") = a0;
//     register uint32_t r1 __asm__("r1") = a1;
//     register uint32_t r2 __asm__("r2") = a2;
//     register uint32_t r3 __asm__("r3") = svc_id;  // Pass svc_id in r3

//     kprintf("before svc, svc_id=%d, a0=%d, a1=%d, a2=%d\n", svc_id, a0, a1, a2);

//     __asm volatile (
//         "svc #0\n"
//         : "+r"(r0)                      // r0 is input (a0) and output (return value)
//         : "r"(r1), "r"(r2), "r"(r3)    // r1=a1, r2=a2, r3=svc_id
//         : "memory"
//     );

//     kprintf("after svc, return value=%d\n", r0);

//     return (int32_t)r0;
// }


// ssize_t  read (int fd, void *buf, size_t n);
// ssize_t  write(int fd, const void *buf, size_t n);

// ssize_t read(ssize_t fd, void *buf, size_t n)
// { return (ssize_t)svc_call3(SYS_read,  (uint32_t)fd, (uint32_t)buf, (uint32_t)n); }

// ssize_t write(ssize_t fd, const void *buf, size_t n)
// { return (ssize_t)svc_call3(SYS_write, (uint32_t)fd, (uint32_t)buf, (uint32_t)n); }

// uint32_t getSysTickTime(void)
//  { 
// // return(uint32_t)svc_call3(SYS___time, 0u, 0u, 0u);

//  uint32_t time_ms = 0;

//     __asm volatile (
//         "mov r1, %0  \n"   // Put &time_ms into register R1
//         "svc #113    \n"   // Trigger system call #113
//         :
//         : "r"(&time_ms)
//         : "r1", "memory", "cc"
//     );

//     kprintf("getSysTickTime: time_ms=%d\n", time_ms);

//     return (int)time_ms;   // Kernel wrote the time here
    
// }

// int getpid(void)
// { return (int)svc_call3(SYS_getpid, 0u, 0u, 0u); }

// void yield(void)
// { (void)svc_call3(SYS_yield, 0u, 0u, 0u); }

// void exitt(void)
// { (void)svc_call3(SYS__exit, 0u, 0u, 0u); for(;;){} }

// int reboot(void)
// { return (int)svc_call3(SYS_reboot, 0u, 0u, 0u); }

// #include <unistd.h>
// #include <stdint.h>
// #include <syscall_def.h>
// #include <stddef.h>
// #include<types.h>

// /**
//  * @brief Generic SVC call wrapper with 3 arguments
//  * @param svc_id: System call number
//  * @param a0: First argument
//  * @param a1: Second argument  
//  * @param a2: Third argument
//  * @return Result from kernel handler in r0
//  */
// static inline __attribute__((always_inline))
// int32_t svc_call(uint8_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
// {
//     register uint32_t r0 __asm__("r0") = a0;
//     register uint32_t r1 __asm__("r1") = a1;
//     register uint32_t r2 __asm__("r2") = a2;

//     // Encode the SVC number in the instruction itself
//     __asm volatile ("svc %[id]" 
//         : "+r"(r0)                    // r0 is both input and output (return value)
//         : [id]"I"(svc_id),           // SVC number as immediate value
//           "r"(r1), "r"(r2)           // r1, r2 are inputs
//         : "r3", "r12", "lr", "memory", "cc"
//     );

//     return (int32_t)r0;
// }

// /**
//  * @brief Read from file descriptor
//  */
// // ssize_t read(int fd, void *buf, size_t n)
// // {
// //     return (ssize_t)svc_call(SYS_read, (uint32_t)fd, (uint32_t)buf, (uint32_t)n);
// // }

// // /**
// //  * @brief Write to file descriptor
// //  */
// // ssize_t write(int fd, const void *buf, size_t n)
// // {
// //     return (ssize_t)svc_call(SYS_write, (uint32_t)fd, (uint32_t)buf, (uint32_t)n);
// // }

// ssize_t write(int fd, const void *buf, size_t n);


// ssize_t read(int fd, void *buf, size_t n)
// {
//     return (ssize_t)svc_call(SYS_read,
//                               (uint32_t)fd,
//                               (uint32_t)buf,
//                               (uint32_t)n);
// }

// ssize_t write(int fd, const void *buf, size_t n)
// {
//     return (ssize_t)svc_call(SYS_write,
//                               (uint32_t)fd,
//                               (uint32_t)buf,
//                               (uint32_t)n);
// }


// /**
//  * @brief Get current SysTick time in milliseconds
//  * @return Current time in milliseconds since system start
//  */



// uint32_t getSysTickTime(void)
// {
//     return (uint32_t)svc_call(SYS___time, 0u, 0u, 0u);
// }

// /**
//  * @brief Get current process ID
//  */
// int getpid(void)
// {
//     return (int)svc_call(SYS_getpid, 0u, 0u, 0u);
// }

// /**
//  * @brief Yield CPU to other processes
//  */
// void yield(void)
// {
//     (void)svc_call(SYS_yield, 0u, 0u, 0u);
// }

// /**
//  * @brief Exit current process
//  */
// void exitt(void)
// {
//     (void)svc_call(SYS__exit, 0u, 0u, 0u);
//     for(;;){} // Never returns
// }

// /**
//  * @brief Reboot system
//  */
// int reboot(void)
// {
//     return (int)svc_call(SYS_reboot, 0u, 0u, 0u);
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
 
#include <unistd.h>
#include <stdint.h>
#include <syscall_def.h>
#include <stddef.h>
#include<kstdio.h>

/**
 * APPROACH: Pass syscall number in r0 (first argument position)
 * and shift other arguments. The handler will extract the syscall
 * number from stacked r0 and actual arguments from r1, r2, r3.
 * 
 * This avoids using r7 which may be reserved as frame pointer.
 */

/**
 * @brief Generic SVC call wrapper - syscall number in first position
 * @param svc_id: System call number (will be in r0 on stack)
 * @param a0: First argument (will be in r1 on stack)
 * @param a1: Second argument (will be in r2 on stack)
 * @param a2: Third argument (will be in r3 on stack)
 * @return Result from kernel handler in r0
 */
static inline __attribute__((always_inline))
int32_t svc_call(uint16_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
{
    register uint32_t r0 __asm__("r0") = svc_id;
    register uint32_t r1 __asm__("r1") = a0;
    register uint32_t r2 __asm__("r2") = a1;
    register uint32_t r3 __asm__("r3") = a2;

    __asm volatile (
        "svc #0"
        : "+r"(r0)                           // r0 is both input (syscall#) and output (return)
        : "r"(r1), "r"(r2), "r"(r3)         // r1-r3 are inputs (arguments)
        : "r12", "lr", "memory", "cc"
    );

    return (int32_t)r0;
}

/**
 * @brief Read from file descriptor
 */

 ssize_t read(int fd, void *buf, size_t n);
ssize_t read(int fd, void *buf, size_t n)
{
    return (ssize_t)svc_call(SYS_read, (uint32_t)fd, (uint32_t)buf, (uint32_t)n);
}

/**
 * @brief Write to file descriptor
 */
ssize_t write(int fd, const void *buf, size_t n);

ssize_t write(int fd, const void *buf, size_t n)
{
    return (ssize_t)svc_call(SYS_write, (uint32_t)fd, (uint32_t)buf, (uint32_t)n);
}

/**
 * @brief Get current SysTick time in milliseconds
 * @return Current time in milliseconds since system start
 */
uint32_t getSysTickTime(void)
{
    return (uint32_t)svc_call(SYS___time, 0u, 0u, 0u);
}

/**
 * @brief Get current process ID
 */
int getpid(void)
{
    return (int)svc_call(SYS_getpid, 0u, 0u, 0u);
}

/**
 * @brief Yield CPU to other processes
 */
void yield(void)
{
    (void)svc_call(SYS_yield, 0u, 0u, 0u);
}

/**
 * @brief Exit current process
 */
void exitt(void)
{
    (void)svc_call(SYS__exit, 0u, 0u, 0u);
    for(;;){} // Never returns
}

/**
 * @brief Reboot system
 */
int reboot(void)
{
    return (int)svc_call(SYS_reboot, 0u, 0u, 0u);
}
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
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY AND CONTRIBUTORS `AS IS'' AND
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
#include <kunistd.h>
#include <stddef.h>   /* provides size_t */
#include <stdint.h>
/* Add your functions here */

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

#include <kunistd.h>
#include <stddef.h>
#include <stdint.h>
#include <cm4.h>
#include <kstdio.h>
#include <errno.h>
#include <sys/types.h>
#include <system_config.h>
#include <stdio.h>

// External functions from cm4.c
extern uint32_t __getTime(void);
extern uint32_t __getSysTickCount(void);

/**
 * @brief Kernel implementation of getSysTickTime
 * Returns the current elapsed time of systick in milliseconds
 * @return Current time in milliseconds since system start
 */
uint32_t k_getSysTickTime(void)
{
    // Get the current systick count (incremented every millisecond)
    // This is safe to call from privileged mode (kernel)
    uint32_t time_ms = __getTime();
    
    return time_ms;
}

/**
 * @brief Kernel implementation of read
 * @param fd: File descriptor
 * @param buf: Buffer to read into
 * @param n: Number of bytes to read
 * @return Number of bytes read, or negative error code
 * 
 * 
 */


 
ssize_t k_read(int fd, void *buf, size_t n)
{
    // TODO: Implement actual file/device reading
    // For now, return not implemented
    return -ENOSYS;
}

/**
 * @brief Kernel implementation of write
 * @param fd: File descriptor
 * @param buf: Buffer to write from
 * @param n: Number of bytes to write
 * @return Number of bytes written, or negative error code
 */

 
ssize_t k_write(int fd, const void *buf, size_t n)
{
    // Check for valid buffer pointer
    if (buf == NULL) {
        return -EINVAL;
    }
    
    //For STDOUT (fd=1) and STDERR (fd=2), write to debug console
    if (fd == 1 || fd == 2) {
        const char *str = (const char *)buf;
        for (size_t i = 0; i < n; i++) {
            putchar(str[i]);
        }
        return (ssize_t)n;
    }

   
    
    // For other file descriptors, not implemented yet
    return -ENOSYS;
}

/**
 * @brief Kernel implementation of getpid
 * @return Current process ID (for now, always returns 1)
 */
int k_getpid(void)
{
    // TODO: Implement actual process management
    // For now, return a dummy PID
    return 1;
}

/**
 * @brief Kernel implementation of yield
 * Yields the CPU to other processes
 */
void k_yield(void)
{
    // TODO: Implement actual process scheduler
    // For now, this is a no-op
}

/**
 * @brief Kernel implementation of exit
 * Terminates the current process
 */
void k_exit(void)
{
    // TODO: Implement actual process termination
    // For now, just halt
    kprintf("Process exit called\n");
    while(1) {
        __WFI();  // Wait for interrupt (low power mode)
    }
}

/**
 * @brief Kernel implementation of reboot
 * @return 0 on success, negative error code on failure
 */
int k_reboot(void)
{
    // Perform software reset using ARM Cortex-M AIRCR register
    kprintf("System rebooting...\n");
    ms_delay(100);  // Give time for message to transmit
    
    // Request system reset
    SCB->AIRCR = (0x5FA << 16) |      // VECTKEY
                 (SCB->AIRCR & 0x700) | // Keep priority group
                 (1 << 2);             // SYSRESETREQ
    
    // Should never reach here
    while(1);
    
    return 0;
}
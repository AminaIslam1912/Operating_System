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
 
// #ifndef __USER_UNISTD_H
// #define __USER_UNISTD_H

// #include <stdint.h>
// #include <stddef.h>
// #include <syscall_def.h>   // SYS_read, SYS_write, SYS___time, ...

// /* minimal userland types */
// #ifndef __SSIZE_T_DEFINED
// #define __SSIZE_T_DEFINED
// typedef int32_t ssize_t;
// #endif

// /* standard FDs (match kernel) */
// #ifndef STDIN_FILENO
// #define STDIN_FILENO   0
// #endif
// #ifndef STDOUT_FILENO
// #define STDOUT_FILENO  1
// #endif
// #ifndef STDERR_FILENO
// #define STDERR_FILENO  2
// #endif

// /* user-space syscall wrappers (SVC-backed) */
// ssize_t  read (ssize_t fd, void *buf, size_t n);
// ssize_t  write(ssize_t fd, const void *buf, size_t n);
// uint32_t getSysTickTime(void);
// int      getpid(void);
// void     yield(void);
// void     exitt(void);
// int      reboot(void);

// #endif /* __USER_UNISTD_H */

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

#ifndef __UNISTD_H
#define __UNISTD_H

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

/**
 * @brief Standard file descriptors
 */
#define STDIN_FILENO  0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

/**
 * @brief User-space system call wrappers
 * These functions trigger SVC instructions to enter kernel mode
 */

/**
 * @brief Read from file descriptor
 * @param fd: File descriptor
 * @param buf: Buffer to read into
 * @param n: Number of bytes to read
 * @return Number of bytes read, or negative error code
 */
// ssize_t read(int fd, void *buf, size_t n);

/**
 * @brief Write to file descriptor
 * @param fd: File descriptor
 * @param buf: Buffer to write from
 * @param n: Number of bytes to write
 * @return Number of bytes written, or negative error code
 */
// ssize_t write(int fd, const void *buf, size_t n);

/**
 * @brief Get current SysTick time in milliseconds
 * @return Current time in milliseconds since system start
 */
uint32_t getSysTickTime(void);

/**
 * @brief Get current process ID
 * @return Current process ID
 */
int getpid(void);

/**
 * @brief Yield CPU to other processes
 */
void yield(void);

/**
 * @brief Exit current process
 * This function never returns
 */
void exitt(void);

/**
 * @brief Reboot the system
 * @return 0 on success, negative error code on failure
 */
int reboot(void);

#endif /* __UNISTD_H */

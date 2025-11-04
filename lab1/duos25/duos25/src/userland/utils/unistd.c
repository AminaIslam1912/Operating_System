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

static inline int32_t svc_call3(uint16_t svc_id, uint32_t a0, uint32_t a1, uint32_t a2)
{
    register uint32_t r0 __asm__("r0") = (uint32_t)svc_id;
    register uint32_t r1 __asm__("r1") = a0;
    register uint32_t r2 __asm__("r2") = a1;
    register uint32_t r3 __asm__("r3") = a2;
    __asm volatile ("svc 0" : "+r"(r0) : "r"(r1), "r"(r2), "r"(r3) : "memory");
    return (int32_t)r0;
}

ssize_t read(int fd, void *buf, size_t n)
{ return (ssize_t)svc_call3(SYS_read,  (uint32_t)fd, (uint32_t)buf, (uint32_t)n); }

ssize_t write(int fd, const void *buf, size_t n)
{ return (ssize_t)svc_call3(SYS_write, (uint32_t)fd, (uint32_t)buf, (uint32_t)n); }

uint32_t getSysTickTime(void)
{ return (uint32_t)svc_call3(SYS___time, 0u, 0u, 0u); }

int getpid(void)
{ return (int)svc_call3(SYS_getpid, 0u, 0u, 0u); }

void yield(void)
{ (void)svc_call3(SYS_yield, 0u, 0u, 0u); }

void exit(void)
{ (void)svc_call3(SYS__exit, 0u, 0u, 0u); for(;;){} }

int reboot(void)
{ return (int)svc_call3(SYS_reboot, 0u, 0u, 0u); }

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
// */

// #include <syscall.h>
// #include <syscall_def.h>
// #include <errno.h>
// #include <errmsg.h>
// void syscall(uint16_t callno)
// {
// /* The SVC_Handler calls this function to evaluate and execute the actual function */
// /* Take care of return value or code */
// 	switch(callno)
// 	{
// 		/* Write your code to call actual function (kunistd.h/c or times.h/c and handle the return value(s) */
// 		case SYS_read: 
// 			break;
// 		case SYS_write:
// 			break;
// 		case SYS_reboot:
// 			break;	
// 		case SYS__exit:
// 			break;
// 		case SYS_getpid:
// 			break;
// 		case SYS___time:
// 			break;
// 		case SYS_yield:
// 			break;				
// 		/* return error code see error.h and errmsg.h ENOSYS sys_errlist[ENOSYS]*/	
// 		default: ;
// 	}
// /* Handle SVC return here */
// }



/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * See original license header in your tree.
 */


 //ager
// #include <stdint.h>
// #include <stddef.h>
// #include <syscall.h>
// #include <syscall_def.h>
// // #include <errno.h>
// #include <errmsg.h>

// /*
//  * -------- Calling convention between SVC handler and syscall() --------
//  * The SVC handler must set these BEFORE calling syscall(callno):
//  *   svc_args[0] = service ID (same as 'callno'; kept to match user-level ABI)
//  *   svc_args[1] = arg0 (e.g., fd)
//  *   svc_args[2] = arg1 (e.g., buf)
//  *   svc_args[3] = arg2 (e.g., size)
//  * And syscall() must store the integer return value into svc_retval.
//  *
//  * You can define these in your SVC handler .c file; we reference them here.
//  */
// extern uint32_t svc_args[4];
// extern int32_t  svc_retval;

// /*
//  * -------- Kernel-private service entry points ----------
//  * These are the *actual* privileged implementations your kernel provides.
//  * Provide them in kunistd.c/times.c/platform.c (names are illustrative).
//  */
// typedef int32_t  pid_t;
// typedef int32_t  ssize_t;

// /* I/O (character terminal via USART when fd == STDIN_FILENO / STDOUT_FILENO) */
// extern ssize_t k_read(int fd, void *buf, size_t size);          /* must honor '\n' termination and 256B cap */
// extern ssize_t k_write(int fd, const void *buf, size_t size);

// /* Time (SysTick in milliseconds) */
// extern uint64_t k_time_ms(void);                                /* returns elapsed ms as 64-bit */

// /* Process/task management & scheduling */
// extern void     k_exit(void);                                   /* marks TCB terminated, then schedules next */
// extern void     k_yield(void);                                  /* triggers PendSV to schedule next ready task */
// extern pid_t    k_getpid(void);                                 /* returns current task ID (from TCB) */

// /* Platform control */
// extern void     k_reboot(void);                                 /* performs a safe system reboot */

// /* Optional: file-descriptor constants if not already visible here */
// #ifndef STDIN_FILENO
// #define STDIN_FILENO   0
// #endif
// #ifndef STDOUT_FILENO
// #define STDOUT_FILENO  1
// #endif

// /* Local helpers to read args safely from svc_args[] */
// static inline uint16_t arg_service_id(void)         { return (uint16_t)svc_args[0]; }
// static inline int32_t  arg0_i32(void)               { return (int32_t) svc_args[1]; }
// static inline void    *arg1_ptr(void)               { return (void*)   (uintptr_t)svc_args[2]; }
// static inline uint32_t arg2_u32(void)               { return (uint32_t)svc_args[3]; }

// /* Clamp read size to 256 bytes per spec */
// static inline size_t clamp_read_size(size_t n)      { return (n > 256u) ? 256u : n; }

// /* Common error exit: set retval to -1 and (optionally) errno via sys_errlist[] */
// static inline void sys_ret_err(int err)
// {
//     /* If you maintain a per-thread errno, set it there; falling back to a global errno is fine too. */
//     // errno = err;                   /* <errno.h> */
//     svc_retval = -err;
// }

// /* ------------------------ Main dispatcher ------------------------ */
// void syscall(uint16_t callno)
// {
//     /* Defensive: ensure service ID in r0 matches the callno the handler passed. */
//     (void)callno; /* We can ignore if you trust the handler; or assert equivalence if desired. */
//     /* Example sanity check (uncomment if you want strictness):
//      * if (arg_service_id() != callno) { sys_ret_err(EINVAL); return; }
//      */

//     switch (arg_service_id())
//     {
//         case SYS_read:
//         {
//             int      fd   = arg0_i32();
//             void    *buf  = arg1_ptr();
//             size_t   sz   = clamp_read_size((size_t)arg2_u32());

//             if (buf == NULL) { sys_ret_err(EINVAL); break; }

//             /* k_read must implement: stop on '\n' and never exceed 256 bytes. */
//             ssize_t nread = k_read(fd, buf, sz);
//             if (nread < 0) { sys_ret_err(-nread); }  /* if your k_read returns -errno */
//             else           { svc_retval = (int32_t)nread; }
//             break;
//         }

//         case SYS_write:
//         {
//             int           fd  = arg0_i32();
//             const void   *buf = (const void*)arg1_ptr();
//             size_t        sz  = (size_t)arg2_u32();

//             if (buf == NULL && sz != 0) { sys_ret_err(EINVAL); break; }

//             ssize_t nw = k_write(fd, buf, sz);
//             if (nw < 0) { sys_ret_err(-nw); }
//             else        { svc_retval = (int32_t)nw; }
//             break;
//         }

//         case SYS___time:
//         {
//             /* getSysTickTime(): elapsed SysTick time in milliseconds (64-bit).
//                We return the lower 32 bits in svc_retval for the generic syscall ABI.
//                If you need full 64-bit in userland, expose a separate pair-getter or
//                store it into a user buffer provided via args. */
//             uint64_t ms = k_time_ms();
//             svc_retval  = (int32_t)(ms & 0xFFFFFFFFu);
//             break;
//         }

//         case SYS_reboot:
//         {
//             /* No return: if the platform reboots immediately. If it schedules a reboot,
//                report success (0) and continue. */
//             k_reboot();
//             svc_retval = 0;
//             break;
//         }

//         case SYS__exit:
//         {
//             /* Terminate current task and yield to next ready task. */
//             k_exit();        /* should mark state=TERMINATED and remove from scheduler’s run queue */
//             k_yield();       /* ensure the next task runs; on some ports k_exit itself never returns */
//             svc_retval = 0;  /* Not reached in well-behaved k_exit; kept to satisfy the ABI. */
//             break;
//         }

//         case SYS_getpid:
//         {
//             pid_t pid = k_getpid();
//             svc_retval = (int32_t)pid;
//             break;
//         }

//         case SYS_yield:
//         {
//             k_yield();       /* cooperative yield from unprivileged code */
//             svc_retval = 0;
//             break;
//         }

//         default:
//         {
//             /* Unknown/unsupported syscall */
//             sys_ret_err(ENOSYS);     /* “Function not implemented” */
//             break;
//         }
//     }
//     /* SVC handler will return to unprivileged code; r0 should be loaded from svc_retval there. */
// }



/*
 * Copyright (c) 2022 
 * Computer Science and Engineering, University of Dhaka
 * Credit: CSE Batch 25 (starter) and Prof. Mosaddek Tushar
 *
 * See original license header in your tree.
 */

#include <stdint.h>
#include <stddef.h>
#include <syscall.h>
#include <syscall_def.h>
#include <errmsg.h>      /* your OS error strings table lives here */

/* -------------------------------------------------------------
 * If your OS has a dedicated error-code header (e.g., error.h),
 * include it here. Otherwise define minimal fallbacks so this
 * file doesn’t depend on libc <errno.h> in the kernel.
 * ------------------------------------------------------------- */


 #include <stdint.h>
#define THUMB_PTR(fn) ((void*)((uintptr_t)(fn) | 1u))

typedef int32_t  ssize_t;
typedef ssize_t (*kread_fn)(int, void*, size_t);
typedef ssize_t (*kwrite_fn)(int, const void*, size_t);
typedef uint64_t (*ktime_fn)(void);
typedef void    (*kvoid_fn)(void);
typedef int32_t (*kpid_fn)(void);

#ifndef EINVAL
#define EINVAL 22     /* Invalid argument */
#endif
#ifndef ENOSYS
#define ENOSYS 38     /* Function not implemented */
#endif

/* -------- Calling convention between SVC handler and syscall() --------
 * SVC handler must set BEFORE calling syscall(callno):
 *   svc_args[0] = service ID (same as 'callno')
 *   svc_args[1] = arg0 (e.g., fd)
 *   svc_args[2] = arg1 (e.g., buf)
 *   svc_args[3] = arg2 (e.g., size)
 * syscall() must store the integer return value into svc_retval.
 */
extern uint32_t svc_args[4];
extern int32_t  svc_retval;

/* -------- Kernel-private service entry points (privileged) ---------- */
typedef int32_t  pid_t;
typedef int32_t  ssize_t;

/* I/O (USART when fd == STDIN_FILENO / STDOUT_FILENO) */
extern ssize_t k_read (int fd, void *buf, size_t size);   /* must honor '\n' and 256B cap */
extern ssize_t k_write(int fd, const void *buf, size_t size);

/* Time (SysTick in milliseconds, 64-bit) */
extern uint64_t k_time_ms(void);

/* Process/task & scheduling */
extern void  k_exit(void);      /* mark TCB terminated, remove from run queue */
extern void  k_yield(void);     /* trigger PendSV / schedule next */
extern pid_t k_getpid(void);

/* Platform control */
extern void  k_reboot(void);

/* FDs (if not pulled in elsewhere) */
#ifndef STDIN_FILENO
#define STDIN_FILENO   0
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO  1
#endif

/* -------- Small helpers to read args from svc_args[] -------- */
static inline uint16_t arg_service_id(void)   { return (uint16_t)svc_args[0]; }
static inline int32_t  arg0_i32(void)         { return (int32_t) svc_args[1]; }
static inline void    *arg1_ptr(void)         { return (void*)(uintptr_t)svc_args[2]; }
static inline uint32_t arg2_u32(void)         { return (uint32_t)svc_args[3]; }

/* Clamp read size to 256 bytes per spec */
static inline size_t clamp_read_size(size_t n){ return (n > 256u) ? 256u : n; }

/* Kernel error path: return negative errno in r0 (no user-space errno here) */
static inline void sys_ret_err(int err)       { svc_retval = -err; }

/* ------------------------ Main dispatcher ------------------------ */
void syscall(uint16_t callno)
{
    (void)callno; /* we can trust handler; enable the assert below if you want to cross-check */
    /* Example strictness:
     * if (arg_service_id() != callno) { sys_ret_err(EINVAL); return; }
     */

    switch (arg_service_id())
    {
        case SYS_read:
        {
            int     fd  = arg0_i32();
            void   *buf = arg1_ptr();
            size_t  sz  = clamp_read_size((size_t)arg2_u32());

            if (buf == NULL) { sys_ret_err(EINVAL); break; }

            ssize_t nread = ((kread_fn)THUMB_PTR(k_read))(fd, buf, sz);

            if (nread < 0)       svc_retval = nread;   /* already negative errno */
            else                 svc_retval = (int32_t)nread;
            break;
        }

        case SYS_write:
        {
            int          fd  = arg0_i32();
            const void  *buf = (const void*)arg1_ptr();
            size_t       sz  = (size_t)arg2_u32();

            if (buf == NULL && sz != 0) { sys_ret_err(EINVAL); break; }

            ssize_t nw = ((kwrite_fn)THUMB_PTR(k_write))(fd, buf, sz);

            if (nw < 0)               svc_retval = nw; /* negative errno */
            else                      svc_retval = (int32_t)nw;
            break;
        }

        case SYS___time:
        {
            /* Return lower 32 bits; expose full 64-bit via a different API if needed */
            uint64_t ms = ((ktime_fn)THUMB_PTR(k_time_ms))();

            svc_retval = (int32_t)(ms & 0xFFFFFFFFu);
            break;
        }

        case SYS_reboot:
        {
           ((kvoid_fn)THUMB_PTR(k_reboot))();
           /* may not return if immediate reboot */
            svc_retval = 0;
            break;
        }

        case SYS__exit:
        {
            ((kvoid_fn)THUMB_PTR(k_exit))();
            ((kvoid_fn)THUMB_PTR(k_yield))();
            /* ensure next task runs (PendSV) */
            svc_retval = 0;        /* not reached on typical implementations */
            break;
        }

        case SYS_getpid:
        {
           pid_t pid = ((kpid_fn)THUMB_PTR(k_getpid))();

            break;
        }

        case SYS_yield:
        {
            k_yield();
            svc_retval = 0;
            break;
        }

        default:
        {
            sys_ret_err(ENOSYS);   /* Function not implemented */
            break;
        }
    }
    /* SVC handler will copy svc_retval into stacked r0 and return to Thread mode. */
}

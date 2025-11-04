
 
// #include <unistd.h>
// #include <stdint.h>
// #include <syscall_def.h>
// #include <stddef.h>
// #include <cm4.h>
// #include <kstdio.h>
// #include <syscall.h>


// uint32_t getSysTickTime(void)
// {
//     uint32_t result;
//     /* Inline assembly: r0 = SYS___time, svc 0, result in r0. We
//      * specify clobbers to inform the compiler that r0 and lr are
//      * modified by the assembly. */
//     __asm volatile(
//         "mov r0, %[callno]\n"
//         "svc 0\n"
//         "mov %[res], r0\n"
//         : [res] "=r" (result)            /* output */
//         : [callno] "r" (SYS___time)      /* input */
//         : "r0", "lr", "memory"
//     );
//     return result;
// }
 
#include <unistd.h>
#include <stdint.h>
#include <syscall_def.h>
#include <stddef.h>

/**
 * APPROACH: Pass syscall number in r0 (first argument position)
 * and shift other arguments. The handler will extract the syscall
 * number from stacked r0 and actual arguments from r1, r2, r3.
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
 * @brief Get current SysTick time in milliseconds
 * @return Current time in milliseconds since system start
 * 
 * This function makes an SVC call to enter kernel mode and retrieve
 * the current SysTick counter value.
 */
uint32_t getSysTickTime(void)
{
    // Make SVC call with SYS___time (113)
    // No arguments needed (0u, 0u, 0u)
    return (uint32_t)svc_call(SYS___time, 0u, 0u, 0u);
}

/**
 * @brief Write to file descriptor
 */
ssize_t write(int fd, const void *buf, size_t n)
{
    return (ssize_t)svc_call(SYS_write, (uint32_t)fd, (uint32_t)buf, (uint32_t)n);
}

/**
 * @brief Read from file descriptor
 */
ssize_t read(int fd, void *buf, size_t n)
{
    return (ssize_t)svc_call(SYS_read, (uint32_t)fd, (uint32_t)buf, (uint32_t)n);
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


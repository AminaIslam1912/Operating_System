#include <kunistd.h>
#include <stddef.h>
#include <stdint.h>
#include <cm4.h>
#include <kstdio.h>
#include <errno.h>
#include<stdio.h>

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
    
    // For STDOUT (fd=1) and STDERR (fd=2), write to debug console
    if (fd == 1 || fd == 2) {
        const uint8_t *str = (const uint8_t *)buf;
        putstr(str, n);
        return (ssize_t)n;
    }
    
    // For other file descriptors, not implemented yet
    return -ENOSYS;
}

/**
 * @brief Kernel implementation of read
 * @param fd: File descriptor
 * @param buf: Buffer to read into
 * @param n: Number of bytes to read
 * @return Number of bytes read, or negative error code
 */
ssize_t k_read(int fd, void *buf, size_t n)
{
    // TODO: Implement actual file/device reading
    // For now, return not implemented
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


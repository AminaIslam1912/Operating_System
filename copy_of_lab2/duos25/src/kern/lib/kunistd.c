#include <kunistd.h>
#include <stddef.h>
#include <stdint.h>
#include <cm4.h>
#include <kstdio.h>
#include <errno.h>
#include <stdio.h>
#include <system_config.h>
#include <UsartRingBuffer.h>
#include<unistd.h>
#include <kstdio.h>
#include <sys_init.h>


// UART register definitions (same as your working code)
#define UART_BASE     0x40004400U   // USART2 base address
#define UART_SR       (*(volatile uint32_t*)(UART_BASE + 0x00))
#define UART_DR       (*(volatile uint32_t*)(UART_BASE + 0x04))
#define UART_TX_READY (1U << 7)
#define UART_RX_READY (1U << 5)

// External functions from cm4.c
extern uint32_t __getTime(void);
extern uint32_t __getSysTickCount(void);

// Use ring buffer USART helpers for I/O
// We avoid libc getchar/putchar due to -nostdlib build

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
    // if (fd == 1 || fd == 2) {
    if (fd == STDOUT_FILENO ) {
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
// ssize_t k_read(int fd, void *buf, size_t n)
// {
//     if (buf == NULL) {
//         return -EINVAL;
//     }
//     if (n == 0) {
//         return 0;
//     }

//     if (fd == 0) {
//         uint8_t *dst = (uint8_t *)buf;
//         /* Cap input length at 256 bytes as per spec */
//         size_t max = (n > 256u) ? 256u : n;
//         size_t i = 0;
//         while (i < max) {
//             /* Wait for data; SVC has lower prio than USART, so RX IRQ
//                can preempt and fill the ring buffer. */
//             while (IsDataAvailable(__CONSOLE) <= 0) {
//                 /* spin until a byte arrives */
//             }
//             int c = Uart_read(__CONSOLE);
//             if (c < 0) {
//                 continue;
//             }
//             dst[i++] = (uint8_t)c;
//             if (c == '\n' || c == '\r') {
//                 break;
//             }
//         }
//         /* If caller requested more than 256, ignore the extra input per spec.
//            We do not flush here to avoid blocking indefinitely; extras remain
//            in the ring buffer. */
//         return (ssize_t)i;
//     }

//     return -ENOSYS;
// }

// ssize_t k_read(int fd, void *buf, size_t n)
// {
//     kprintf("in k_read \n");
//     if (buf == NULL) {
//         return -EINVAL;
//     }
//     if (n == 0) {
//         return 0;
//     }

//     // Cap input length at 256 bytes as per spec
//     if (n > 256u) {
//         n = 256u;
//     }

//     // Only support STDIN for now
//     if (fd != 0 && fd != STDIN_FILENO) {
//         return -ENOSYS;
//     }

//     uint8_t *dst = (uint8_t *)buf;
//     size_t i = 0;

//     while (i < n) {
//         // Wait for a byte to be available in the RX ring buffer
//         while (IsDataAvailable(__CONSOLE) <= 0) {
//             // busy wait; USART IRQ fills the buffer
//         }

//         int c = Uart_read(__CONSOLE);
//         if (c < 0) {
//             // On transient error, continue; if nothing read yet, report EIO
//             if (i == 0) return -EIO;
//             break;
//         }

//         dst[i++] = (uint8_t)c;

//         // Echo back the character for user feedback
//         Uart_write((int)(uint8_t)c, __CONSOLE);

//         // Stop on newline or carriage return
//         if (c == '\n' || c == '\r') {
//             break;
//         }
//     }

//     return (ssize_t)i;
// }


static int uart_recv_char(void) 
{
    // Wait until data received
    // This is a blocking wait - it will wait until a character arrives
    while (!(UART_SR & UART_RX_READY));
    
    // Read and return the received byte
    return (int)(UART_DR & 0xFF);
}

/**
 * @brief Kernel implementation of read
 * @param fd: File descriptor
 * @param buf: Buffer to read into
 * @param n: Number of bytes to read (max 256 bytes)
 * @return Number of bytes read, or negative error code
 */
ssize_t k_read(int fd, void *buf, size_t n)
{
    // Validate parameters
    if (buf == NULL || n == 0) {
        return -EINVAL;  // Invalid argument
    }
    
    // Only handle STDIN (fd=0)
    if (fd != STDIN_FILENO ) {
        return -ENOSYS;  // Not implemented for other file descriptors
    }
    
    // Cast buffer to char pointer
    char *cbuf = (char *)buf;
    int bytes_read = 0;
    
    // Limit maximum read size to 256 bytes
    int max_size = (n > 256) ? 256 : (int)n;
    
    // Read characters one by one
    for (int i = 0; i < max_size; i++) {
        // Receive one character from UART
        int c = uart_recv_char();
        
        // Check for error (though uart_recv_char blocks, this is for safety)
        if (c < 0) {
            break;
        }
        
        // Store character in buffer
        cbuf[i] = (char)c;
        bytes_read++;
        
        // Echo the character back to terminal
        kputchar(c);
        
        // Check for termination characters
        if (c == '\n' || c == '\r' || c == '\0') {
            break;
        }
    }
    
    return (ssize_t)bytes_read;
}



/**
 * @brief Kernel implementation of getpid
 * @return Current process ID (for now, always returns 1)
 */
int k_getpid(void)
{
    // TODO: Implement actual process management
    // For now, return a dummy PID
    kprintf("Process getpid called\n");
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
    kprintf("Process yield called\n");
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
    // while(1) {
    //     __WFI();  // Wait for interrupt (low power mode)
    // }
}

/**
 * @brief Kernel implementation of reboot
 * @return 0 on success, negative error code on failure
 */
// int k_reboot(void)
// {
//     // Print message to inform user
//     kprintf("System rebooting...\n");

//     while(!(USART2->SR & USART_SR_TC));
    
//     // Give time for UART to transmit the message
//     ms_delay(1000);
    
//     // Perform software reset using ARM Cortex-M AIRCR register
//     // AIRCR = Application Interrupt and Reset Control Register
//     SCB->AIRCR = (0x5FA << 16) |      // VECTKEY: Write key (required)
//                  (SCB->AIRCR & 0x700) | // Keep priority group unchanged
//                  (1 << 2);             // SYSRESETREQ: Request system reset
    
//     // Should never reach here - system will reset
//     while(1);
    
//     return 0;
// }


int k_reboot(void)
{
    // Print message and flush UART
//     kprintf("System rebooting...\n");
    
//    while ((UART_SR & UART_TX_READY) == 0) {
//     /* wait for the last byte to leave USART2 */
// }


   
    
    // Give more time for UART transmission
    // ms_delay(1000);
    
    // Disable all interrupts
    //  __disable_irq();
    
    // Perform system reset
    SCB->AIRCR = ((0x5FA << SCB_AIRCR_VECTKEY_Pos) | 
                  (SCB->AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                  SCB_AIRCR_SYSRESETREQ_Msk);
    
    // Wait for reset
    while(1);
    
    return 0; // Never reached
}


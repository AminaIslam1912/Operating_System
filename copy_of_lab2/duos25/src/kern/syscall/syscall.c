

// #include <syscall.h>
// #include <syscall_def.h>
// #include <errno.h>
// #include <errmsg.h>
// #include <cm4.h>

// /*
//  * syscall: kernel dispatcher invoked from SVC handler.
//  * args points to stacked registers on exception entry:
//  *   args[0]=r0, args[1]=r1, args[2]=r2, args[3]=r3, args[6]=pc
//  * Return value is delivered in r0 to user mode via SVC handler.
//  */
// uint32_t syscall(uint16_t callno)
// {
//   /* unused for now; kept for future syscalls with arguments */

//     switch (callno) {
//         /* Example placeholders (not implemented): SYS_read, SYS_write, etc. */

//         case SYS___time:
//             /* Return current elapsed time in milliseconds */
        

//         default:
//             /* Not implemented */
             
//     }
// }



#include <syscall.h>
#include <syscall_def.h>
#include <errno.h>
#include <errmsg.h>
#include <kunistd.h>
#include <stdint.h>
#include <sys/types.h>
#include <kstdio.h>
#include <sys_init.h>
#include <cm4.h>

/**
 * @brief Main syscall dispatcher
 * @param callno: System call number (extracted from stacked r0)
 * @param svc_args: Pointer to stacked registers
 *        [0]=syscall#, [1]=arg0, [2]=arg1, [3]=arg2, [4]=r12, [5]=lr, [6]=pc, [7]=xpsr
 * 
 * This function is called from SVC_Handler_C and dispatches to appropriate
 * kernel functions based on the syscall number. The return value should be
 * placed in svc_args[0] (which represents the stacked r0 register).
 */
void syscall(uint16_t callno, uint32_t *svc_args)
{
    int32_t ret = 0;  // Return value (will be placed in r0)
    
    switch(callno)
    {
        case SYS_read:
        {
           
            int fd = (int)svc_args[1];
            void *buf = (void *)svc_args[2];
            size_t n = (size_t)svc_args[3];
            
            // Call kernel function
            ret = k_read(fd, buf, n);
            break;
        }
        
        case SYS_write:
        {
            int fd = (int)svc_args[1];
            const void *buf = (const void *)svc_args[2];
            size_t n = (size_t)svc_args[3];
            
            ret = k_write(fd, buf, n);
            break;
        }
        
        case SYS___time:
        {
            
            ret = (int32_t)k_getSysTickTime();
            break;
        }
        
        case SYS_getpid:
        {
            // Get process ID
            ret = k_getpid();
            break;
        }
        
        case SYS_yield:
        {
            // Yield CPU
            k_yield();
            ret = 0;
            break;
        }
        
        case SYS__exit:
        {
            // Exit process
            k_exit();
            ret = 0;  // Never actually returns
            break;
        }
        
        case SYS_reboot:
        {
            
            ret = k_reboot();
            break;
        }
        
        default:
            // Unknown system call - return error
            ret = -ENOSYS;  
            break;
    }
    
    // Store return value in stacked r0 so it returns to user space
    svc_args[0] = (uint32_t)ret;
}




#include <unistd.h>
#include <kstdio.h>
#include <sys_init.h>
#include <cm4.h>
#include <kmain.h>
// extern kmain;

extern void kmain(void);

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int main(void)

{
    

    //kmain();

    // kprintf("\nSimple read() Test\n\n");
    ms_delay(2000);

    // First verify other syscalls work
    kprintf("Verifying  syscalls...\n");

    ms_delay(2000);

    uint32_t t = getSysTickTime();

    kprintf("Time: %u ms \n", t);
    ms_delay(2000);

    int pid = getpid();
    kprintf("PID: %d \n\n", pid);
    ms_delay(2000);

    // Now test read
    kprintf("Now testing read()...\n");
    ms_delay(2000);

    kprintf("Type something and press Enter: ");
    ms_delay(2000);

    char buffer[32];
    ssize_t n = read(0, buffer, 31);

    // kprintf("\nResult:\n");
    // ms_delay(2000);

    kprintf("\n\nBytes read: %d\n", n);
    ms_delay(2000);

    if (n > 0)
    {
        buffer[n] = '\0';
        kprintf("\nString : %s\n", buffer);
        
    }
    else if (n == 0)
    {
        kprintf("No data read\n");
    }
    else
    {
        kprintf("Error code: %d\n", n);
    }

    kprintf("\nNow testing write()...\n\n");
    ms_delay(2000);

    write(1, "helloFromWrite", 14);

   
    ms_delay(2000);
 
    // ms_delay(100); 

    yield();
    ms_delay(1000); 
    
    kprintf("\n\nInitiating system reboot...\n");
    reboot();   
    
    kprintf("\n=== Test complete ===\n");

    return 0;
}
// // // // #include <kunistd.h>
// // // // #include <stdint.h>
// // // // #include <unistd.h>

// // // // int main(void)
// // // // {
// // // //     char buf[128];
// // // //     const char *hello = "Type something (newline to end):\n";
// // // //     (void)write(STDOUT_FILENO, hello, 33);

// // // //     ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
// // // //     if (n > 0) {
// // // //         (void)write(STDOUT_FILENO, "You typed: ", 11);
// // // //         (void)write(STDOUT_FILENO, buf, (size_t)n);
// // // //         (void)write(STDOUT_FILENO, "\n", 1);
// // // //     }

// // // //     uint32_t t = getSysTickTime();
// // // //     (void)write(STDOUT_FILENO, "ms=", 3);

// // // //     char d[12]; int i = 11; d[i--] = '\0'; if (t == 0) d[i--] = '0';
// // // //     while (t){ d[i--] = '0' + (t % 10u); t /= 10u; }
// // // //     (void)write(STDOUT_FILENO, &d[i+1], (size_t)(11 - (i+1)));

// // // //     (void)write(STDOUT_FILENO, "\nBye!\n", 6);
// // // //     exit();
// // // //     return 0; /* never reached */
// // // // }


// // // #include <times.h>
// // // #include <kstdio.h>
// // // #include <unistd.h>

// // // int main(void)
// // // {
// // //     // uint32_t time = getSysTickTime();
// // //     // kprintf("System time: %d ms\n", time);
// // //     // return 0;
// // // }


// // /*
// //  * Example main.c demonstrating the use of getSysTickTime() system call
// //  */

// /* Minimal user program to test SVC time syscall */
// #include <kstdio.h>
// #include <times.h>
// #include <cm4.h>
// #include <stdint.h>

// int main(void)
// {
//     // kprintf("User: SVC time test running\n");
    
//     //     uint32_t t = getSysTickTime();
//     //     kprintf("time = %u ms\n", t);
//     //     ms_delay(1000);
//     //     t = getSysTickTime();
//     //     kprintf("time = %u ms\n", t);
//     return 0;
// }

#include <unistd.h>
#include <kstdio.h>
#include<sys_init.h>
#include<cm4.h>

int main(void)
{
    kprintf("\n=== SVC Syscall Test Program ===\n\n");
    
    // Test 1: Get system time via SVC
    kprintf("Test 1: Getting system time via SVC call...\n");
    uint32_t start = getSysTickTime();
    kprintf("Start time: %u ms\n\n", start);
    
    // Test 2: Delay and get time again
    kprintf("Test 2: Waiting 2000ms...\n");
    ms_delay(2000);
    
    uint32_t end = getSysTickTime();
    kprintf("End time: %u ms\n", end);
    kprintf("Elapsed: %u ms\n\n", end - start);
    
    // Test 3: Multiple readings
    kprintf("Test 3: Reading time 5 times with 500ms delay:\n");
    for (int i = 0; i < 5; i++) {
        uint32_t t = getSysTickTime();
        kprintf("  Reading %d: %u ms\n", i + 1, t);
        ms_delay(500);
    }
    kprintf("\n");
    
    // Test 4: Get process ID via SVC
    kprintf("Test 4: Getting process ID via SVC...\n");
    int pid = getpid();
    kprintf("Current PID: %d\n\n", pid);
    
    // Test 5: Write via SVC
    kprintf("Test 5: Writing to stdout via SVC...\n");
    const char *msg = "Hello from user space via SVC!\n";
    ssize_t written = write(1, msg, 32);
    kprintf("Wrote %d bytes\n\n", (int)written);
    
    kprintf("=== All tests completed successfully ===\n\n");
    
    // Continuous monitoring loop
    kprintf("Starting continuous time monitoring...\n");
    uint32_t last_time = getSysTickTime();
    uint32_t counter = 0;
    
    while(1) {
        uint32_t current_time = getSysTickTime();
        
        // Print time every second
        if (current_time - last_time >= 1000) {
            counter++;
            kprintf("[%u] Uptime: %u seconds (%u ms)\n", 
                    counter, current_time / 1000, current_time);
            last_time = current_time;
        }
    }
    
    return 0;
}


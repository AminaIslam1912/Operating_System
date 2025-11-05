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
#include <sys_init.h>
#include <cm4.h>
#include <kmain.h>
// extern kmain;

extern void kmain(void);

// int main(void)

// {

//     kprintf("\n=== SVC Syscall Test Program ===\n\n");
//     // kmain();

//     // Test 0: Basic read via SVC
//     // kprintf("Type something (newline to end):\n");
//     // char buf[128];
//     // ssize_t n = read(0, buf, sizeof(buf) - 1);
//     // if (n > 0) {
//     //     buf[n] = '\0';
//     //     kprintf("You typed: %s\n\n", (uint8_t*)buf);
//     // } else {
//     //     kprintf("read() returned %d\n\n", (int)n);
//     // }

//     // Test 1: Get system time via SVC
//     kprintf("Test 1: Getting system time via SVC call...\n");
//     uint32_t start = getSysTickTime();
//     kprintf("Start time: %u ms\n\n", start);

//     // Test 2: Delay and get time again
//     kprintf("Test 2: Waiting 2000ms...\n");
//     ms_delay(2000);

//     // uint32_t end = getSysTickTime();
//     // kprintf("End time: %u ms\n", end);
//     // kprintf("Elapsed: %u ms\n\n", end - start);

//     // Test 3: Multiple readings
//     // kprintf("Test 3: Reading time 5 times with 500ms delay:\n");
//     // for (int i = 0; i < 5; i++) {
//     //     uint32_t t = getSysTickTime();
//     //     kprintf("  Reading %d: %u ms\n", i + 1, t);
//     //     ms_delay(500);
//     // }
//     kprintf("\n");

//     // Test 4: Get process ID via SVC
//     kprintf("Test 4: Getting process ID via SVC...\n");
//     int pid = getpid();
//     kprintf("Current PID: %d\n\n", pid);

//     // Test 5: Write via SVC
//     kprintf("Test 5: Writing to stdout via SVC...\n");
//     const char *msg = "Hello from user space via SVC!\n";
//     ssize_t written = write(1, msg, 32);
//     kprintf("Wrote %d bytes\n\n", (int)written);

//     kprintf("=== All tests completed successfully ===\n\n");

//     // // Test 0: Basic read via SVC
//     // kprintf("Type something (newline to end):\n");
//     // char buf[128];
//     // ssize_t n = read(0, buf, sizeof(buf) - 1);
//     // if (n > 0) {
//     //     buf[n] = '\0';
//     //     kprintf("You typed: %s\n\n", (uint8_t*)buf);
//     // } else {
//     //     kprintf("read() returned %d\n\n", (int)n);
//     // }

//     // Continuous monitoring loop
//     // kprintf("Starting continuous time monitoring...\n");
//     // uint32_t last_time = getSysTickTime();
//     // uint32_t counter = 0;

//     // while(1) {
//     //     uint32_t current_time = getSysTickTime();

//     //     // Print time every second
//     //     if (current_time - last_time >= 1000) {
//     //         counter++;
//     //         kprintf("[%u] Uptime: %u seconds (%u ms)\n",
//     //                 counter, current_time / 1000, current_time);
//     //         last_time = current_time;
//     //     }
//     // }

//     return 0;
// }

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

int main(void)

{
    // kprintf("\n=== SYS_read Test Program ===\n\n");

    // // Test 1: Read a line from user
    // kprintf("Test 1: Reading a line from STDIN\n");
    // kprintf("Type something and press Enter:\n");
    // write(1, "mainf", 5);

    // ms_delay(2000);

    //  char buffer[128];

    // ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    // if (bytes_read > 0) {
    //     // Null-terminate the string
    //     buffer[bytes_read] = '\0';

    //     kprintf("\nYou typed %d bytes:\n", bytes_read);
    //     kprintf("Data: %s", buffer);
    // } else if (bytes_read == 0) {
    //     kprintf("No data read\n");
    // } else {
    //     kprintf("Read error: %d\n", bytes_read);
    // }

    // kprintf("\n");

    // // Test 2: Echo loop
    // kprintf("Test 2: Echo loop (type 'quit' to exit)\n");
    // kprintf("Type lines and they will be echoed back:\n\n");

    // while (1) {
    //     kprintf("> ");

    //     bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    //     if (bytes_read > 0) {
    //         buffer[bytes_read] = '\0';

    //         // Check for quit command
    //         if (buffer[0] == 'q' && buffer[1] == 'u' &&
    //             buffer[2] == 'i' && buffer[3] == 't') {
    //             kprintf("Exiting echo loop...\n");
    //             break;
    //         }

    //         // Echo back
    //         kprintf("Echo: %s", buffer);
    //     }
    // }

    // // Test 3: Test with write syscall
    // kprintf("\nTest 3: Combined read/write test\n");
    // kprintf("Enter your name: ");

    // bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    // if (bytes_read > 0) {
    //     buffer[bytes_read] = '\0';

    //     // Remove newline if present
    //     if (bytes_read > 0 && (buffer[bytes_read-1] == '\n' || buffer[bytes_read-1] == '\r')) {
    //         buffer[bytes_read-1] = '\0';
    //     }

    //     // Write greeting using write syscall
    //     const char *greeting = "\nHello, ";
    //     write(STDOUT_FILENO, greeting, 8);
    //     write(STDOUT_FILENO, buffer, bytes_read - 1);
    //     write(STDOUT_FILENO, "!\n", 2);
    // }

    // // Test 4: Test buffer limit (256 bytes)
    // kprintf("\nTest 4: Testing 256 byte limit\n");
    // kprintf("Try typing more than 256 characters:\n");

    // char big_buffer[300];
    // bytes_read = read(STDIN_FILENO, big_buffer, sizeof(big_buffer));

    // kprintf("\nRead %d bytes (max is 256)\n", bytes_read);

    // // Test 5: Performance test
    // kprintf("\nTest 5: Multiple reads test\n");
    // kprintf("Type 'done' to finish\n");

    // int read_count = 0;
    // uint32_t start_time = getSysTickTime();

    // while (read_count < 5) {
    //     kprintf("Read #%d: ", read_count + 1);

    //     bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    //     if (bytes_read > 0) {
    //         buffer[bytes_read] = '\0';

    //         if (buffer[0] == 'd' && buffer[1] == 'o' &&
    //             buffer[2] == 'n' && buffer[3] == 'e') {
    //             break;
    //         }

    //         read_count++;
    //     }
    // }

    // uint32_t end_time = getSysTickTime();
    // kprintf("\nCompleted %d reads in %u ms\n", read_count, end_time - start_time);

    // kprintf("\n=== All tests completed ===\n");
    // kprintf("System will continue running...\n\n");

    // // Continuous monitoring
    // while(1) {
    //     uint32_t time = getSysTickTime();
    //     kprintf("[%u ms] Enter command: ", time);

    //     bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);

    //     if (bytes_read > 0) {
    //         buffer[bytes_read] = '\0';

    //         // Simple command processing
    //         if (buffer[0] == 't' && buffer[1] == 'i' && buffer[2] == 'm' && buffer[3] == 'e') {
    //             uint32_t current = getSysTickTime();
    //             kprintf("Current time: %u ms (%u seconds)\n",
    //                     current, current / 1000);
    //         }
    //         else if (buffer[0] == 'p' && buffer[1] == 'i' && buffer[2] == 'd') {
    //             int pid = getpid();
    //             kprintf("Process ID: %d\n", pid);
    //         }
    //         else if (buffer[0] == 'h' && buffer[1] == 'e' &&
    //                  buffer[2] == 'l' && buffer[3] == 'p') {
    //             kprintf("\nAvailable commands:\n");
    //             kprintf("  time  - Show current system time\n");
    //             kprintf("  pid   - Show process ID\n");
    //             kprintf("  help  - Show this help\n");
    //             kprintf("  exit  - Exit program\n\n");
    //         }
    //         else if (buffer[0] == 'e' && buffer[1] == 'x' &&
    //                  buffer[2] == 'i' && buffer[3] == 't') {
    //             kprintf("Exiting...\n");
    //             break;
    //         }
    //         else {
    //             kprintf("Unknown command. Type 'help' for commands.\n");
    //         }
    //     }

    //     ms_delay(100);
    // }

    kprintf("\n=== Simple read() Test ===\n\n");
    ms_delay(2000);

    // First verify other syscalls work
    kprintf("Verifying other syscalls...\n");

    ms_delay(2000);

    uint32_t t = getSysTickTime();

    kprintf("Time: %u ms ✓\n", t);
    ms_delay(2000);

    int pid = getpid();
    kprintf("PID: %d ✓\n\n", pid);
    ms_delay(2000);

    // Now test read
    kprintf("Now testing read()...\n");
    ms_delay(2000);

    kprintf("Type something and press Enter: ");
    ms_delay(2000);

    char buffer[32];
    ssize_t n = read(0, buffer, 31);

    kprintf("\n\nResult:\n");
    ms_delay(2000);

    kprintf("  Bytes read: %d\n", n);
    ms_delay(2000);

    if (n > 0)
    {
        buffer[n] = '\0';
        kprintf("  Data: '%s'\n", buffer);
        kprintf("  ✓ SUCCESS!\n");
    }
    else if (n == 0)
    {
        kprintf("  No data read\n");
    }
    else
    {
        kprintf("  Error code: %d\n", n);
    }

    write(1, "mainf", 5);

    kprintf("\n=== Test complete ===\n");

    while (1)
    {
        ms_delay(1000);
    }

    return 0;
}

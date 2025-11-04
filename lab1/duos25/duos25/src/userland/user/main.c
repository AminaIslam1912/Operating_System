#include <kunistd.h>
#include <stdint.h>
#include <unistd.h>

int main(void)
{
    char buf[128];
    const char *hello = "Type something (newline to end):\n";
    (void)write(STDOUT_FILENO, hello, 33);

    ssize_t n = read(STDIN_FILENO, buf, sizeof(buf));
    if (n > 0) {
        (void)write(STDOUT_FILENO, "You typed: ", 11);
        (void)write(STDOUT_FILENO, buf, (size_t)n);
        (void)write(STDOUT_FILENO, "\n", 1);
    }

    uint32_t t = getSysTickTime();
    (void)write(STDOUT_FILENO, "ms=", 3);

    char d[12]; int i = 11; d[i--] = '\0'; if (t == 0) d[i--] = '0';
    while (t){ d[i--] = '0' + (t % 10u); t /= 10u; }
    (void)write(STDOUT_FILENO, &d[i+1], (size_t)(11 - (i+1)));

    (void)write(STDOUT_FILENO, "\nBye!\n", 6);
    exit();
    return 0; /* never reached */
}

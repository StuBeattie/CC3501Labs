#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, const char *argv[])
{
    for (;;)
    {
        // Print a prompt
        printf("[Demo app] > ");
        fflush(stdout); // Print the output even though it doesn't end in a newline
        // Read a line of keyboard input
        char buf[100];
        ssize_t bytes_read = read(STDIN_FILENO, buf, sizeof(buf) - 1); // with room for a trailing null
        if (bytes_read == 0)
        {
            return 0;
        }
        buf[bytes_read] = 0;
        printf("Read: %s\n", buf);
    }
}
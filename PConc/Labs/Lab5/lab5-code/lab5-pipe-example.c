#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief program that creates a pipe, writes values to a it and reads them
 *
 */
int main()
{
    // tow files descriptiors used to write. read on the pipe
    int pipe_fd[2];

    // initialization of the pipe
    if (pipe(pipe_fd) != 0)
    {
        printf("error creating the pipe");
        exit(-1);
    }
    int n = 0;
    int read_value;
    // infinite look that in each iteration writes a number to the pipe and read it aftwards
    while (1)
    {
        printf("going to write %d into pipe_fd[1]\n", n);
        n++;
        sleep(1);

        write(pipe_fd[1], &n, sizeof(n));
        // pipe_fd[1] correpsonded to en entry of data in the pipe
        // &n is apointer to the data to be written
        // sizeof(n) is the ammount of data to write in the pipe

        read(pipe_fd[0], &read_value, sizeof(read_value));
        // pipe_fd[0] correpsonded to the exit of data in the pipe
        // &n is apointer to variable that will hold the read data
        // sizeof(n) is the ammount of data to be read from the pipe
        printf("\tjust read %d from pipe_fd[0]\n", read_value);
    }
}
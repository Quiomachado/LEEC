#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/**
 * @brief program that creates a pipe, writes values to a it and reads them
 *
 */

int pipe_fd[2];

void *thread_function(void *arg)
{
    int *int_arg = (int *)arg;
    char read_value[100];
    while (1)
    {
        read(pipe_fd[0], &read_value, sizeof(read_value));
        printf("Thread just read %s from pipe_fd[0]\n", read_value);
    }
    pthread_exit(NULL);
}

int main()
{
    // tow files descriptiors used to write. read on the pipe

    // initialization of the pipe
    if (pipe(pipe_fd) != 0)
    {
        printf("error creating the pipe");
        exit(-1);
    }
    char n[] = "ola";

    pthread_t thread_id[4];
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&thread_id[i], NULL, thread_function, (void *)i);
    }

    write(pipe_fd[1], &n, sizeof(n));

    // infinite look that in each iteration writes a number to the pipe and read it aftwards
    /* while (1)
    {
        printf("going to write %d into pipe_fd[1]\n", n);
        write(pipe_fd[1], &n, sizeof(n));
        n++;
        sleep(1);
        // pipe_fd[1] correpsonded to en entry of data in the pipe
        // &n is apointer to the data to be written
        // sizeof(n) is the ammount of data to write in the pipe
        // pipe_fd[0] correpsonded to the exit of data in the pipe
        // &n is apointer to variable that will hold the read data
        // sizeof(n) is the ammount of data to be read from the pipe
    } */
}
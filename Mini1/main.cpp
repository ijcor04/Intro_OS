//Isaiah Corrales
//Mini Project 1 CMPS-4103-101
//This program will ask the user for an integer it will then begin its main process and two child forks
//will also be created, the main process will wait to be printed until the child forks are finished
// I used ChatGPT to teach me about fork(), wait() and how to avoid creating unwanted child processes
// I also asked it to teach me about the libraries I would be using in C 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    int N;
	//prompts the user for an integer
    printf("Enter the day of space travel (N): ");
    scanf("%d", &N);

    pid_t pid1 = fork();

    if (pid1 == 0) 
	{
        // First child process prints N, N+2, N+4
        printf("Child 1: %d %d %d\n", N, N+2, N+4);
    } else 
	{
		// this else statement makes sure that we are on the parent and
		//can do another fork call without making 4 processes 
        pid_t pid2 = fork();
        if (pid2 == 0) 
		{
            // Second child process prints N+6, N+8, N+10
            printf("Child 2: %d %d %d\n", N+6, N+8, N+10);
        } else 
		{
            // Main process prints N+12, N+13, N+14
            wait(NULL); // Wait for child processes to finish
            wait(NULL);
            printf("Main process: %d %d %d\n", N+12, N+13, N+14);
        }
    }

    return 0;
}

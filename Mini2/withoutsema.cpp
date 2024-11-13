//Isaiah Corrales-
//Mini Project 2, CMPS-4103-101
//Ocotber 28th, 2024
//This program will utilize three threads to add to our global array and TOTAL. The value we get from 
//adding our array value to the value that is already in our TOTAL global variable will be added into TOTAL.

#include <iostream>
#include <pthread.h>
//defining size of array and the number of threads
#define SIZE 7500
#define NUM_THREADS 3
//initializing our global array & global variable
int array[SIZE];
int TOTAL = 0;
// Function each thread will execute
void* add_to_total(void* thread_id)
{
    int tid = *(int*)thread_id;
    int start = (tid - 1) * (SIZE / NUM_THREADS);
    int end = tid * (SIZE / NUM_THREADS);

    for (int i = start; i < end; i++)
    {
        TOTAL =(TOTAL + array[i]);
    }

    pthread_exit(nullptr);
}

int main()
{
    // Initialize the array
    for (int i = 0; i < SIZE; ++i) 
    {
        array[i] = i + 1;
    }

    // Create threads
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {1, 2, 3};
    for (int i = 0; i < NUM_THREADS; ++i) 
    {
        pthread_create(&threads[i], nullptr, add_to_total, (void*)&thread_id[i]);
    }

    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; ++i) 
    {
        pthread_join(threads[i], nullptr);
    }

    // Print TOTAL
    std::cout << "TOTAL without semaphores: " << TOTAL << std::endl;
    return 0;
}

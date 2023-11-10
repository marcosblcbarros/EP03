#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_SAMPLES 1000000

double estimate_pi(int seed, int num_samples) {
    srand(seed);

    int inside_circle = 0;

    for (int i = 0; i < num_samples; ++i) {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1.0) {
            inside_circle++;
        }
    }

    return (double)inside_circle / num_samples * 4.0;
}

int main() {
    int num_processes = 4; 
    int num_samples_per_process = NUM_SAMPLES / num_processes;
    pid_t child_pid;

    for (int i = 0; i < num_processes; ++i) {
        if ((child_pid = fork()) == 0) {
            
            double pi_estimate = estimate_pi(getpid(), num_samples_per_process);
            printf("Processo filho %d estimou PI como: %f\n", getpid(), pi_estimate);
            exit(0);
        }
    }

    
    for (int i = 0; i < num_processes; ++i) {
        wait(NULL);
    }

    return 0;
}

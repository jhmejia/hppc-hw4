#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]) {
    int num_iterations;
    int num_threads;

    int     thread_count;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <number of threads>\n", argv[0]);
        exit(0);
    }
    thread_count = strtol(argv[1], NULL, 10);
    omp_set_num_threads(thread_count);

    printf("Enter the number of iterations: ");
    scanf("%d", &num_iterations);

    #  pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        int num_threads = omp_get_num_threads();

        #pragma omp for
        for (int i = 0; i < num_iterations; ++i) {
            printf("Thread %d: Iteration %d\n", thread_id, i);
        }
    }

    return 0;
}

#include <stdio.h>
#include <omp.h>

int main() {
    int num_iterations;

    printf("Enter the number of iterations: ");
    scanf("%d", &num_iterations);

    #pragma omp parallel
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

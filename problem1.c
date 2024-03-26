#include <stdio.h>
#include <omp.h> // Include the OpenMP header

int main() {
    #ifdef _OPENMP
        // Check if the _OPENMP macro is defined
        int openmp_version = _OPENMP;
        printf("OpenMP version: %d.%02d\n", openmp_version / 100, openmp_version % 100);
    #else
        printf("OpenMP is not supported.\n");
    #endif

    return 0;
}


#include <iostream>
#include <omp.h>

int main() {
    const int n = 10; // Size of the arrays
    int A[n], B[n], C[n];

    // Initialize arrays A and B
    for (int i = 0; i < n; ++i) {
        A[i] = i + 1;
        B[i] = (i + 1) * 2;
    }

    // Step 1: Compute the prefix sum of (A + B) in parallel
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        C[i] = A[i] + B[i];
    }

    // Step 2: Perform the prefix sum computation in parallel
    for (int stride = 1; stride < n; stride *= 2) {
        #pragma omp parallel for
        for (int i = stride; i < n; ++i) {
            C[i] += C[i - stride];
        }
    }

    // Output the results
    std::cout << "Array C (Prefix Sum of A + B):" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "C[" << i << "] = " << C[i] << std::endl;
    }

    return 0;
}
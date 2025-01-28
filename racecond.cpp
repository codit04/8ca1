#include <iostream>
#include <omp.h>

int main() {
    const int n = 1000000; // Number of iterations
    int counter = 0;       // Shared variable

    // Parallel region with data race
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        counter++; // Unsafe increment (data race)
    }

    // Output the result
    std::cout << "Expected counter value: " << n << std::endl;
    std::cout << "Actual counter value: " << counter << std::endl;

    return 0;
}
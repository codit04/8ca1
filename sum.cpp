#include <iostream>
#include <omp.h>

int main() {
    int n = 1000000; // Example: Sum of the first 1,000,000 numbers
    long long sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }

    std::cout << "Sum of the first " << n << " numbers is: " << sum << std::endl;

    return 0;
}
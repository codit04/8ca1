#include <iostream>
#include <omp.h>

// Function to compute the product of a range of numbers
long long partial_product(int start, int end) {
    long long result = 1;
    for (int i = start; i <= end; ++i) {
        result *= i;
    }
    return result;
}

int main() {
    int n = 20; // Example: Compute 20!
    long long factorial = 1;

    // Number of threads to use
    int num_threads = 4; // Adjust based on your system

    // Divide the work among threads
    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        int chunk_size = n / num_threads;
        int start = thread_id * chunk_size + 1;
        int end = (thread_id == num_threads - 1) ? n : (thread_id + 1) * chunk_size;

        // Compute partial product for this thread's range
        long long partial_result = partial_product(start, end);

        // Combine partial results using critical section
        #pragma omp critical
        {
            factorial *= partial_result;
        }
    }

    std::cout << n << "! = " << factorial << std::endl;

    return 0;
}
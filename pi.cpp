#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

double calculate_pi_parallel(long num_points, int num_threads) {
    long circle_count = 0;

    srand(time(nullptr));  // Seed random generator once

    #pragma omp parallel num_threads(num_threads)
    {
        unsigned int seed = time(nullptr) ^ omp_get_thread_num();  // Unique seed per thread
        long local_count = 0;

        #pragma omp for
        for (long i = 0; i < num_points; i++) {
            double x = (double)rand_r(&seed) / RAND_MAX;
            double y = (double)rand_r(&seed) / RAND_MAX;

            if (x * x + y * y <= 1.0) {
                local_count++;
            }
        }

        #pragma omp atomic
        circle_count += local_count;
    }

    return 4.0 * circle_count / num_points;
}

int main() {
    long num_points = 1000000;  // Number of random points
    int num_threads = 4;        // Number of threads

    double pi_estimate = calculate_pi_parallel(num_points, num_threads);

    cout << "Estimated Pi (Parallel with " << num_threads << " threads): " << pi_estimate << endl;
    return 0;
}

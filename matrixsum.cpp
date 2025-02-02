#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

using namespace std;

const int NX = 1000;  // Number of rows
const int NY = 1000;  // Number of columns

// Function to initialize matrix with random values
void initialize_matrix(vector<vector<int>> &matrix) {
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            matrix[i][j] = rand() % 10; // Random values between 0 and 9
        }
    }
}

// Parallel sum of matrix elements
long long matrix_sum_parallel(const vector<vector<int>> &matrix) {
    long long sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            sum += matrix[i][j];
        }
    }

    return sum;
}

int main() {
    vector<vector<int>> matrix(NX, vector<int>(NY));

    initialize_matrix(matrix);
    
    double start_time = omp_get_wtime();
    long long sum = matrix_sum_parallel(matrix);
    double end_time = omp_get_wtime();

    cout << "Matrix Sum (Parallel): " << sum << endl;
    cout << "Time Taken: " << (end_time - start_time) << " seconds" << endl;
    return 0;
}

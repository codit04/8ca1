int fib(int n) {
    if (n < 2) return n;
    int x, y;
    #pragma omp parallel sections
    {
        #pragma omp section
        x = fib(n - 1);
        #pragma omp section
        y = fib(n - 2);
    }
    return x + y;
}

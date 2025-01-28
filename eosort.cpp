#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>


void sort(int arr[],int n){
    bool sorted = false;
    while(sorted == false){
        sorted = true;
        for(int i =0 ;i<=n-2;i+=2){
            if (arr[i] > arr[i+1]){
                int  t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                sorted = false;
            }
        }
        for(int i = 1;i<=n-2;i+=2){
            if (arr[i] > arr[i+1]){
                int  t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                sorted = false;
            }
        }
    }
}
void sort_parallel(int arr[],int n){

    bool sorted = false;
    while(sorted == false){
        sorted = true;
        #pragma omp parallel for firstprivate(arr,sorted)
        for(int i =0 ;i<=n-2;i+=2){
            if (arr[i] > arr[i+1]){
                int  t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                sorted = false;
            }
        }
        #pragma omp parallel for firstprivate(arr,sorted)
        for(int i = 1;i<=n-2;i+=2){
            if (arr[i] > arr[i+1]){
                int  t = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = t;
                sorted = false;
            }
        }
    }
}
int main(){
    int n = 40000;
    int arr[40000];
    for (int i=0;i<n;i++){
        arr[i] = rand();
    }
    clock_t t;
    t = clock();
    sort(arr,n);
    t = clock() - t;


    double time_taken = (double)(t)/CLOCKS_PER_SEC;
    printf("\nTime taken : %f\n",time_taken);


    clock_t t2;
    t2 = clock();
    #pragma omp parallel
        #pragma omp single
            sort_parallel(arr,n);
    t2 = clock() - t2;
    double time_taken2 = (double)(t2)/CLOCKS_PER_SEC;
    printf("\nTime taken : %f\n",time_taken2);
}


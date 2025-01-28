#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


void sort(int arr[],int n){

    for(int i =0 ;i<n;i++){
        for(int j = i;j<n;j++){
            if (arr[i] > arr[j]){
                int  t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }
}
void sort_parallel(int arr[],int n){

    for(int i =0 ;i<n;i++){
        #pragma omp parallel for
            for(int j = i;j<n;j++){
                if (arr[i] > arr[j]){
                    int  t = arr[i];
                    arr[i] = arr[j];
                    arr[j] = t;
                }
            }
        #pragma omp barrier
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
    sort_parallel(arr,n);
    t2 = clock() - t2;
    double time_taken2 = (double)(t2)/CLOCKS_PER_SEC;
    printf("\nTime taken : %f\n",time_taken2);
}


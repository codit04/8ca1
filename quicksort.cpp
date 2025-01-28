#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition(int arr[],int l,int h){
    int i = l-1;
    int pivot = arr[h];
    for (int j = l;j<h;j++){
        if (arr[j] < pivot){
            i++;
            swap(&arr[i],&arr[j]);
        }
    }
    swap(&arr[i+1],&arr[h]);
    return i+1;
}


void sort(int arr[],int l,int h){
    if (l<h){
        int p = partition(arr,l,h);
        sort(arr,0,p-1);
        sort(arr,p+1,h);
    }
}

void sort_parallel(int arr[],int l,int h){
    if (l<h){
        int p = partition(arr,l,h);
        #pragma omp parallel firstprivate(arr,p,l)
        sort(arr,l,p-1);
        #pragma omp parallel firstprivate(arr,p,h)
        sort(arr,p+1,h);
    }
}

int main(){
    clock_t t;
    t  = clock();
    int n = 300;
    int arr[300];
    for (int i=0;i<n;i++){
        arr[i] = rand();
    }
    sort(arr,0,n-1);
    t = clock() - t;
    /*
    for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    */
    double time_taken = (double)(t)/CLOCKS_PER_SEC;
    printf("\nTime taken : %f\n",time_taken);

    clock_t t2;
    t2 = clock();

    #pragma omp parallel
        #pragma omp single
            sort_parallel(arr,0,n-1);

    t2 = clock() - t2;
    double time_taken2 = (double)(t2)/CLOCKS_PER_SEC;
    printf("\nTime taken : %f\n",time_taken2);
}

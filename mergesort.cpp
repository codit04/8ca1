#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


void merge(int arr[],int l,int m,int u){
    int n1 = m-l+1;
    int n2 = u-m;

    int a[n1],b[n2];
    for (int i=0;i<n1;i++){
        a[i] = arr[l+i];
    }
    for (int i=0;i<n2;i++){
        b[i] = arr[m+1+i];
    }

    int i = 0,j = 0,k = l;
    while(i<n1 && j<n2){
        if (a[i] == b[j]){
            arr[k] = a[i];
            k++;
            arr[k] = b[j];
            i++;
            j++;
        }
        else if (a[i] < b[j]){
            arr[k] = a[i];
            i++;
        }
        else{
            arr[k] = b[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        arr[k] = a[i];
        i++;
        k++;
    }
    while(j<n2){
        arr[k] = b[j];
        j++;
        k++;
    }
}

void sort(int arr[],int l,int u){
    if (l<u){
        int m = (l+u)/2;
        sort(arr,l,m);
        sort(arr,m+1,u);
        merge(arr,l,m,u);
    }

}

void sort_parallel(int arr[],int l,int u){
    if (l<u){
        int m = (l+u)/2;

        #pragma omp task firstprivate(arr,l,m)
        sort(arr,l,m);

        #pragma omp task firstprivate(arr,m,u)
        sort(arr,m+1,u);

        #pragma omp taskwait
        merge(arr,l,m,u);
    }
}
int main(){
    int n = 30000;
    int arr[30000];
    for (int i=0;i<n;i++){
        arr[i] = rand();
    }
    clock_t t;
    t = clock();
    sort(arr,0,n-1);
    t = clock() - t;
    /*
    for (int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }*/
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

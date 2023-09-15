

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pbPlots.h"
#include "supportLib.h"

void randomize(int *arr, int n);
void randomizedQuickSort(int *arr, int left, int right) ;
void swap(int *a, int *b);
int partition(int *arr, int left, int right);


int main (){
    printf("\nEnter number of test cases for random quick sort: ");
    int t;
    scanf("%d", &t);

    double *elementSize = (double *)malloc(t * sizeof(double));
    double *time = (double *)malloc(t * sizeof(double));

    // create an empty file
    FILE *fp = fopen("randomQuicksort.txt", "w");
    fclose(fp);

    for(int i = 0; i < t; i++){
        printf("\nEnter the size of array: ");
        int n;
        scanf("%d", &n);

        // store the size of array in an array
        elementSize[i] = n;

        // create array of n size
        int *arr = (int *)malloc(n * sizeof(int));
        randomize(arr, n);
        // append the array in a file
        FILE *fp = fopen("randomQuicksort.txt", "a");
        fprintf(fp, "%d size array: ", n);
        for(int i = 0; i < n; i++){
            fprintf(fp, "%d ", arr[i]);
        }
        fprintf(fp, "\n");
        fclose(fp);
        
        // find time taken by randomQuicksort 
        clock_t start, end;
        start = clock();
        randomizedQuickSort(arr, 0, n-1);
        // append the array in a file
        fp = fopen("randomQuicksort.txt", "a");
        fprintf(fp, "sorted array: ");
        for(int i = 0; i < n; i++){
            fprintf(fp, "%d ", arr[i]);
        }        
        end = clock();
        double time_taken = ((double)(end - start) / CLOCKS_PER_SEC);
        time[i] = time_taken;
        fprintf(fp, "\ntime taken: %f", time_taken);
       fprintf(fp, "\n \n");
        fclose(fp);
        printf("Time taken by quick sort: %f\n", time_taken);
    }

    // add plot data in file
    fp = fopen("randomQuicksort.txt", "a");
    for (size_t i = 0; i < t; i++)
    {
        fprintf(fp, "%f %f\n", elementSize[i], time[i]);

    }
    fclose(fp);

    // plot the graph
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
    DrawScatterPlot(imageRef, 600, 400, elementSize,t, time,t, errorMessage);
    
    size_t length;
    double *pngData = ConvertToPNG(&length, imageRef->image);
    WriteToFile(pngData, length, "randomizedQuickSort.png");
    return 0;
}

//function  to generate random n numbers in array
void randomize(int *arr, int n){
     srand(time(0));
    for(int i = 0; i < n; i++){
        arr[i] = rand();
    }
}

// Swap function
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to randomly select a pivot element
int randomPartition(int *arr, int left, int right) {
    int randomIndex = left + rand() % (right - left + 1);
    swap(&arr[randomIndex], &arr[right]); // Swap the randomly selected element with the rightmost element
    return partition(arr, left, right);
}

// Function to partition the array
int partition(int *arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[right]);
    return i + 1;
}

// Function to sort the array using Randomized QuickSort
void randomizedQuickSort(int *arr, int left, int right) {
    if (left < right) {
        int pivot = randomPartition(arr, left, right);
        randomizedQuickSort(arr, left, pivot - 1);
        randomizedQuickSort(arr, pivot + 1, right);
    }
}



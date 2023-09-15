#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "pbPlots.h"
#include "supportLib.h"

// Linear time algorithm (O(n))
void linearTimeAlgorithm(int n) {
    int c =0;
    for (int i = 0; i < n; i++) {
        c++;

    }
}

// Quadratic time algorithm (O(n^2))
void quadraticTimeAlgorithm(int n) {
      int c =0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
             c++;
        }
    }
}

// Cubic time algorithm (O(n^3))
void cubicTimeAlgorithm(int n) {
      int c =0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                   c++;
            }
        }
    }
}

// n*log(n) time algorithm
void nLogNTimeAlgorithm(int n) {
      int c =0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= log2(n); j++) {
             c++;
        }
    }
}

// Exponential time algorithm (O(2^n))
void exponentialTimeAlgorithm(int n) {
      int c =0;
    for (int i = 0; i < pow(2, n); i++) {
           c++;
    }
}

int main() {
    clock_t start_time, end_time;
    double execution_time;
    double maxN [5];

    printf("\nComplexity \tMax 'n' for 10s\n");

    // Linear time algorithm
    start_time = clock();
    int n_linear = 1;
    while (1) {
        linearTimeAlgorithm(n_linear);
        end_time = clock();
        execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        if (execution_time >= 10.0) {
            break;
        }
        n_linear++;
    }
    printf("Linear\t\t%d\n", n_linear);
    maxN[0] = n_linear;

     // n*log(n) time algorithm
    start_time = clock();
    int n_nlogn = 1;
    while (1) {
        nLogNTimeAlgorithm(n_nlogn);
        end_time = clock();
        execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        if (execution_time >= 10.0) {
            break;
        }
        n_nlogn++;
    }
    printf("n*log(n)\t%d\n", n_nlogn);
    maxN[1] = n_nlogn;

    // Quadratic time algorithm
    start_time = clock();
    int n_quadratic = 1;
    while (1) {
        quadraticTimeAlgorithm(n_quadratic);
        end_time = clock();
        execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        if (execution_time >= 10.0) {
            break;
        }
        n_quadratic++;
    }
    printf("Quadratic\t%d\n", n_quadratic);
    maxN[2] = n_quadratic;

    // Cubic time algorithm
    start_time = clock();
    int n_cubic = 1;
    while (1) {
        cubicTimeAlgorithm(n_cubic);
        end_time = clock();
        execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        if (execution_time >= 10.0) {
            break;
        }
        n_cubic++;
    }
    printf("Cubic\t\t%d\n", n_cubic);
    maxN[3] = n_cubic;   

    // Exponential time algorithm
    start_time = clock();
    int n_exponential = 1;
    while (1) {
        exponentialTimeAlgorithm(n_exponential);
        end_time = clock();
        execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        if (execution_time >= 10.0) {
            break;
        }
        n_exponential++;
    }
    printf("Exponential\t%d\n", n_exponential);
    maxN[4] = n_exponential;

    // plot the graph
    RGBABitmapImageReference *imageRef = CreateRGBABitmapImageReference();
    StringReference *errorMessage = (StringReference *)malloc(sizeof(StringReference));
    DrawBarPlot(imageRef, 600, 400, maxN,5, errorMessage);
    // DrawScatterPlot(imageRef, 600, 400, 10, n_linear, n_nlogn, n_quadratic, n_cubic, n_exponential, errorMessage);

     size_t length;
    double *pngData = ConvertToPNG(&length, imageRef->image);
    WriteToFile(pngData, length, "maxNumberInTenSec.png");

    return 0;
}

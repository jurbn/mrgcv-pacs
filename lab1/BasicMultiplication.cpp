#include <iostream>
#include <fstream>
#include <chrono>

#include "MatrixUtils.h"

using namespace std;

ofstream BenchmarkFile("benchmark_basic.csv");

/**
 * Generates two matrices of size NxN and multiplies them using the basic algorithm.
 * @param N The size of the matrices.
 * @return void
*/
void generateAndMultiplicateBasic(int N){
    // Declare the matrices
    double** A = new double*[N];
    double** B = new double*[N];
    double** C = new double*[N];
    // Allocate memory for the rows of the matrices (to avoid segfault)
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }

    // Fill the matrices
    srand((unsigned int)time(NULL));    // seed the random number generator
    randomlyFillMatrix(N, A);           // fill matrix A with random numbers
    randomlyFillMatrix(N, B);           // fill matrix B with random numbers

    // Start the timer and multiply the matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds

    // Write the results to the benchmark file
    BenchmarkFile << N << ","; 
    BenchmarkFile << (double)(duration.count() / 1000000.0) << endl;   // This is the duration in milliseconds (6 decimal resolution)

    // Deallocate memory to avoid memory leaks
    for (int i = 0; i < N; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
}

int main() {
    cout << "Matrix Multiplication benchmark in progress..." << endl;
    BenchmarkFile << "Size,Basic" << endl;
    for (int N=1; N < 10; N++)
        generateAndMultiplicateBasic(N);
    for (int N=1; N < 10; N++)
        generateAndMultiplicateBasic(N*10);
    for (int N=1; N < 10; N++)
        generateAndMultiplicateBasic(N*100);
    for (int N=1; N < 11; N++)
        generateAndMultiplicateBasic(N*1000);
    BenchmarkFile.close();
    return 0;
}
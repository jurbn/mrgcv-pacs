#include <iostream>
#include <fstream>
#include <chrono>

#include "MatrixUtils.h"

using namespace std;

ofstream BenchmarkFile("benchmark_super_optimized.csv");

void generateAndMultiplicate(int N){
    // Declare the matrices
    double** A = new double*[N];
    double** B = new double*[N];
    double** C = new double*[N];

    // Allocate memory for the rows of the matrices (**to avoid segfault**)
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }

    // Declare the Eigen matrices
    Eigen::MatrixXd eigenA(N, N);
    Eigen::MatrixXd eigenB(N, N);
    Eigen::MatrixXd eigenC(N, N);

    // Fill the matrices
    srand((unsigned int)time(NULL));
    randomlyFillMatrix(N, A, eigenA);
    // cout << "Matrix A: " << endl;
    // printMatrix(N, A);
    randomlyFillMatrix(N, B, eigenB);
    // cout << "Matrix B: " << endl;
    // printMatrix(N, B);

    // Basic multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds  
    BenchmarkFile << N << ","; 
    BenchmarkFile << (double)(duration.count() / 1000000.0) << ",";   // This is the duration in milliseconds (3 decimal resolution)

    // Eigen multiplication of both matrices
    start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, eigenA, eigenB, eigenC);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    BenchmarkFile << (double)(duration.count() / 1000000.0) << endl;   // This is the duration in milliseconds (3 decimal resolution)

    // cout << "Matrix C: "<< endl;
    // printMatrix(N, C);

    // Deallocate memory to avoid memory leak
    for (int i = 0; i < N; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
    // The Eigen matrices are automatically deallocated
}

void generateAndMultiplicateOptimized(int N){
    // Declare the matrices
    double** A = new double*[N];
    double** B = new double*[N];
    double** C = new double*[N];

    // Allocate memory for the rows of the matrices (**to avoid segfault**)
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }

    // Fill the matrices
    srand((unsigned int)time(NULL));
    randomlyFillMatrix(N, A);
    // cout << "Matrix A: " << endl;
    // printMatrix(N, A);
    randomlyFillMatrix(N, B);
    // cout << "Matrix B: " << endl;
    // printMatrix(N, B);

    // Basic multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds  
    BenchmarkFile << N << ","; 
    BenchmarkFile << (double)(duration.count() / 1000000.0) << ",";   // This is the duration in milliseconds (3 decimal resolution)

    // Optimized multiplication of both matrices
    start = chrono::high_resolution_clock::now();
    multiplyMatricesOptimized(N, A, B, C);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    BenchmarkFile << (double)(duration.count() / 1000000.0) << endl;   // This is the duration in milliseconds (3 decimal resolution)

    // cout << "Matrix C: "<< endl;
    // printMatrix(N, C);

    // Deallocate memory to avoid memory leak
    for (int i = 0; i < N; ++i) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
    // The Eigen matrices are automatically deallocated
}

void generateAndMultiplicateOnlyOptimized(int N){
    // Declare the matrices
    double** A = new double*[N];
    double** B = new double*[N];
    double** C = new double*[N];

    // Allocate memory for the rows of the matrices (**to avoid segfault**)
    for (int i = 0; i < N; ++i) {
        A[i] = new double[N];
        B[i] = new double[N];
        C[i] = new double[N];
    }

    // Fill the matrices
    srand((unsigned int)time(NULL));
    randomlyFillMatrix(N, A);
    // cout << "Matrix A: " << endl;
    // printMatrix(N, A);
    randomlyFillMatrix(N, B);
    // cout << "Matrix B: " << endl;
    // printMatrix(N, B);

    // Basic multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatricesOptimizedParallelized(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds  
    BenchmarkFile << N << ","; 
    BenchmarkFile << (double)(duration.count() / 1000000.0) << endl;   // This is the duration in milliseconds (6 decimal resolution)

    // Deallocate memory to avoid memory leak
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
    BenchmarkFile << "Size,SuperOptimized" << endl;
    for (int N=1; N < 10; N++)
        generateAndMultiplicateOnlyOptimized(N);
    for (int N=1; N < 10; N++)
        generateAndMultiplicateOnlyOptimized(N*10);
    for (int N=1; N < 10; N++)
        generateAndMultiplicateOnlyOptimized(N*100);
    for (int N=1; N < 11; N++)
        generateAndMultiplicateOnlyOptimized(N*1000);
    BenchmarkFile.close();
    return 0;
}
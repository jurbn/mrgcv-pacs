#include <iostream>
#include <fstream>
#include <chrono>

#include "MatrixUtils.h"

using namespace std;

ofstream BenchmarkFile("benchmark_basic.csv");

void generateAndMultiplicateBasic(int N){
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

    BenchmarkFile << N << ",";
    // Basic multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds  
    BenchmarkFile << N << ","; 
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
}

void generateAndMultiplicateEigen(int N){
    // Declare the Eigen matrices
    Eigen::MatrixXd eigenA(N, N);
    Eigen::MatrixXd eigenB(N, N);
    Eigen::MatrixXd eigenC(N, N);

    // Fill the matrices
    srand((unsigned int)time(NULL));
    randomlyFillMatrix(N, eigenA);
    // cout << "Matrix A: " << endl;
    // printMatrix(N, A);
    randomlyFillMatrix(N, eigenB);
    // cout << "Matrix B: " << endl;
    // printMatrix(N, B);

    BenchmarkFile << N << ",";
    // Eigen multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, eigenA, eigenB, eigenC);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    BenchmarkFile << (double)(duration.count() / 1000000.0) << endl;   // This is the duration in milliseconds (3 decimal resolution)

    // Eigen matrices are automatically deallocated
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

    BenchmarkFile << N << ",";
    // Optimized multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatricesOptimized(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
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
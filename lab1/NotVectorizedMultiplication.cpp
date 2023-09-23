#define EIGEN_DONT_VECTORIZE

#include <iostream>
#include <fstream>
#include <chrono>

#include "MatrixUtils.h"

using namespace std;

ofstream BenchmarkFile("benchmark_not_vectorized.csv");

/**
 * Generates two matrices of size NxN and multiplies them using the basic algorithm.
 * @param N The size of the matrices.
 * @return void
*/
void generateAndMultiplicateEigen(int N){
    // Declare the Eigen matrices
    Eigen::MatrixXd eigenA(N, N);
    Eigen::MatrixXd eigenB(N, N);
    Eigen::MatrixXd eigenC(N, N);

    // Fill the matrices
    srand((unsigned int)time(NULL));
    randomlyFillMatrix(N, eigenA);
    randomlyFillMatrix(N, eigenB);

    // Eigen multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    multiplyMatrices(N, eigenA, eigenB, eigenC);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    
    // Write the results to the benchmark file
    BenchmarkFile << N << ",";
    BenchmarkFile << (double)(duration.count() / 1000000.0) << endl;   // This is the duration in milliseconds (6 decimal resolution)

    // Eigen matrices are automatically deallocated
}

int main() {
    cout << "Not Vectorized Matrix Multiplication benchmark in progress..." << endl;
    BenchmarkFile << "Size,NotVectorized" << endl;
    for (int N=1; N < 10; N++)
        generateAndMultiplicateEigen(N);
    for (int N=1; N < 10; N++)
        generateAndMultiplicateEigen(N*10);
    for (int N=1; N < 10; N++)
        generateAndMultiplicateEigen(N*100);
    for (int N=1; N < 11; N++)
        generateAndMultiplicateEigen(N*1000);
    BenchmarkFile.close();
    return 0;
}
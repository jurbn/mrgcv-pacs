#include <iostream>

#include "MatrixUtils.h"

using namespace std;

/**
 * Fills a matrix of size NxN with random doubles.
 * @param N The size of the matrix.
 * @param matrix The matrix to be filled (needs to be allocated).
 * @return void
*/
void randomlyFillMatrix(int N, double** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix[i][j] = double(rand())/double(RAND_MAX/100);
        }
    }
}

/**
 * Fills a matrix of size NxN with random doubles.
 * @param N The size of the matrix.
 * @param matrix The matrix to be filled (needs to be allocated).
 * @return void
*/
void randomlyFillMatrix(int N, Eigen::MatrixXd matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix(i, j) = double(rand())/double(RAND_MAX/100);
        }
    }
}

/**
 * Multiplies two matrices of size NxN.
 * @param N The size of the matrices.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param C The matrix where the result will be stored (needs to be allocated).
 * @return void
*/
void multiplyMatrices(int N, double** A, double** B, double** C){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            for (int k=0; k<N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/**
 * Multiplies two matrices of size NxN.
 * @param N The size of the matrices.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param C The matrix where the result will be stored (needs to be allocated).
 * @return void
*/
void multiplyMatrices(int N, Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C){
    C = A * B;
}

/**
 * Multiplies two matrices of size NxN using an slightly optimized algorithm and parallelization.
 * @param N The size of the matrices.
 * @param A The first matrix.
 * @param B The second matrix.
 * @param C The matrix where the result will be stored (needs to be allocated).
 * @return void
*/
void multiplyMatricesOptimized(int N, double** A, double** B, double** C){
    // pragma omp parallel for private(i,j,k) shared(A,B,C)   // this pragma will parallelize the outer loop
    for (int i=0; i<N; i++){
        for (int k=0; k<N; k++){        // We set k on the inner loop to improve cache performance
            for (int j=0; j<N; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/**
 * Prints a matrix of size NxN.
 * @param N The size of the matrix.
 * @param matrix The matrix to be printed.
 * @return void
*/
void printMatrix(int N, double** matrix){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

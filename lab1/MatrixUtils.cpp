#include <iostream>

#include "MatrixUtils.h"

using namespace std;

void randomlyFillMatrix(int N, double** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix[i][j] = double(rand())/double(RAND_MAX/100);
        }
    }
}

void randomlyFillMatrix(int N, Eigen::MatrixXd matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix(i, j) = double(rand())/double(RAND_MAX/100);
        }
    }
}

// Same as the two before but will fill both array and Eignen matrices
void randomlyFillMatrix(int N, double** matrix, Eigen::MatrixXd eigenMatrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            double random = double(rand())/double(RAND_MAX/100);
            matrix[i][j] = random;
            eigenMatrix(i, j) = random;
        }
    }
}

void multiplyMatrices(int N, double** A, double** B, double** C){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            for (int k=0; k<N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiplyMatrices(int N, Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C){
    C = A * B;
}

void multiplyMatricesOptimized(int N, double** A, double** B, double** C){
    for (int i=0; i<N; i++){
        for (int k=0; k<N; k++){        // We set k on the inner loop to improve cache performance
            for (int j=0; j<N; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void multiplyMatricesOptimizedParallelized(int N, double** A, double** B, double** C){
    #pragma omp parallel for private(i,j,k) shared(A,B,C)   // this pragma will parallelize the outer loop
    for (int i=0; i<N; i++){
        for (int k=0; k<N; k++){        // We set k on the inner loop to improve cache performance
            for (int j=0; j<N; j++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int N, double** matrix){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

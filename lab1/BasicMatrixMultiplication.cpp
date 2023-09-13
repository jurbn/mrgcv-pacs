#include <iostream>
#include <fstream>
#include <chrono>

#include "Eigen/Dense"

using namespace std;

ofstream BenchmarkFile("benchmark.csv");

void fillMatrixWithRandomNumbers(int N, double** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix[i][j] = double(rand())/double(RAND_MAX/100);
        }
    }
}

void fillMatrixWithRandomNumbers(int N, Eigen::MatrixXd matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix(i, j) = double(rand())/double(RAND_MAX/100);
        }
    }
}

// Same as the two before but will fill both array and Eignen matrices
void fillMatrixWithRandomNumbers(int N, double** matrix, Eigen::MatrixXd eigenMatrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            double random = double(rand())/double(RAND_MAX/100);
            matrix[i][j] = random;
            eigenMatrix(i, j) = random;
        }
    }
}


void calculateMatrixMultiplication(int N, double** A, double** B, double** C){
    for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
            for (int k=0; k<N; k++){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void calculateMatrixMultiplication(int N, Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C){
    C = A * B;
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
    fillMatrixWithRandomNumbers(N, A, eigenA);
    // cout << "Matrix A: " << endl;
    // printMatrix(N, A);
    fillMatrixWithRandomNumbers(N, B, eigenB);
    // cout << "Matrix B: " << endl;
    // printMatrix(N, B);

    // Basic multiplication of both matrices
    auto start = chrono::high_resolution_clock::now();
    calculateMatrixMultiplication(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    BenchmarkFile << N << ","; 
    BenchmarkFile << (double)(duration.count() / 1000.0) << ",";   // This is the duration in milliseconds (3 decimal resolution)

    // Eigen multiplication of both matrices
    start = chrono::high_resolution_clock::now();
    calculateMatrixMultiplication(N, eigenA, eigenB, eigenC);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    BenchmarkFile << (double)(duration.count() / 1000.0) << endl;   // This is the duration in milliseconds (3 decimal resolution)

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
    BenchmarkFile << "Size,Basic,Eigen" << endl;
    for (int N=1; N < 10; N++)
        generateAndMultiplicate(N);
    for (int N=1; N < 10; N++)
        generateAndMultiplicate(N*10);
    for (int N=1; N < 11; N++)
        generateAndMultiplicate(N*100);
    
    BenchmarkFile.close();
    return 0;
}

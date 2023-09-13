#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;

ofstream BenchmarkFile("benchmark.csv");

void fillMatrixWithRandomNumbers(int N, double** matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++){
            matrix[i][j] = double(rand())/double(RAND_MAX/100);
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

    // Fill the matrices
    srand((unsigned int)time(NULL));
    fillMatrixWithRandomNumbers(N, A);
    // cout << "Matrix A: " << endl;
    // printMatrix(N, A);
    fillMatrixWithRandomNumbers(N, B);
    // cout << "Matrix B: " << endl;
    // printMatrix(N, B);

    // Multiply both matrices
    auto start = chrono::high_resolution_clock::now();
    calculateMatrixMultiplication(N, A, B, C);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);   // This is the duration in nanoseconds
    BenchmarkFile << N << ","; 
    BenchmarkFile << (double)(duration.count() / 1000.0) << endl;   // This is the duration in milliseconds (3 decimal resolution)

    // cout << "Matrix C: "<< endl;
    // printMatrix(N, C);

    // Deallocate memory
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

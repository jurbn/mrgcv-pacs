#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

#include "Eigen/Dense"  // Eigen library, use g++ -I /path/to/eigen/ MatrixUtils.cpp to compile

void randomlyFillMatrix(int N, double** matrix);
void randomlyFillMatrix(int N, Eigen::MatrixXd matrix);
void randomlyFillMatrix(int N, double** matrix, Eigen::MatrixXd eigenMatrix);
void multiplyMatrices(int N, double** A, double** B, double** C);
void multiplyMatrices(int N, Eigen::MatrixXd A, Eigen::MatrixXd B, Eigen::MatrixXd C);
void multiplyMatricesOptimized(int N, double** A, double** B, double** C);
void multiplyMatricesOptimizedParallelized(int N, double** A, double** B, double** C);
void printMatrix(int N, double** matrix);

#endif
#ifndef MATRIX_OPS_H
#define MATRIX_OPS_H

#include <vector>
#include <string>
#include <iostream>

struct Matrix {
    int rows;
    int cols;
    std::vector<double> data;
};

// Function declarations
Matrix readMatrix(std::ifstream& inputFile);
void gpuMatrixAdd(const Matrix& h_A, const Matrix& h_B, Matrix& h_C);
void writeMatrix(const Matrix& result, std::ostream& out);

#endif
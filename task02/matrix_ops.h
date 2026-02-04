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
Matrix addMatrices(const Matrix& A, const Matrix& B);
void writeMatrix(const Matrix& result, std::ostream& out);

#endif
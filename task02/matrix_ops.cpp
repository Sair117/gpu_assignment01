#include "matrix_ops.h"
#include <fstream>
#include <stdexcept>

Matrix readMatrix(std::ifstream& inputFile) {
    Matrix m;
    if (!(inputFile >> m.rows >> m.cols)) {
        throw std::runtime_error("Failed to read dimensions");
    }
    m.data.resize(m.rows * m.cols);
    for (int i = 0; i < m.rows * m.cols; ++i) {
        if (!(inputFile >> m.data[i])) {
            throw std::runtime_error("Unexpected end of file while reading matrix data");
        }
    }
    return m;
}

Matrix addMatrices(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols) {
        throw std::runtime_error("Matrix dimensions do not match for addition");
    }
    Matrix result = {A.rows, A.cols, std::vector<double>(A.rows * A.cols)};
    for (size_t i = 0; i < A.data.size(); ++i) {
        result.data[i] = A.data[i] + B.data[i];
    }
    return result;
}

void writeMatrix(const Matrix& result, std::ostream& out) {
    out << result.rows << " " << result.cols << "\n";
    for (int i = 0; i < result.rows; ++i) {
        for (int j = 0; j < result.cols; ++j) {
            out << result.data[i * result.cols + j] << (j == result.cols - 1 ? "" : " ");
        }
        out << "\n";
    }
}
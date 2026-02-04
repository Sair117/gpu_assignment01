#include <cuda_runtime.h>
#include <iostream>
#include <stdexcept>
#include "matrix_ops.h"
#include <fstream>

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

__global__ void matrixAddKernel(const double* A, const double* B, double* C, int size) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < size) {
        C[idx] = A[idx] + B[idx]; 
    }
}

void gpuMatrixAdd(const Matrix& h_A, const Matrix& h_B, Matrix& h_C) {
    int size = h_A.rows * h_A.cols;
    size_t bytes = size * sizeof(double);

    double *d_A, *d_B, *d_C;

    // 1. Allocate GPU Memory
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    // 2. Copy data from CPU to GPU
    cudaMemcpy(d_A, h_A.data.data(), bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B.data.data(), bytes, cudaMemcpyHostToDevice);

    // 3. Define Execution Configuration
    int threadsPerBlock = 256;
    int blocksPerGrid = (size + threadsPerBlock - 1) / threadsPerBlock;

    // 4. Launch Kernel on RTX 2050
    matrixAddKernel<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, size);

    // 5. Copy result back to CPU
    cudaMemcpy(h_C.data.data(), d_C, bytes, cudaMemcpyDeviceToHost);

    // 6. Free GPU Memory
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
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
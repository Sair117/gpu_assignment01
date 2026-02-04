#include <iostream>
#include <fstream>
#include <chrono> 
#include "matrix_ops.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file> [output_file]" << std::endl;
        return 1;
    }

    try {
        std::ifstream inFile(argv[1]);
        if (!inFile) throw std::runtime_error("Could not open input file");

        Matrix A = readMatrix(inFile);
        Matrix B = readMatrix(inFile);
        
        auto start = std::chrono::high_resolution_clock::now();
        Matrix C = addMatrices(A, B);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> cpu_time = end - start;
        std::cout << cpu_time.count(); 

        if (argc > 2) {
            std::ofstream outFile(argv[2]);
            if (!outFile) throw std::runtime_error("Could not open output file");
            writeMatrix(C, outFile);
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
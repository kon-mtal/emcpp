#include <iostream>

#include "Matrix.h"

#include <vector>

Matrix::Matrix() {
    std::cout << "default constructor of matrix" << std::endl;
    N = 0; M = 0;
    data = nullptr;
}

Matrix::Matrix(size_t N, size_t M) : N(N), M(M), data(new double[N * M]) {
    std::cout << "constructor of " << N << "x" << M << " matrix" << std::endl;
    std::fill_n(data, N*M, 0);
}

Matrix::Matrix(const std::initializer_list<std::initializer_list<double>> init) {
    size_t maxcols = 0;
    for (auto el: init) {
        maxcols = std::max(maxcols, el.size());
    }

    N = init.size(); M = maxcols;
    std::cout << "constructor of " << N << "x" << M << " matrix from initializer_list" << std::endl;
    data = new double[N * M];

    for (size_t r = 0; r < init.size(); ++r) {
        const auto& row = *(init.begin() + r);
        std::copy(row.begin(), row.end(), data + r * M);
        std::fill(data + r * M + row.size(), data + r * M + maxcols, 0);
    }
}

Matrix::~Matrix() {
    std::cout << "destructor " << label << std::endl;
    delete[] data;
}

Matrix::Matrix(const Matrix& other) : N(other.N), M(other.M) {
    std::cout << "copy constructor" << std::endl;
    if (&other == this) { return; }

    data = new double[N * M];
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            std::copy(other.data + i * M, other.data + (i + 1) * M, data + i * M);
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    std::cout << "copy assignment operator" << std::endl;
    if (&other == this) { return *this; }

    delete[] data;
    N = other.N, M = other.M;
    data = new double[N * M];
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < M; ++j) {
            std::copy(other.data + i * M, other.data + (i + 1) * M, data + i * M);
        }
    }

    return *this;
}

double Matrix::operator()(size_t r, size_t c) const {
    //std::cout << "() operator" << std::endl;
    return *(data + r * M + c);
}

Matrix::Matrix(Matrix && other) noexcept : N(other.N), M(other.M) {
    std::cout << "move constructor" << std::endl;
    if (&other == this) { return; }
    this->data = other.data;
    other.data = nullptr;
}

Matrix& Matrix::operator=(Matrix && other) noexcept {
    std::cout << "move assignment operator" << std::endl;
    if (&other == this) { return *this; }
    this->N = other.N;
    this->M = other.M;
    this->data = other.data;
    other.data = nullptr;
    return *this;
}

Matrix Matrix::operator-() const {
    //std::cout << "- operator" << std::endl;
    Matrix returned = Matrix(this->N, this->M);
    for (size_t i = 0; i < N * M; ++i) {
        *(returned.data + i) = -*(this->data + i);
    }
    return returned;
}

MatrixWithLabel::MatrixWithLabel(
        std::string label,
        const size_t numberOfRows,
        const size_t numberOfColumns)
: Matrix(numberOfRows, numberOfColumns), label(std::move(label)) {}

MatrixWithLabel::MatrixWithLabel(
        std::string label,
        const std::initializer_list<std::initializer_list<double>> init)
: Matrix(init), label(std::move(label)) {}

void MatrixWithLabel::setLabel(std::string _label) {
    this->label = std::move(_label);
}

std::string MatrixWithLabel::getLabel() {
    return label;
}

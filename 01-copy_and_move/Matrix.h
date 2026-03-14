#pragma once
#include <iostream>

class Matrix {
    size_t N, M;
    double* data;

public:
    std::string label = "default";

    Matrix();
    Matrix(size_t, size_t);
    Matrix(std::initializer_list<std::initializer_list<double>> init);

    ~Matrix();
    Matrix(const Matrix&);
    Matrix& operator=(const Matrix &);
    Matrix(Matrix&&) noexcept;
    Matrix& operator=(Matrix &&) noexcept ;

    double operator()(size_t, size_t) const;
    Matrix operator-() const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        os << "{";
        size_t i;
        for (i = 0; i < m.N * m.M - 1; ++i) {
            os << *(m.data + i) << ", ";
        }
        os << *(m.data + i) << "}" << std::endl;
        return os;
    }
};

class MatrixWithLabel : Matrix {
    std::string label = "A";

    using Matrix::Matrix;

public:
    MatrixWithLabel(std::string, size_t, size_t);
    MatrixWithLabel(std::string, std::initializer_list<std::initializer_list<double>>);

    void setLabel(std::string);
    std::string getLabel();
};

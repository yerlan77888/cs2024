#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

template <typename T, size_t Rows, size_t Cols>
class Matrix {
private:
    std::vector<std::vector<T>> data;

public:
    Matrix() : data(Rows, std::vector<T>(Cols, T())) {}

    // Getter for the matrix size
    constexpr size_t getRows() const { return Rows; }
    constexpr size_t getCols() const { return Cols; }

    // Matrix Transposition
    Matrix<T, Cols, Rows> transpose() const {
        Matrix<T, Cols, Rows> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(j, i) = data[i][j];
            }
        }
        return result;
    }

    // Element Access
    T& operator()(size_t row, size_t col) {
        assert(row < Rows && col < Cols);
        return data[row][col];
    }

    const T& operator()(size_t row, size_t col) const {
        assert(row < Rows && col < Cols);
        return data[row][col];
    }

    // Matrix Addition
    Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    // Matrix Subtraction
    Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = data[i][j] - other(i, j);
            }
        }
        return result;
    }

    // Scalar Multiplication
    Matrix<T, Rows, Cols> operator*(const T& scalar) const {
        Matrix<T, Rows, Cols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                result(i, j) = data[i][j] * scalar;
            }
        }
        return result;
    }

    // Matrix Multiplication
    template <size_t OtherCols>
    Matrix<T, Rows, OtherCols> operator*(const Matrix<T, Cols, OtherCols>& other) const {
        Matrix<T, Rows, OtherCols> result;
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < OtherCols; ++j) {
                for (size_t k = 0; k < Cols; ++k) {
                    result(i, j) += data[i][k] * other(k, j);
                }
            }
        }
        return result;
    }

    // Print Matrix
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& matrix) {
        for (size_t i = 0; i < Rows; ++i) {
            for (size_t j = 0; j < Cols; ++j) {
                os << matrix(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }
};

// Specialization for vectors (size, 1)
template <typename T, size_t Rows>
class Matrix<T, Rows, 1> {
private:
    std::vector<std::vector<T>> data;

public:
    Matrix() : data(Rows, std::vector<T>(1, T())) {}

    // Getter for the matrix size
    constexpr size_t getRows() const { return Rows; }
    constexpr size_t getCols() const { return 1; }

    // Element Access
    T& operator()(size_t row) {
        assert(row < Rows);
        return data[row][0];
    }

    const T& operator()(size_t row) const {
        assert(row < Rows);
        return data[row][0];
    }

    // Vector Addition
    Matrix<T, Rows, 1> operator+(const Matrix<T, Rows, 1>& other) const {
        Matrix<T, Rows, 1> result;
        for (size_t i = 0; i < Rows; ++i) {
            result(i) = data[i][0] + other(i);
        }
        return result;
    }

    // Vector Subtraction
    Matrix<T, Rows, 1> operator-(const Matrix<T, Rows, 1>& other) const {
        Matrix<T, Rows, 1> result;
        for (size_t i = 0; i < Rows; ++i) {
            result(i) = data[i][0] - other(i);
        }
        return result;
    }

    // Scalar Multiplication
    Matrix<T, Rows, 1> operator*(const T& scalar) const {
        Matrix<T, Rows, 1> result;
        for (size_t i = 0; i < Rows; ++i) {
            result(i) = data[i][0] * scalar;
        }
        return result;
    }

    // Vector Dot Product
    T operator*(const Matrix<T, Rows, 1>& other) const {
        T result = 0;
        for (size_t i = 0; i < Rows; ++i) {
            result += data[i][0] * other(i);
        }
        return result;
    }

    // Vector L2 Norm
    double norm() const {
        T result = *this * *this;
        return std::sqrt(static_cast<double>(result));
    }

    // Print Vector
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, 1>& vector) {
        for (size_t i = 0; i < Rows; ++i) {
            os << vector(i) << "\n";
        }
        return os;
    }
};

int main() {
    // Example usage for a matrix
    Matrix<int, 2, 3> matrix1;
    matrix1(0, 0) = 1; matrix1(0, 1) = 2; matrix1(0, 2) = 3;
    matrix1(1, 0) = 4; matrix1(1, 1) = 5; matrix1(1, 2) = 6;

    Matrix<int, 3, 2> matrix2;
    matrix2(0, 0) = 7; matrix2(0, 1) = 8;
    matrix2(1, 0) = 9; matrix2(1, 1) = 10;
    matrix2(2, 0) = 11; matrix2(2, 1) = 12;

    Matrix<int, 2, 2> result = matrix1 * matrix2;

    std::cout << "Matrix 1:\n" << matrix1 << "\n";
    std::cout << "Matrix 2:\n" << matrix2 << "\n";
    std::cout << "Result Matrix:\n" << result << "\n";

    // Example usage for a vector
    Matrix<int, 3, 1> vector1;
    vector1(0) = 1; vector1(1) = 2; vector1(2) = 3;

    Matrix<int, 3, 1> vector2;
    vector2(0) = 4; vector2(1) = 5; vector2(2) = 6;

    Matrix<int, 3, 1> sum = vector1 + vector2;
    double norm = vector1.norm();

    std::cout << "Vector 1:\n" << vector1 << "\n";
    std::cout << "Vector 2:\n" << vector2 << "\n";
    std::cout << "Sum Vector:\n" << sum << "\n";
    std::cout << "L2 Norm of Vector 1: " << norm << "\n";

    return 0;
}

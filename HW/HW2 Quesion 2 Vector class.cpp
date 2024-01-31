#include <iostream>

class Vector {
private:
    double x, y, z;

public:
    // Constructors
    Vector() : x(0.0), y(0.0), z(0.0) {}
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}

    // Getters
    double getX() const { return x; }
    double getY() const { return y; }
    double getZ() const { return z; }

    // Setters
    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }
    void setZ(double newZ) { z = newZ; }

    // Compound assignment and arithmetic operators
    Vector& operator+=(const Vector& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vector& operator-=(const Vector& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vector& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    // Multiplication for scalar product
    double operator*(const Vector& rhs) const {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    // Input and output operators
    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        is >> vec.x >> vec.y >> vec.z;
        return is;
    }
};

// Arithmetic operators for addition and subtraction
Vector operator+(Vector lhs, const Vector& rhs) {
    lhs += rhs;
    return lhs;
}

Vector operator-(Vector lhs, const Vector& rhs) {
    lhs -= rhs;
    return lhs;
}

// Multiplication for scalar and vector product
Vector operator*(Vector vec, double scalar) {
    vec *= scalar;
    return vec;
}

Vector operator*(double scalar, Vector vec) {
    vec *= scalar;
    return vec;
}

int main() {
    Vector vec1(1.0, 2.0, 3.0);
    Vector vec2(4.0, 5.0, 6.0);

    // Addition
    Vector sum = vec1 + vec2;
    std::cout << "Sum: " << sum << std::endl;

    // Subtraction
    Vector diff = vec1 - vec2;
    std::cout << "Difference: " << diff << std::endl;

    // Scalar product
    double scalarProduct = vec1 * vec2;
    std::cout << "Scalar Product: " << scalarProduct << std::endl;

    // Multiplication by a scalar
    Vector scaledVec = vec1 * 2.0;
    std::cout << "Scaled Vector: " << scaledVec << std::endl;

    // Input from user
    Vector userVec;
    std::cout << "Enter a vector (x y z): ";
    std::cin >> userVec;
    std::cout << "Entered Vector: " << userVec << std::endl;

    return 0;
}

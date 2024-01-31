#include <iostream>
#include <vector>

class Vector {
private:
    std::vector<double> elements;

public:
    Vector() = default;
    Vector(const std::vector<double>& elems) : elements(elems) {}

    const std::vector<double>& getElements() const { return elements; }
    void setElements(const std::vector<double>& elems) { elements = elems; }

    Vector& operator+=(const Vector& other) {
        size_t size = std::min(elements.size(), other.elements.size());
        for (size_t i = 0; i < size; ++i) {
            elements[i] += other.elements[i];
        }
        return *this;
    }

    friend Vector operator*(const Vector& vec, double scalar) {
        Vector result = vec;
        for (double& element : result.elements) {
            element *= scalar;
        }
        return result;
    }

    friend double operator*(const Vector& vec1, const Vector& vec2) {
        size_t size = std::min(vec1.elements.size(), vec2.elements.size());
        double result = 0.0;
        for (size_t i = 0; i < size; ++i) {
            result += vec1.elements[i] * vec2.elements[i];
        }
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vec) {
        os << "[";
        for (size_t i = 0; i < vec.elements.size(); ++i) {
            os << vec.elements[i];
            if (i < vec.elements.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        char bracket;
        is >> bracket;
        vec.elements.clear();
        double element;
        while (is >> element) {
            vec.elements.push_back(element);
            char comma;
            is >> comma;
            if (comma == ']') {
                break;
            }
        }
        return is;
    }
};

int main() {
    Vector v1({1, 2, 3});
    Vector v2({4, 5, 6});

    v1 += v2;
    std::cout << "Result after addition: " << v1 << "\n";

    Vector scaled = v1 * 2.5;
    std::cout << "Result after scaling: " << scaled << "\n";

    double dotProduct = v1 * v2;
    std::cout << "Dot product: " << dotProduct << "\n";
    return 0;
}

#include <iostream>

template <int n, int k>
struct SumSequence {
    static const int value = n + SumSequence<n, k - 1>::value * n;
};

template <int n>
struct SumSequence<n, 0> {
    static const int value = 0;
};

int main() {
    const int result = SumSequence<2, 3>::value; // Change the values of n and k as needed
    std::cout << "The sum of the sequence F(n, k) is: " << result << std::endl;

    return 0;
}

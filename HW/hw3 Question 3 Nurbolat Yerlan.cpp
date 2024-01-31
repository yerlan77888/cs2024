#include <iostream>

// Meta-function to remove const from a type
template <typename T>
struct RemoveConst {
    using type = T;
};

template <typename T>
struct RemoveConst<const T> {
    using type = T;
};

// Meta-function to remove reference from a type
template <typename T>
struct RemoveReference {
    using type = T;
};

template <typename T>
struct RemoveReference<T&> {
    using type = T;
};

// Example usage
int main() {
    using OriginalType = const int&;
    
    // Remove const
    using WithoutConst = RemoveConst<OriginalType>::type;
    std::cout << "Without Const: " << typeid(WithoutConst).name() << std::endl;

    // Remove reference
    using WithoutReference = RemoveReference<WithoutConst>::type;
    std::cout << "Without Reference: " << typeid(WithoutReference).name() << std::endl;

    return 0;
}

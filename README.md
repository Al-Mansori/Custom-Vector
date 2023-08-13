# MAVector - Custom Vector Class

The `MAVector` is a custom C++ vector class that provides a similar interface to the standard `std::vector`. It is designed to dynamically manage and manipulate a sequence of elements of a given type. This class aims to offer basic functionalities commonly found in vectors, such as dynamic resizing, inserting, erasing, and comparison operations.

## Features

- Dynamic resizing to accommodate new elements.
- Efficient memory management to minimize reallocation.
- Element insertion at a specified position.
- Element erasure by range or single element.
- Supports various comparison operations.
- Compatible with standard algorithms.
- User-defined element type support.

## Usage

1. Include the `MAVector` header in your C++ code:

```cpp
#include "MAVector.hpp"
```

2. Create an instance of `MAVector` with a specified type:

```cpp
MAVector<int> intVector;
MAVector<string> stringVector;
```

3. Use the provided methods to manage and manipulate the vector:

```cpp
intVector.push_back(5);
stringVector.push_back("Hello");
intVector.pop_back();
stringVector.insert(stringVector.begin(), "World");
stringVector.erase(stringVector.begin());
// ... and more
```

## Important Methods and Operations

- `push_back(const T& val)`: Adds an element to the end of the vector.
- `pop_back()`: Removes the last element and returns it.
- `insert(iterator t1, const T& val)`: Inserts an element before the specified iterator.
- `erase(iterator t1, iterator t2)`: Removes elements in the range [t1, t2).
- `erase(iterator t1)`: Removes the element at the specified iterator.
- `begin()`: Returns an iterator to the beginning of the vector.
- `end()`: Returns an iterator to the end of the vector.
- `operator<`, `operator>`, `operator==`: Comparison operations.
- `operator<<`: Stream insertion operator for printing the vector.

## Notes

- This custom vector class provides a subset of the functionalities offered by the `std::vector` class in the C++ Standard Library.
- While the class aims to provide similar functionalities, it may not be as fully optimized or thoroughly tested as the standard library implementation.

## Example

```cpp
#include <iostream>
#include "MAVector.hpp"

int main() {
    MAVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    MAVector<int>::iterator it = vec.begin();
    it++;

    vec.insert(it, 15);
    vec.erase(vec.begin());

    std::cout << "Vector Contents:\n" << vec;

    return 0;
}
```

---

**Note**: This custom vector class is intended for educational purposes and demonstrates the basic principles of managing dynamic arrays in C++. It may not cover all possible edge cases or optimizations found in the standard library implementation. Use the C++ Standard Library's `std::vector` for production code.

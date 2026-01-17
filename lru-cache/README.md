# C++ High-Performance LRU Cache

A modern, header-only Least Recently Used (LRU) Cache implementation in C++17. This project focuses on achieving O(1) time complexity for all operations using a combination of a hash map and a doubly linked list, optimized with `std::list::splice`.

## ✨ Features

- **Header-only**: Zero-dependency, easy to integrate.
- **$O(1)$ Efficiency**: Constant time for both `get` and `put` operations.
- **Optimal Movement**: Utilizes std::list::splice for $O(1)$ node relocation without memory copying.
- **Type-Safe API**: Uses std::optional for get operations to distinguish between "missing" and "default" values.
- **Exception Safe**: Robust error handling, including capacity validation.
- **Modern C++**: Clean, template-based implementation compliant with C++17 standards.

## 🚀 Usage

```cpp
#include "ring_buffer.hpp"
#include <iostream>

int main() {
    RingBuffer<int> rb(3);
    rb.push(1);
    rb.push(2);

    std::cout << *rb.pop() << std::endl; // Output: 1
    return 0;
}
```

## 🛠 Build and Test

This project uses CMake and GoogleTest (fetched automatically via FetchContent).

```bash
mkdir build && cd build
cmake ..
cmake --build .
./run_tests
```

## 📊 Test Coverage

Achieved 100.0% line and function coverage.

```bash
# To generate coverage report (requires lcov)
lcov --capture --directory . --output-file coverage.info --ignore-errors format,inconsistent,category
lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/v1/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory out --ignore-errors inconsistent,category
open out/index.html
```

## ⚖️ License
MIT License
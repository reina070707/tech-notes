# C++ Thread-Safe Ring Buffer

A modern, header-only, thread-safe circular buffer implementation in C++17.
Developed with a focus on performance, move semantics, and 100% test coverage.

## ✨ Features

- **Header-only**: Easy to integrate into any project.
- **Thread-safe**: Protected by `std::mutex` for multi-threaded environments.
- **Move Semantics**: Supports move-only types like `std::unique_ptr`.
- **RAII Compliant**: Uses modern C++ standards for memory management.
- **High Reliability**: 100% line and function coverage verified by GoogleTest & LCOV.

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
lcov --capture --directory . --output-file coverage.info --ignore-errors inconsistent,category
genhtml coverage_filtered.info --output-directory out --ignore-errors inconsistent,category
```

## ⚖️ License
MIT License
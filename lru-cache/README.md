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
#include "lru-cache.hpp"
#include <iostream>
#include <string>

int main() {
    // Instantiate with a capacity of 2
    LRUCache<int, std::string> cache(2);

    cache.put(1, "one");
    cache.put(2, "two");

    // Accessing an element makes it "most recently used"
    if (auto val = cache.get(1)) {
        std::cout << "Found: " << *val << std::endl; // Output: one
    }

    // This will evict key 2 because key 1 was recently accessed
    cache.put(3, "three");

    if (!cache.get(2)) {
        std::cout << "Key 2 was evicted." << std::endl;
    }

    return 0;
}
```

## ✅ Robustness Verification (Typed Tests)

Using GoogleTest's **Type-Parameterized Tests**, the core logic is verified against multiple data types to ensure template reliability:

- **Primitives**: `int` (Ensures zero-overhead for simple types).
- **Heap-Allocated**: `std::string` (Ensures correct resource management).
- **Complex Containers**: `std::vector<int>` (Ensures safety with move semantics and RAII).

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
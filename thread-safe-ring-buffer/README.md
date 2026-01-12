# tech-notes 🧪
### **Bridging Applied Mathematics with Mission-Critical Software**

Welcome to my technical laboratory. This repository is a collection of high-performance data structures, architectural patterns, and algorithmic experiments, specifically designed for **autonomous robotics** and **real-time systems**.

---

## 🚀 Featured Project: High-Performance Thread-Safe Ring Buffer

My primary focus is a modern C++ implementation of a Ring Buffer that achieves maximum throughput by leveraging mathematical properties.

### 🔹 Mathematical Optimization: The Modulo Trick
To eliminate the high CPU cost of the modulo operator (`%`), I utilize a bitwise AND mask for index management. This reduces the increment operation from ~20-40 CPU cycles to **exactly 1 cycle**.

> **Optimization Formula**:
> `index = (index + 1) & (capacity - 1)`

> **Design Choice**: To ensure this optimization is always valid, the constructor automatically rounds up the requested capacity to the nearest power of 2 ($2^n$) using C++20's `std::bit_ceil`.

### 🔹 Technical Specifications
- **Concurrency**: Zero-busy-wait synchronization using `std::condition_variable_any`.
- **Interruptible**: Integrated `std::stop_token` (C++20) for graceful shutdowns in multi-threaded environments.
- **Efficiency**: Full support for **Move Semantics** and **RAII** to ensure zero-copy overhead.
- **Quality**: **100% Test Coverage** using GoogleTest and LCOV.


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
lcov --remove coverage.info '/usr/*' '*/_deps/*' '*/v1/*' --output-file coverage_filtered.info
genhtml coverage_filtered.info --output-directory out --ignore-errors inconsistent,category
open out/index.html
```

---

## ⚖️ License
MIT License
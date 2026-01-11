# tech-notes 🧪
### **Bridging Applied Mathematics with Mission-Critical Software**

Welcome to my technical laboratory. This repository is a collection of high-performance data structures, architectural patterns, and algorithmic experiments, specifically designed for **autonomous robotics** and **real-time systems**.

---

## 🚀 Featured Project: High-Performance Thread-Safe Ring Buffer

My primary focus is a modern C++ implementation of a Ring Buffer that achieves maximum throughput by leveraging mathematical properties.

### 🔹 Mathematical Optimization: The Modulo Trick
To eliminate the high CPU cost of the modulo operator (`%`), I utilize a bitwise AND mask for index management. This reduces the increment operation from ~20-40 CPU cycles to **exactly 1 cycle**.



$$index = (index + 1) \& (capacity - 1)$$

> **Design Choice**: To ensure this optimization is always valid, the constructor automatically rounds up the requested capacity to the nearest power of 2 ($2^n$) using C++20's `std::bit_ceil`.

### 🔹 Technical Specifications
- **Concurrency**: Zero-busy-wait synchronization using `std::condition_variable_any`.
- **Interruptible**: Integrated `std::stop_token` (C++20) for graceful shutdowns in multi-threaded environments.
- **Efficiency**: Full support for **Move Semantics** and **RAII** to ensure zero-copy overhead.
- **Quality**: Target **100% Test Coverage** using GoogleTest and LCOV.

---

## 📊 Roadmap & Active Research

| Topic | Key Concept | Status | Implementation |
| :--- | :--- | :--- | :--- |
| **Ring Buffer** | Bitwise Logic & $2^n$ Alignment | ✅ Complete | [View Code](./thread-safe-ring-buffer.hpp) |
| **LRU Cache** | $O(1)$ Hash-Map & Doubly Linked List | 🚧 In Progress | *Coming Soon* |
| **Applied Math** | Numerical Analysis & Kalman Filters | 📅 Planned | - |

---

## 🔧 Environment & "Spec"
- **Language**: Modern C++ (C++20), Python, Rust
- **Tools**: CMake, GoogleTest, GitHub Actions, LCOV, Docker
- **Hardware**: ThinkPad P14s (64GB RAM), Ubuntu/ROS2

---

## 👋 About the Author
**Reina Hirata (平田 令納)**
- **M.S. in Applied Mathematics** (Waseda University).
- **Incoming Lead Software Engineer in Test** at a Robotics company (March 2026).
- **"Jaja-uma (Unconventional)" Engineer**: A pink-haired mom of three (151.4cm tall) who bridges the gap between impeccable logic and the passionate chaos of real-world implementation.

[<img src="https://img.shields.io/badge/LinkedIn-Connect-blue?style=flat&logo=linkedin">](https://www.linkedin.com/in/reina-hirata-293b57115/) &nbsp; [<img src="https://img.shields.io/badge/LAPRAS-Portfolio-42C4C2?style=flat">](https://lapras.com/public/reinahirata07)

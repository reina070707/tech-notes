# tech-notes 🧪
**The Design Lab of a Mathematical Software Engineer**

This repository serves as my personal technical laboratory. Here, I document deep dives into data structures, architectural patterns, and performance optimizations, bridging the gap between **Applied Mathematics** and **Mission-Critical Software**.

---

## 🔬 Focus Areas
- **Algorithmic Efficiency:** Analyzing time/space complexity with mathematical rigor.
- **Modern C++ Design:** Exploring C++17/20 features for robust robotics software.
- **System Architecture:** Designing for thread-safety, low-latency, and high-reliability.
- **Robotics & Space Tech:** Domain-specific notes on autonomous systems and satellite data.

---

## 📂 Active Research & Implementations

| Topic | Key Concept | Implementation / Note |
| :--- | :--- | :--- |
| **Ring Buffer** | Bitwise optimization & $2^n$ capacity | [View Code](./ring-buffer/ring_buffer.hpp) |
| **Concurrency** | **Waitable Pattern** via `std::condition_variable` | [View Code](./thread-safe-ring-buffer/thread-safe-ring-buffer.hpp) |
| **LRU Cache** | $O(1)$ Hash-Map & List composition | *Coming Soon* |
| **Applied Math** | Numerical analysis for sensor fusion | *Planned* |

### 🚀 Highlight: Optimized Ring Buffer
My recent implementation of a Ring Buffer utilizes bitwise AND for index incrementing:
$$index = (index + 1) \& (capacity - 1)$$
This optimization requires the capacity to be a power of 2 ($2^n$), significantly reducing CPU cycles by avoiding the modulo (%) operator.

### 💡 Highlight: Thread-Safe Synchronization
Beyond algorithmic speed, I implemented a **Waitable Ring Buffer** that eliminates CPU-heavy busy-waiting. By utilizing `std::condition_variable`, threads remain in a suspended state until data is available, ensuring optimal resource management—a critical pattern for power-constrained robotics systems.

---

## 🛠 My "Spec" (Environment)
- **Machine:** ThinkPad P14s Gen 6 (64GB RAM)
- **Editor:** Neovim / VSCode + LSP (clangd)
- **OS:** Linux (Ubuntu) / macOS

---

## 🌸 About the Author
- **Reina Hirata**
- M.S. in Applied Mathematics (Waseda Univ.)
- Incoming Lead Software Engineer in Test at Robotics company (March 2026)

---
[<img src="https://img.shields.io/badge/LinkedIn-Connect-blue?style=flat&logo=linkedin">](https://www.linkedin.com/in/reina-hirata-293b57115) &nbsp; [<img src="https://img.shields.io/badge/LAPRAS-Score-42C4C2?style=flat">](https://lapras.com/public/reinahirata07) &nbsp; [<img src="https://img.shields.io/badge/Algorithm_Daily-Repo-green?style=flat&logo=github">](../algorithm-daily)
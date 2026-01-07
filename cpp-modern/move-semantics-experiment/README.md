# Tech Notes: C++ Move Semantics & Memory Efficiency

## 📌 Context
This repository contains a series of technical experiments conducted during my transition into the **Robotics** field. 

Inspired by a recent deep dive into the "Ring Buffer" implementation, these notes focus on optimizing data transfer by mastering Modern C++ memory management.

## 🧪 Experiment: Move Semantics (`&` vs `&&`)
This experiment visualizes the difference between **Copying** and **Moving** data in C++.

### Key Concepts
* **L-value Reference (`&`)**: Used for persistent objects. Requires a "Copy" operation which can be expensive for large data.
* **R-value Reference (`&&`)**: Used for temporary objects. Allows "Moving" resources instead of copying.
* **`std::move`**: Casts an L-value to an R-value to enable move semantics.
* **`std::forward`**: Preserves the value category (Perfect Forwarding) when passing arguments through templates.



### Why it matters for Robotics
In robotics development, we handle high-frequency sensor data and large camera frames. Constantly copying these buffers would lead to:
1.  **Latency**: Slower response times for the robot.
2.  **Memory Overhead**: High CPU/Memory usage.

By using **Move Semantics**, we ensure zero-copy data transfer, maintaining the performance required for real-time systems.

## 📊 Result
In `main.cpp`, the `push_move` test demonstrates that:
- Before move: The string contains "Katsushika Robotics".
- After move: The original string becomes empty `[]`, and the data is successfully "stolen" by the internal buffer with near-zero cost.

## 🛠 How to Run
```bash
g++ -std=c++17 main.cpp -o experiment
./experiment

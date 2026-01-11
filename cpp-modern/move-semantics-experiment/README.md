# Tech Notes: C++ Move Semantics & Memory Efficiency

## 📌 Context
This repository contains a series of technical experiments conducted during my transition into the **Robotics** field. 

For a conceptual deep dive into why move semantics are essential, please refer to my viral article on Zenn (Japanese):
👉 **[Understanding Move Semantics: The "Moving" Metaphor](https://zenn.dev/reinahirata07/articles/a43a0449f2657a)**

## 🧪 Experiment: Move Semantics (`&` vs `&&`)
This experiment visualizes the difference between **Copying** and **Moving** data in C++.

### Key Concepts
* **L-value Reference (`&`)**: "Protecting the original while showing it."
* **R-value Reference (`&&`)**: "Taking over the original for efficient reuse."
* **`std::move`**: Casts an L-value to an R-value to enable move semantics.
* **`std::forward`**: Preserves the value category (Perfect Forwarding).

### Why it matters for Robotics
In robotics development, we handle high-frequency sensor data and large camera frames. Constantly copying these buffers would lead to:
1.  **Latency**: Slower response times for the robot's control loop.
2.  **Memory Overhead**: Unnecessary CPU/Memory pressure.

By using **Move Semantics**, we ensure **zero-copy data transfer**, maintaining the performance required for real-time systems.

## 📊 Result
In `main.cpp`, the `push_move` test demonstrates:
- **Before move**: String contains `"Robotics"`.
- **After move**: The original string becomes empty `[]`, and the data is successfully "stolen" by the internal buffer with near-zero cost.

## 🛠 How to Run
```bash
g++ -std=c++20 main.cpp -o experiment
./experiment
```

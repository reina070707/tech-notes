#include <iostream>
#include <string>
#include <vector>
#include <utility> // std::move のため

// 1. for copying, handle with care（const &）
void push_copy(const std::string& val) {
    std::string internal_buffer = val; // 複製を作る
    std::cout << "  [Inside copy] Value: " << internal_buffer << std::endl;
}

// 2. for moving, data will be stolen（&&）
void push_move(std::string&& val) {
    std::string internal_buffer = std::move(val); // stole!
    std::cout << "  [Inside move] Value: " << internal_buffer << std::endl;
}

int main() {
    std::string my_data = "Katsushika Robotics";

    // --- experiment 1: copy ---
    std::cout << "--- Experiment 1: Copy ---" << std::endl;
    std::cout << "Before push_copy: " << my_data << std::endl;
    
    push_copy(my_data); // it has the address. L-value reference
    
    std::cout << "After  push_copy: " << my_data << " (Still here!)" << std::endl << std::endl;

    // --- experiment 2: move ---
    std::cout << "--- Experiment 2: Move ---" << std::endl;
    std::cout << "Before push_move: " << my_data << std::endl;
    
    // std::move(my_data) is a sign that this data is no need.
    push_move(std::move(my_data)); 
    
    std::cout << "After  push_move: [" << my_data << "] (Empty! Data was stolen!)" << std::endl;

    return 0;
}
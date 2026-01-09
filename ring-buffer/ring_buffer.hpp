#ifndef RING_BUFFER_HPP
#define RING_BUFFER_HPP

#include <vector>
#include <optional>
#include <mutex>
#include <stdexcept>

template <typename T>
class RingBuffer {
    std::size_t capacity;
    std::size_t readIndex; // tail
    std::size_t writeIndex; // head
    std::size_t count;
    std::vector<T> buffer;
    mutable std::mutex mtx_;

    // helper function for push()
    template <typename U>
    void push_impl(U&& val) {
        std::lock_guard<std::mutex> lock(mtx_);

        buffer[writeIndex] = std::forward<U>(val);
        writeIndex = (writeIndex + 1) % capacity; // count up

        if (count < capacity) {
            count++;
        } else {
            // also count up when full
            readIndex = (readIndex + 1) % capacity;
        }
    }

public:
    explicit RingBuffer(const std::size_t size) : capacity(size), readIndex(0), writeIndex(0), count(0) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
        buffer.resize(capacity);
    }

    // L-value copy (left reference)
    void push(const T& val) {
        push_impl(val);
    }

    // R-value move (right reference)
    void push(T&& val) {
        push_impl(std::move(val));
    }

    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mtx_);
        if (count == 0) return std::nullopt;

        T val = std::move(buffer[readIndex]);
        readIndex = (readIndex + 1) % capacity; // count up
        count--;
        return val;
    }

    bool is_empty() const { std::lock_guard<std::mutex> lock(mtx_); return count == 0; }
    bool is_full() const { std::lock_guard<std::mutex> lock(mtx_); return count >= capacity; }
    std::size_t size() const { std::lock_guard<std::mutex> lock(mtx_); return count; }
};

#endif // RING_BUFFER_HPP
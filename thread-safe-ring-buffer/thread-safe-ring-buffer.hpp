#include <bit>
#include <stdexcept>
#include <mutex>
#include <condition_variable>
#include <optional>
#include <stop_token>
#include <vector>

template <typename T>
class ThreadSafeRingBuffer {
private:
    std::vector<T> buffer_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;
    size_t capacity_;

    std::mutex mtx_;
    std::condition_variable_any cond_;

public:
    explicit ThreadSafeRingBuffer(size_t cap) : capacity_(cap) {
        if (capacity_ == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }

        // Automatically round up 'cap' to the nearest power of 2
        // e.g., 10 -> 16, 100 -> 128, 1024 -> 1024
        capacity_ = std::bit_ceil(cap);

        buffer_.resize(capacity_);
    }

    void push(T item) {
        std::lock_guard<std::mutex> lock(mtx_);

        buffer_[tail_] = std::move(item);
        tail_ = (tail_ + 1) & (capacity_ - 1);
        size_++;

        // notify
        cond_.notify_one();
    }

    std::optional<T> wait_and_pop(std::stop_token st = {}) {
        std::unique_lock<std::mutex> lock(mtx_);

        // waiting for a value pushed
        bool success = cond_.wait(lock, st, [this] { return size_ > 0; });

        if (!success || st.stop_requested()) return std::nullopt;

        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) & (capacity_ - 1);
        size_--;
        return value;
    }
};

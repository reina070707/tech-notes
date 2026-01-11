#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class ThreadSafeRingBuffer {
private:
    std::vector<T> buffer_;
    size_t head_ = 0;
    size_t tail_ = 0;
    size_t size_ = 0;
    size_t capacity_;

    std::mutex mtx_;
    std::condition_variable cond_;

public:
    explicit ThreadSafeRingBuffer(size_t cap) : capacity_(cap) {
        buffer_.resize(cap);
    }

    void push(T item) {
        std::lock_guard<std::mutex> lock(mtx_);

        buffer_[tail_] = std::move(item);
        tail_ = (tail_ + 1) % capacity_;
        size_++;

        // notify
        cond_.notify_one();
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(mtx_);

        // waiting for a value pushed
        cond_.wait(lock, [this] { return size_ > 0; });

        value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % capacity_;
        size_--;
    }
};

#include <cstddef> // size_t用
#include <optional>
#include <vector>

template <typename T>
class RingBuffer {
    std::size_t capacity;
    std::size_t readIndex; // tail
    std::size_t writeIndex; // head
    std::size_t count;
    std::vector<T> buffer;

public:
    RingBuffer(const std::size_t size) : capacity(size), readIndex(0), writeIndex(0), count(0) {
        assert((size > 0) && ((size & (size - 1)) == 0) && "Capacity must be a power of 2");
        buffer.resize(capacity);
    }

    bool push(const T& val) {
        if (count >= capacity) return false;

        buffer[writeIndex] = val;
        writeIndex = (writeIndex + 1) & (capacity - 1); // count up
        count++;
        return true;
    }

    std::optional<T> pop() {
        if (count <= 0) return std::nullopt;

        T val = buffer[readIndex];
        readIndex = (readIndex + 1) & (capacity - 1); // count up
        count--;
        return val;
    }

    bool is_empty() const { return count == 0; }
    bool is_full() const { return count >= capacity; }
    std::size_t size() const { return count; }
};
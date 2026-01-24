#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <concepts>
#include <list>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <unordered_map>

// concepts of available for hash
template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

template <Hashable K, std::movable V>
class LRUCache {
private:
    size_t capacity_;
    std::list<std::pair<K, V>> items_; // K: key, V: value
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cache_;
    mutable std::mutex mutex_;

public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    std::optional<V> get(const K& key) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = cache_.find(key);
        if (it == cache_.end()) return std::nullopt;

        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }

    void put(const K& key, V value) {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = cache_.find(key);
        if (it != cache_.end()) {
            it->second->second = std::move(value);
            items_.splice(items_.begin(), items_, it->second);
            return;
        }

        if (items_.size() >= capacity_) {
            cache_.erase(items_.back().first);
            items_.pop_back();
        }

        items_.emplace_front(key, std::move(value));
        cache_[key] = items_.begin();
    }
};

#endif // LRU_CACHE_HPP
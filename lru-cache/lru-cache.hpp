#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <stdexcept>
#include <list>
#include <optional>
#include <unordered_map>

template <typename K, typename V>
class LRUCache {
private:
    size_t capacity_;
    std::list<std::pair<K, V>> items_; // K: key, V: value
    std::unordered_map<K, typename std::list<std::pair<K, V>>::iterator> cache_;

public:
    explicit LRUCache(size_t capacity) : capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
    }

    std::optional<V> get(const K& key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) return std::nullopt;

        items_.splice(items_.begin(), items_, it->second);
        return it->second->second;
    }

    void put(const K& key, const V& value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            it->second->second = value;
            items_.splice(items_.begin(), items_, it->second);
            return;
        }

        if (items_.size() >= capacity_) {
            cache_.erase(items_.back().first);
            items_.pop_back();
        }

        items_.emplace_front(key, value);
        cache_[key] = items_.begin();
    }
};

#endif // LRU_CACHE_HPP
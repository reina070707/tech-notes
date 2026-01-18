#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include "lru-cache.hpp"

// ==========================================================
// 1. Fixture Definition
// ==========================================================
template <typename T>
class LRUCacheTypedTest : public ::testing::Test {
protected:
    // helper function for each type
    T createValue(int seed) {
        if constexpr (std::is_same_v<T, std::string>) {
            return "value_" + std::to_string(seed);
        } else if constexpr (std::is_same_v<T, std::vector<int>>) {
            return {seed, seed + 1};
        } else {
            return static_cast<T>(seed);
        }
    }
};

using TestTypes = ::testing::Types<int, std::string, std::vector<int>>;
TYPED_TEST_SUITE(LRUCacheTypedTest, TestTypes);

// ==========================================================
// 2. Exception Tests
// ==========================================================
using IntCache = LRUCache<int, int>;

TEST(LRUCacheTest, ConstructorThrow) {
    EXPECT_THROW({
        IntCache cache(0);
    }, std::invalid_argument);
}

TEST(LRUCacheTest, ConstructorNoThrow) {
    EXPECT_NO_THROW({
        IntCache cache(10);
    });
}

// ==========================================================
// 3. Typed Tests (using fixture)
// ==========================================================
// using TestCache = LRUCache<int, std::string>;

TYPED_TEST(LRUCacheTypedTest, BasicPutGet) {
    LRUCache<int, TypeParam> cache(2);
    auto v1 = this->createValue(1);

    cache.put(1, v1);
    auto val = cache.get(1);

    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), v1);
}

TYPED_TEST(LRUCacheTypedTest, GetNonExistentKey) {
    LRUCache<int, TypeParam> cache(2);
    EXPECT_FALSE(cache.get(999).has_value());
}

TYPED_TEST(LRUCacheTypedTest, EvictionLogic) {
    LRUCache<int, TypeParam> cache(2);
    auto v1 = this->createValue(1);
    auto v2 = this->createValue(2);
    auto v3 = this->createValue(3);

    cache.put(1, v1);
    cache.put(2, v2);
    cache.get(1); // update the latest for 1

    cache.put(3, v3); // Should be deleted 2

    EXPECT_TRUE(cache.get(1).has_value());
    EXPECT_FALSE(cache.get(2).has_value());
    EXPECT_TRUE(cache.get(3).has_value());
}

TYPED_TEST(LRUCacheTypedTest, CapacityOne) {
    LRUCache<int, TypeParam> cache(1);
    auto v1 = this->createValue(1);
    auto v2 = this->createValue(2);

    cache.put(1, v1);
    cache.put(2, v2);

    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_EQ(cache.get(2).value(), v2);
}

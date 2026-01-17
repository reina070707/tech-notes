#include <gtest/gtest.h>
#include "lru-cache.hpp"
#include <memory>

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

using TestCache = LRUCache<int, std::string>;

TEST(LRUCacheTest, BasicPutGet) {
    TestCache cache(2);

    cache.put(1, "one");
    auto val = cache.get(1);

    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "one");
}

// 3. Test for not existed key
TEST(LRUCacheTest, GetNonExistentKey) {
    TestCache cache(2);
    auto val = cache.get(999);

    EXPECT_FALSE(val.has_value());
}

// 4. Test for eviction due to capacity
TEST(LRUCacheTest, EvictionLogic) {
    TestCache cache(2);

    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three"); // Should delete one

    EXPECT_FALSE(cache.get(1).has_value()); // deleted one
    EXPECT_TRUE(cache.get(2).has_value());  // reminded two
    EXPECT_TRUE(cache.get(3).has_value());  // reminded three
}

// 5. Test for updating of getter function
TEST(LRUCacheTest, UpdateOrderOnGet) {
    TestCache cache(2);

    cache.put(1, "one");
    cache.put(2, "two");

    // update latest 1
    cache.get(1);

    // Should be deleted two when put three
    cache.put(3, "three");

    EXPECT_TRUE(cache.get(1).has_value());  // keep one
    EXPECT_FALSE(cache.get(2).has_value()); // removed two
    EXPECT_TRUE(cache.get(3).has_value());  // put three
}

// 6. Test for updating existing key
TEST(LRUCacheTest, PutUpdateExistingKey) {
    TestCache cache(2);

    cache.put(1, "old");
    cache.put(1, "new"); // updating value

    auto val = cache.get(1);
    ASSERT_TRUE(val.has_value());
    EXPECT_EQ(val.value(), "new");
}

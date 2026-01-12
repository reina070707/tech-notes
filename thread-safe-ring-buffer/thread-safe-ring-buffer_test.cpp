#include <gtest/gtest.h>
#include "thread-safe-ring-buffer.hpp"
#include <memory>

TEST(ThreadSafeRingBufferTest, ConstructorThrow) {
    EXPECT_THROW({
        ThreadSafeRingBuffer<int> rb(0);
    }, std::invalid_argument);
}

TEST(ThreadSafeRingBufferTest, ConstructorNoThrow) {
    EXPECT_NO_THROW({
        ThreadSafeRingBuffer<int> rb(10);
    });
}

TEST(ThreadSafeRingBufferTest, CapacityCeiledUp) {
    ThreadSafeRingBuffer<int> rb(10);
    EXPECT_EQ(rb.capacity(), 16);
}

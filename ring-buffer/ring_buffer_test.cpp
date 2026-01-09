#include <gtest/gtest.h>
#include "ring_buffer.hpp"
#include <memory>

// Push/Pop
TEST(RingBufferTest, BasicOperations) {
    RingBuffer<int> rb(3);
    rb.push(10);
    rb.push(20);
    EXPECT_EQ(rb.pop(), 10);
    EXPECT_EQ(rb.pop(), 20);
    EXPECT_TRUE(rb.is_empty());
}

TEST(RingBufferTest, MoveSemantics) {
    RingBuffer<std::unique_ptr<int>> rb(2);
    auto p = std::make_unique<int>(42);
    rb.push(std::move(p));

    EXPECT_EQ(p, nullptr);
    auto popped = rb.pop();
    ASSERT_TRUE(popped.has_value());
    EXPECT_EQ(**popped, 42);
}

TEST(RingBufferTest, Overwrite) {
    RingBuffer<int> rb(2);
    rb.push(1);
    rb.push(2);
    rb.push(3); // overwrite happens

    EXPECT_EQ(rb.size(), 2);
    EXPECT_EQ(rb.pop(), 2);
    EXPECT_EQ(rb.pop(), 3);
}
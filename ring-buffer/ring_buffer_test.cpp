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

TEST(RingBufferTest, ConstructorThrow) {
    EXPECT_THROW({
        RingBuffer<int> rb(0);
    }, std::invalid_argument);
}

TEST(RingBufferTest, ConstructorNoThrow) {
    EXPECT_NO_THROW({
        RingBuffer<int> rb(10);
    });
}

TEST(RingBufferTest, Empty) {
    RingBuffer<int> rb(2);
    EXPECT_TRUE(rb.is_empty());
    EXPECT_FALSE(rb.is_full());
    EXPECT_EQ(rb.size(), 0);
    EXPECT_EQ(rb.pop(), std::nullopt);
}

TEST(RingBufferTest, Senario) {
    RingBuffer<std::string> rb(2);

    rb.push("hello");
    rb.push("robotics");

    EXPECT_FALSE(rb.is_empty());
    EXPECT_TRUE(rb.is_full());
    EXPECT_EQ(rb.size(), 2);
    EXPECT_EQ(rb.pop(), "hello");
    EXPECT_EQ(rb.size(), 1);
}

TEST(RingBufferTest, CapacityOne) {
    RingBuffer<int> rb(1);
    rb.push(100);
    EXPECT_EQ(rb.size(), 1);
    rb.push(200); // Overwrite 100
    EXPECT_EQ(rb.pop(), 200);
    EXPECT_TRUE(rb.is_empty());
}

TEST(RingBufferTest, MultiCycle) {
    RingBuffer<int> rb(2);
    for(int i = 0; i < 100; ++i) {
        rb.push(i);
        EXPECT_EQ(rb.pop(), i);
    }
    EXPECT_TRUE(rb.is_empty());
}

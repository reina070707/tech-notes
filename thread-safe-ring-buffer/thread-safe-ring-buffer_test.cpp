#include <gtest/gtest.h>
#include "thread-safe-ring-buffer.hpp"
#include <memory>
#include <thread>
#include <vector>

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

TEST(RingBufferTest, CapacityOne) {
    ThreadSafeRingBuffer<int> rb(1);
    EXPECT_EQ(rb.capacity(), 1);
    rb.push(100);
    EXPECT_EQ(rb.size(), 1);
    rb.push(200); // Overwrite 100
    EXPECT_EQ(rb.wait_and_pop(), 200);
    EXPECT_EQ(rb.size(), 0);
}

TEST(RingBufferTest, MultiCycle) {
    ThreadSafeRingBuffer<int> rb(2);
    for(int i = 0; i < 100; ++i) {
        rb.push(i);
        EXPECT_EQ(rb.wait_and_pop(), i);
    }
    EXPECT_EQ(rb.size(), 0);
}

TEST(ThreadSafeRingBufferTest, CapacityCeiledUp) {
    ThreadSafeRingBuffer<int> rb(10);
    EXPECT_EQ(rb.capacity(), 16);
    EXPECT_EQ(rb.size(), 0);
}

TEST(ThreadSafeRingBufferTest, PushPop) {
    ThreadSafeRingBuffer<int> rb(4);
    rb.push(100);
    rb.push(200);
    EXPECT_EQ(rb.size(), 2);

    EXPECT_EQ(rb.wait_and_pop().value(), 100);
    EXPECT_EQ(rb.wait_and_pop().value(), 200);
    EXPECT_EQ(rb.size(), 0);
}

// verification for move semantics
TEST(ThreadSafeRingBufferTest, MoveSemantics) {
    ThreadSafeRingBuffer<std::unique_ptr<int>> rb(4);
    auto data = std::make_unique<int>(42);

    // check moving
    rb.push(std::move(data));
    EXPECT_EQ(data, nullptr);

    // back the value when pop
    auto popped = rb.wait_and_pop();
    ASSERT_TRUE(popped.has_value());
    EXPECT_EQ(**popped, 42);
}

// multithread, block behavior
TEST(ThreadSafeRingBufferTest, MultiThreadWaitAndPop) {
    ThreadSafeRingBuffer<int> rb(4);
    int result = 4;

    // pop thread
    std::thread consumer([&]() {
        auto val = rb.wait_and_pop();
        if (val) result = (*val);
    });

    // push after sleeping 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    rb.push(999);

    consumer.join();
    EXPECT_EQ(result, 999);
}
#include "list.hpp"
#include <array>
#include <random>
#include <iostream>
#include <gtest/gtest.h>

constexpr auto TEST_SEEDER = 389248924;

template<>
size_t Node<int>::alloc_cnt=0;

#define ASSERT_SIZE(ls, expectedSize) \
    ASSERT_EQ(ls.size(),expectedSize)

#define EXPECT_EMPTY(ls) \
    EXPECT_TRUE(ls.empty())

#define ASSERT_EMPTY(ls) \
    ASSERT_TRUE(ls.empty())

// test cases start from here.
TEST(Empty, Accessors){
    List<int> ls;
    EXPECT_EMPTY(ls);
}

TEST(Empty, CopyConstruct){
    List<int> ls;
    ASSERT_EMPTY(ls);
    List<int> ls2(ls);
    ASSERT_EMPTY(ls);
    EXPECT_EMPTY(ls2);
}


TEST(Empty, Insert){
    int testConst1 = 14;
    List<int> ls;
    ASSERT_EMPTY(ls);
    ls.insert(0,testConst1);
    ASSERT_SIZE(ls,1);
    EXPECT_EQ(ls.front(),testConst1);
    EXPECT_EQ(ls.back(),testConst1);
    EXPECT_EQ(ls.at(0),testConst1);
}

TEST(Empty, PushFront){
    int testConst1 = 31;
    List<int> ls;
    ASSERT_EMPTY(ls);
    ls.push_front(testConst1);
    ASSERT_SIZE(ls,1);
    EXPECT_EQ(ls.front(),testConst1);
    EXPECT_EQ(ls.back(),testConst1);
    EXPECT_EQ(ls.at(0),testConst1);
}

TEST(Empty, PushBack){
    int testConst1 = 42;
    List<int> ls;
    ASSERT_EMPTY(ls);
    ls.push_back(testConst1);
    ASSERT_SIZE(ls,1);
    EXPECT_EQ(ls.front(),testConst1);
    EXPECT_EQ(ls.back(),testConst1);
    EXPECT_EQ(ls.at(0),testConst1);

}

TEST(Empty, Clear){
    List<int> ls;
    ASSERT_EMPTY(ls);

    ls.clear();
    EXPECT_EMPTY(ls);
}
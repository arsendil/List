#include <gtest/gtest.h>
#include "headers/List.hpp"
#include <string>

// ======== Construction & Basic Operations ========
TEST(ListTest, DefaultConstructorIsEmpty)
{
    List<int> lst;
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.size(), 0u);
}

TEST(ListTest, ConstructorWithSizeAndValue)
{
    List<int> lst(5, 42);
    EXPECT_FALSE(lst.empty());
    EXPECT_EQ(lst.size(), 5u);

    for (List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        EXPECT_EQ(*it, 42);
    }
}

TEST(ListTest, CopyConstructor)
{
    List<int> lst1(3, 7);
    List<int> lst2(lst1);
    EXPECT_EQ(lst1.size(), lst2.size());

    List<int>::iterator it1 = lst1.begin();
    List<int>::iterator it2 = lst2.begin();
    for (; it1 != lst1.end() && it2 != lst2.end(); ++it1, ++it2) {
        EXPECT_EQ(*it1, *it2);
    }
}

// ======== Push / Pop ========
TEST(ListTest, PushBackAndIterate)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    int expected = 1;
    for (List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        EXPECT_EQ(*it, expected++);
    }
}

TEST(ListTest, PushFrontWorks)
{
    List<int> lst;
    lst.push_front(10);
    lst.push_front(20);

    EXPECT_EQ(lst.size(), 2u);

    List<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 20);
    ++it;
    EXPECT_EQ(*it, 10);
}

TEST(ListTest, PopBackWorks)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    lst.pop_back();
    EXPECT_EQ(lst.size(), 2u);

    List<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 2);
}

// ======== Resize / Clear ========
TEST(ListTest, ResizeBigger)
{
    List<int> lst(2, 5);
    lst.resize(5, 9);
    EXPECT_EQ(lst.size(), 5u);

    int count9 = 0;
    for (List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        if (*it == 9) count9++;
    }
    EXPECT_EQ(count9, 3);
}

TEST(ListTest, ResizeSmaller)
{
    List<int> lst(5, 1);
    lst.resize(2);
    EXPECT_EQ(lst.size(), 2u);
}

TEST(ListTest, ClearMakesEmpty)
{
    List<int> lst(5, 2);
    lst.clear();
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.size(), 0);
}

// ======== Iterators ========
TEST(ListTest, ConstIteratorTraversal)
{
    const List<int> lst(3, 100);
    int counter = 0;
    for (List<int>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        EXPECT_EQ(*it, 100);
        counter++;
    }
    EXPECT_EQ(counter, 3);
}

TEST(ListTest, ReverseIteratorTraversal)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    int expected = 3;
    for (List<int>::reverse_iterator it = lst.rbegin(); it != lst.rend(); ++it) {
        EXPECT_EQ(*it, expected--);
    }
}

// ======== Basic construction =========
TEST(ListTest, DefaultConstructor)
{
    List<int> lst;
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.size(), 0u);
}

TEST(ListTest, FillConstructor)
{
    List<int> lst(5, 42);
    EXPECT_EQ(lst.size(), 5u);
    for (List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        EXPECT_EQ(*it, 42);
    }
}

TEST(ListTest, RangeConstructor)
{
    int arr[] = {1,2,3,4};
    List<int> lst(arr, arr + 4);
    EXPECT_EQ(lst.size(), 4u);
    int i = 1;
    for (List<int>::iterator it = lst.begin(); it != lst.end(); ++it, ++i) {
        EXPECT_EQ(*it, i);
    }
}

TEST(ListTest1, CopyConstructor)
{
    List<std::string> a;
    a.push_back("hello");
    a.push_back("world");
    List<std::string> b(a);
    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.front(), "hello");
    EXPECT_EQ(b.back(), "world");
}

// ======== Modifiers =========
TEST(ListTest, PushBackAndFront)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_front(0);

    EXPECT_EQ(lst.size(), 3u);
    EXPECT_EQ(lst.front(), 0);
    EXPECT_EQ(lst.back(), 2);
}

TEST(ListTest, PopBackAndFront)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    lst.pop_back();
    EXPECT_EQ(lst.size(), 2u);
    EXPECT_EQ(lst.back(), 2);

    lst.pop_front();
    EXPECT_EQ(lst.size(), 1u);
    EXPECT_EQ(lst.front(), 2);
}

TEST(ListTest, InsertMiddle)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(3);

    List<int>::iterator it = lst.begin();
    ++it; // points to 3
    lst.insert(it, 2);

    EXPECT_EQ(lst.size(), 3u);

    int expected[] = {1,2,3};
    int i = 0;
    for (List<int>::iterator iter = lst.begin(); iter != lst.end(); ++iter, ++i) {
        EXPECT_EQ(*iter, expected[i]);
    }
}

TEST(ListTest, ClearEmptiesTheList)
{
    List<int> lst(10, 5);
    EXPECT_FALSE(lst.empty());
    lst.clear();
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.size(), 0u);
}

// ======== Iterators =========
TEST(ListTest, ForwardIteration)
{
    List<int> lst;
    for (int i = 1; i <= 3; ++i) lst.push_back(i);

    int sum = 0;
    for (List<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        sum += *it;
    }
    EXPECT_EQ(sum, 6);
}

TEST(ListTest, ReverseIteration)
{
    List<int> lst;
    for (int i = 1; i <= 3; ++i) lst.push_back(i);

    int expected[] = {3,2,1};
    int i = 0;
    for (List<int>::reverse_iterator it = lst.rbegin(); it != lst.rend(); ++it, ++i) {
        EXPECT_EQ(*it, expected[i]);
    }
}

TEST(ListTest, PushBackAndSize)
{
    List<int> lst;
    EXPECT_TRUE(lst.empty());
    lst.push_back(10);
    lst.push_back(20);
    EXPECT_EQ(lst.size(), 2u);
    EXPECT_EQ(lst.back(), 20);
    EXPECT_EQ(lst.front(), 10);
}

TEST(ListTest, PushFront)
{
    List<int> lst;
    lst.push_front(1);
    lst.push_front(2);
    lst.push_front(3);
    EXPECT_EQ(lst.size(), 3u);
    EXPECT_EQ(lst.front(), 3);
    EXPECT_EQ(lst.back(), 1);
}

TEST(ListTest, PopBack)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.pop_back();
    EXPECT_EQ(lst.size(), 1u);
    EXPECT_EQ(lst.back(), 1);
    lst.pop_back();
    EXPECT_TRUE(lst.empty());
}

TEST(ListTest, PopFront)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.pop_front();
    EXPECT_EQ(lst.size(), 1u);
    EXPECT_EQ(lst.front(), 2);
    lst.pop_front();
    EXPECT_TRUE(lst.empty());
}

TEST(ListTest, InsertSingle)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(3);
    List<int>::iterator it = lst.begin();
    ++it; // points to 3
    lst.insert(it, 2);
    EXPECT_EQ(lst.size(), 3u);

    List<int>::iterator iter = lst.begin();
    EXPECT_EQ(*iter, 1);
    ++iter;
    EXPECT_EQ(*iter, 2);
    ++iter;
    EXPECT_EQ(*iter, 3);
}

TEST(ListTest, EraseSingle)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    List<int>::iterator it = lst.begin();
    ++it; 
    it = lst.erase(it); 

    EXPECT_EQ(lst.size(), 2u);
    EXPECT_EQ(*it, 3); 
    EXPECT_EQ(lst.front(), 1);
    EXPECT_EQ(lst.back(), 3);
}

TEST(ListTest, EraseRange)
{
    List<int> lst;
    for (int i = 1; i <= 5; ++i) {
        lst.push_back(i);
    }
    List<int>::iterator first = lst.begin();
    ++first; 
    List<int>::iterator last = first;
    ++last; ++last; 
    lst.erase(first, last);

    EXPECT_EQ(lst.size(), 3u);
    List<int>::iterator it = lst.begin();
    EXPECT_EQ(*it, 1);
    ++it;
    EXPECT_EQ(*it, 4);
    ++it;
    EXPECT_EQ(*it, 5);
}

TEST(ListTest, ResizeBiggerAndSmaller)
{
    List<int> lst(3, 7); 
    EXPECT_EQ(lst.size(), 3u);
    lst.resize(5, 9);    
    EXPECT_EQ(lst.size(), 5u);
    EXPECT_EQ(lst.back(), 9);

    lst.resize(2);
    EXPECT_EQ(lst.size(), 2u);
    EXPECT_EQ(lst.back(), 7);
}

TEST(ListTest, ClearAndEmpty)
{
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.clear();
    EXPECT_TRUE(lst.empty());
    EXPECT_EQ(lst.size(), 0u);
}

TEST(ListTest, SwapWorks)
{
    List<int> a;
    a.push_back(1);
    a.push_back(2);

    List<int> b;
    b.push_back(10);

    a.swap(b);

    EXPECT_EQ(a.size(), 1u);
    EXPECT_EQ(a.front(), 10);

    EXPECT_EQ(b.size(), 2u);
    EXPECT_EQ(b.front(), 1);
    EXPECT_EQ(b.back(), 2);
}

TEST(ListComparisonTest, EqualityOperator)
{
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    List<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(ListComparisonTest, InequalityOperator)
{
    List<int> a;
    a.push_back(1);
    a.push_back(2);

    List<int> b;
    b.push_back(1);
    b.push_back(3);

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a == b);
}

TEST(ListComparisonTest, LessOperator)
{
    List<int> a;
    a.push_back(1);
    a.push_back(2);

    List<int> b;
    b.push_back(1);
    b.push_back(3);

    EXPECT_TRUE(a < b);   // 2 < 3
    EXPECT_FALSE(b < a);
}

TEST(ListComparisonTest, GreaterOperator)
{
    List<int> a;
    a.push_back(2);
    a.push_back(5);

    List<int> b;
    b.push_back(2);
    b.push_back(3);

    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);
}

TEST(ListComparisonTest, LessEqualAndGreaterEqual)
{
    List<int> a;
    a.push_back(1);
    a.push_back(2);

    List<int> b;
    b.push_back(1);
    b.push_back(2);

    List<int> c;
    c.push_back(1);
    c.push_back(3);

    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a >= b);

    EXPECT_TRUE(a <= c);
    EXPECT_TRUE(c >= a);
}
// ======== Basic construction and push/pop tests ========
TEST(ListTest, DefaultConstructorIsEmpty1)
{
    List<int> l;
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), (size_t)0);
}

TEST(ListTest, PushBackAndFrontBack)
{
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);

    EXPECT_EQ(l.size(), (size_t)3);
    EXPECT_EQ(l.front(), 10);
    EXPECT_EQ(l.back(), 30);
}

TEST(ListTest, PushFrontWorks1) {
    List<int> l;
    l.push_front(5);
    l.push_front(10);

    EXPECT_EQ(l.front(), 10);
    EXPECT_EQ(l.back(), 5);
    EXPECT_EQ(l.size(), (size_t)2);
}

TEST(ListTest, PopFrontAndBack)
{
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    l.pop_front();
    EXPECT_EQ(l.front(), 2);
    l.pop_back();
    EXPECT_EQ(l.back(), 2);
    EXPECT_EQ(l.size(), (size_t)1);
}

// ======== Insert / Erase ========
TEST(ListTest, InsertAndErase)
{
    List<int> l;
    l.push_back(1);
    l.push_back(3);

    List<int>::iterator it = l.begin();
    ++it; // position of 3
    l.insert(it, 2);

    EXPECT_EQ(l.size(), (size_t)3);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 3);

    it = l.begin();
    ++it; // iterator to 2
    l.erase(it);
    EXPECT_EQ(l.size(), (size_t)2);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 3);
}

// ======== Splice ========
TEST(ListTest, SpliceWholeList)
{
    List<int> l1;
    l1.push_back(1);
    l1.push_back(2);

    List<int> l2;
    l2.push_back(3);
    l2.push_back(4);

    l1.splice(l1.end(), l2);

    EXPECT_EQ(l1.size(), (size_t)4);
    EXPECT_TRUE(l2.empty());

    List<int>::iterator it = l1.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3); ++it;
    EXPECT_EQ(*it, 4);
}

// ======== Unique ========
TEST(ListTest, UniqueRemovesConsecutiveDuplicates)
{
    List<int> l;
    l.push_back(1);
    l.push_back(1);
    l.push_back(2);
    l.push_back(2);
    l.push_back(3);

    l.unique();
    EXPECT_EQ(l.size(), (size_t)3);

    List<int>::iterator it = l.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);
}

// ======== Reverse ========
TEST(ListTest, ReverseWorks)
{
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);

    l.reverse();
    EXPECT_EQ(l.front(), 3);
    EXPECT_EQ(l.back(), 1);

    List<int>::iterator it = l.begin();
    EXPECT_EQ(*it, 3); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 1);
}

// ======== Sort ========
TEST(ListTest, SortWorks)
{
    List<int> l;
    l.push_back(3);
    l.push_back(1);
    l.push_back(2);

    l.sort();

    List<int>::iterator it = l.begin();
    EXPECT_EQ(*it, 1); ++it;
    EXPECT_EQ(*it, 2); ++it;
    EXPECT_EQ(*it, 3);
}

int
main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


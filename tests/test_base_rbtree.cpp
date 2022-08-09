#include <gtest/gtest.h>

#include "../src/rbtree/rbtree.h"

using namespace eq;

TEST(BaseRBTreeSuite, BaseRBTreeItWorks) {
  EXPECT_EQ(1, 1);
}

TEST(BaseRBTreeSuite, BaseRBTreeCreate) {
    base_rbtree<int> tree;
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.depth(), 0);
    EXPECT_EQ(tree.empty(), true);
}

TEST(BaseRBTreeSuite, BaseRBTreeInsert) {
    base_rbtree<int> tree;

    std::vector<void *> ptrs_to_free;
    ptrs_to_free.reserve(10);

    for (int i = 0; i < 10; ++i) {
        auto *node = new base_rbtree_node<int>{i};
        tree.insert_node(*node);
        ptrs_to_free.push_back(static_cast<void*>(node));
    }

    for (int i = 0; i < 10; ++i)
        EXPECT_TRUE(tree.find_node_by_data(i).has_value());

    //  This is an unsafe "free all" operation - do not access `tree` after this loop.
    for (auto ptr : ptrs_to_free)
        delete ptr;
}

TEST(BaseRBTreeSuite, BaseRBTreeRemove) {
    base_rbtree<int> tree;
    auto *node1 = new base_rbtree_node<int> {1};
    auto *node2 = new base_rbtree_node<int> {2};
    auto *node3 = new base_rbtree_node<int> {3};

    tree.insert_node(*node1);
    tree.insert_node(*node2);
    tree.insert_node(*node3);

    EXPECT_TRUE(tree.find_node_by_data(1).has_value());
    EXPECT_TRUE(tree.find_node_by_data(2).has_value());
    EXPECT_TRUE(tree.find_node_by_data(3).has_value());

    tree.remove_node(*node1);
    tree.remove_node(*node2);
    tree.remove_node(*node3);

    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
}


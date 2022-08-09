#include "base_rbtree.h"

#pragma once

namespace eq {

template <typename K>
class rbtree_node;

template <typename K>
class rbtree : public base_rbtree<K>
{
    using node_type = rbtree_node<K>;
    friend node_type;

public:
    virtual ~rbtree() noexcept override {}
};

template <typename K>
class rbtree_node : public base_rbtree_node<K>
{
    friend rbtree<K>;
};

}

#pragma once

#include <memory>
#include <optional>
#include <functional>

#include <gsl/assert>

#define EQ_RBTREE_DEBUG

namespace eq {

    struct config {
        bool keep_duplicates{false};
    };

    template<typename T>
    using optional_ref = std::optional<std::reference_wrapper<T>>;

///

    enum class rbtree_color : uint8_t {
        black, red
    };

    class base_rbtree_iterator;

    template<typename K>
    class base_rbtree_node;

    template<typename K>
    class base_rbtree {
        using node_type = base_rbtree_node<K>;
        friend node_type;

        std::size_t m_num_nodes{0};
        std::size_t m_depth{0};

        node_type *m_root{nullptr};
        node_type *m_leftmost{nullptr};
        config m_config;

    private:
        optional_ref<node_type> leftmost_of_subtree(node_type &root_node) {
            if (&root_node == m_root && m_leftmost != nullptr)
                return m_leftmost;
            auto *curr = &root_node;
            while (curr->m_left)
                curr = curr->m_left;
            return std::ref(*curr);
        }

        optional_ref<node_type> rightmost_of_subtree(node_type &root_node) {
            auto *curr = &root_node;
            while (curr->m_right)
                curr = curr->m_right;
            return std::ref(*curr);
        }

        static inline node_type *parent_of(node_type &node) {
            return node.m_parent;
        }

        static inline node_type *grandparent_of(node_type &node) {
            assert(node.m_parent);
            return node.m_parent->m_parent;
        }

        static inline node_type *left_uncle_of(node_type &node) {
            assert(node.m_parent);
            return node.m_parent->m_left;
        }

        static inline node_type *right_uncle_of(node_type &node) {
            assert(node.m_parent);
            return node.m_parent->m_right;
        }


    public:
        base_rbtree() = default;

        base_rbtree(const base_rbtree &) = default;

        base_rbtree(base_rbtree &&) noexcept = default;

        base_rbtree &operator=(const base_rbtree &) noexcept = default;

        base_rbtree &operator=(base_rbtree &&) noexcept = default;

        virtual ~base_rbtree() noexcept {}

        void rotate_left_based_on(node_type &node) {
            node_type *right = node.m_right;
            node_type *parent = parent_of(node);

            node.m_right = right->m_left;
            if (node.m_right)
                node.m_right->m_parent = &node;

            right->m_left = &node;
            node.m_parent = right;

            right->m_parent = parent;
            if (!parent)
                m_root = parent;
            else if (parent->m_left == &node)
                parent->m_left = right;
            else
                parent->m_right = right;
        }

        void rotate_right_based_on(node_type &node) {
            node_type *left = node.m_left;
            node_type *parent = parent_of(node);

            node.m_left = left->m_right;
            if (node.m_left)
                node.m_left->m_parent = &node;

            left->m_right = &node;
            node.m_parent = left;

            left->m_parent = parent;
            if (!parent)
                m_root = parent;
            else if (parent->m_right == &node)
                parent->m_right = left;
            else
                parent->m_left = left;
        }

        void rebalance_after_insert_of(node_type &node) {
            auto try_uncle_shortcut = [](node_type *uncle, node_type *curr) -> bool {
                if (!uncle || uncle->is_black())
                    return false;
                parent_of(*curr)->m_color = rbtree_color::black;
                grandparent_of(*curr)->m_color = rbtree_color::red;
                uncle->m_color = rbtree_color::black;
                curr = grandparent_of(*curr);
                return true;
            };

            for (node_type *curr = &node; parent_of(*curr) && parent_of(*curr)->is_red();) {
                if (grandparent_of(*curr)->m_left == parent_of(*curr)) {
                    // In _left_ subtree of _grandparent_
                    node_type *uncle = grandparent_of(*curr)->m_right;
                    if (try_uncle_shortcut(uncle, curr))
                        continue;

                    if (parent_of(*curr)->m_left == curr) {
                        // In _right_ subtree of _parent_
                        curr = parent_of(*curr);
                        rotate_left_based_on(*curr);
                    }
                    parent_of(*curr)->m_color = rbtree_color::black;
                    grandparent_of(*curr)->m_color = rbtree_color::red;

                    rotate_right_based_on(*grandparent_of(*curr));
                } else {
                    // In _right_ subtree of _grandparent_
                    node_type *uncle = grandparent_of(*curr)->m_left;
                    if (try_uncle_shortcut(uncle, curr))
                        continue;

                    if (parent_of(*curr)->m_left == curr) {
                        // In _left_ subtree of _parent_
                        curr = parent_of(*curr);
                        rotate_right_based_on(*curr);
                    }

                    parent_of(*curr)->m_color = rbtree_color::black;
                    grandparent_of(*curr)->m_color = rbtree_color::red;
                    rotate_left_based_on(*grandparent_of(*curr));
                }
            }
            m_root->m_color = rbtree_color::black;
        }

        void insert_node(node_type &new_node) {
            auto parent = find_location_of_data(new_node.m_data);
            if (!parent) {
                m_root = &new_node;
                m_num_nodes = 1;
                m_leftmost = &new_node;
                new_node.m_color = rbtree_color::black;
                return;
            }

            auto &parent_node = parent->get();
            if (parent_node.m_data == new_node.m_data && m_config.keep_duplicates)
                return;

            if (parent_node.m_data > new_node.m_data)
                parent_node.m_right = &new_node;
            else
                parent_node.m_left = &new_node;
            new_node.m_parent = &parent_node;
            ++m_num_nodes;
            if (m_leftmost->m_data < new_node.m_data)
                m_leftmost = &new_node;

            if (m_depth > 2)
                rebalance_after_insert_of(new_node);
        }

        void remove_node(node_type &node) {
            if (m_root->m_left == nullptr && m_root->m_right == nullptr) {
                m_root = nullptr;
                m_num_nodes = 0;
                return;
            }
            --m_num_nodes;
            // TODO:
            return;
        }

        optional_ref<node_type> find_location_of_data(const K &data) {
            auto *ptr = m_root;
            while (ptr) {
                if (ptr->m_data == data)
                    return std::ref(*ptr);
                if (ptr->m_data > data) {
                    if (!ptr->m_right)
                        return std::ref(*ptr);
                    ptr = ptr->m_right;
                } else if (ptr->m_data < data) {
                    if (!ptr->m_left)
                        return std::ref(*ptr);
                    ptr = ptr->m_left;
                }
            }

            return {};
        }

        optional_ref<node_type> find_node_by_data(const K &data) {
            const auto node_or_empty = find_location_of_data(data);
            if (!node_or_empty.has_value())
                return {};
            if (node_or_empty->get().m_data != data)
                return {};
            return node_or_empty;
        }

        std::size_t size() const noexcept {
            return m_num_nodes;
        }

        std::size_t depth() const noexcept {
            return m_depth;
        }

        bool empty() const noexcept {
            return m_num_nodes == 0;
        }
    };

    template<typename K>
    class base_rbtree_node {
        friend base_rbtree<K>;

        rbtree_color m_color{rbtree_color::red};
        const K m_data;
        base_rbtree_node *m_left{nullptr};
        base_rbtree_node *m_right{nullptr};
        base_rbtree_node *m_parent{nullptr};

    public:
        virtual ~base_rbtree_node() noexcept {}

        base_rbtree_node(const K &data)
                : m_data{data} {
        }

        base_rbtree_node(const base_rbtree_node &) = default;

        base_rbtree_node &operator=(const base_rbtree_node &) noexcept = default;

        bool is_red() const noexcept {
            return m_color == rbtree_color::red;
        }

        bool is_black() const noexcept {
            return m_color == rbtree_color::black;
        }

        const K &data() const noexcept {
            return m_data;
        }
    };

}

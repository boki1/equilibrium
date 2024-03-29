#pragma once

#if __STDC_HOSTED__
#include <stdlib.h>
#else
typedef unsigned long size_t;
#endif

enum rbtree_color {
	RED,
	BLACK,
};

struct rbtree_node {
	enum rbtree_color _color;
	struct rbtree_node *_left;
	struct rbtree_node *_right;
	struct rbtree_node *_parent;
	void *_data_ptr;
};

typedef int (*rbtree_comparator)(struct rbtree *, struct rbtree_node *,
								 void *data);

struct rbtree {
	struct rbtree_node *_root;
	struct rbtree_node *_smallest;
	struct rbtree_node *_biggest;
	size_t _size;
	size_t _depth;
	rbtree_comparator _compare_data_cb;
};

struct rbtree_iterator {
		struct rbtree_node *_ptr;
		struct rbtree *_tree;
};

// Tree operations
int rbtree_init(struct rbtree *);
int rbtree_destroy(struct rbtree *);
int rbtree_copy(struct rbtree *);

// Mutable data operations
int rbtree_insert(struct rbtree *, void *);
int rbtree_remove(struct rbtree *);

// Immutable data operations
struct rbtree_node *rbtree_find_if(struct rbtree *, void *, rbtree_comparator);
struct rbtree_node *rbtree_find(struct rbtree *, void *);
struct rbtree_iterator rbtree_find_it(struct rbtree *, rbtree_comparator);
struct rbtree_iterator rbtree_begin(struct rbtree *);
struct rbtree_iterator rbtree_end(struct rbtree *);
int rbtree_next(struct rbtree_iterator *);
int rbtree_prev(struct rbtree_iterator *);

#define rbtree_for_each_node(tree, it)                          \
		for (struct rbtree_iterator it = rbtree_begin(&(tree)), \
									end = rbtree_end(&(tree));  \
			 it._ptr != end._ptr; rbtree_next(it._ptr))

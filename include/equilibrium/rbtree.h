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
	void *_data_ptr;
};

struct rbtree {
	struct rbtree_node *_root;
	struct rbtree_node *_smallest;
	size_t _size;
	size_t _depth;
};

int rbtree_init(struct rbtree *);
int rbtree_destroy(struct rbtree *);

int rbtree_insert(struct rbtree *);
int rbtree_remove(struct rbtree *);
int rbtree_find(struct rbtree *);

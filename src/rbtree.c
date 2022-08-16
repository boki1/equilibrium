#include <assert.h>
#include <stdlib.h>

#include <equilibrium/rbtree.h>

static void rotate_subtree_left(struct rbtree_node *root,
								struct rbtree_node *pivot)
{
		assert(root != NULL);
		assert(pivot != NULL);

		root->_right = pivot->_left;
		if (root->_right)
				root->_right->_parent = root;
		pivot->_left = root;
		root->_parent = pivot;
}

static void rotate_subtree_right(struct rbtree_node *root,
								 struct rbtree_node *pivot)
{
		assert(root != NULL);
		assert(pivot != NULL);

		root->_left = pivot->_right;
		if (root->_left)
				root->_left->_parent = root;
		pivot->_right = root;
		root->_parent = pivot;
}

int rbtree_init(struct rbtree *rbtree)
{
		assert(rbtree != NULL);
		rbtree->_size = 0;
		rbtree->_depth = 0;
		rbtree->_root = NULL;
		rbtree->_smallest = NULL;
		rbtree->_biggest = NULL;
}

int rbtree_destroy(struct rbtree *rbtree)
{
}
int rbtree_copy(struct rbtree *rbtree)
{
}

/*
 * Finds a node which is suitable to be a parent of a node containing `data`.
 * The different with regular "find" is that it also accepts (i.e returns 0) nodes which do not
 * have equal data with the input one, but have not subtree in which the operation to continue.
 */
static int rbtree_find_place_for_data_compare_cb(struct rbtree *rbtree,
												 void *data,
												 struct rbtree_node *node)
{
		const int res = rbtree->_compare_data_cb(rbtree, data, node->_data_ptr);
		if (res == 0)
				return 0;
		if (res > 0 && !node->_right)
				return 0;
		if (res < 0 && !node->_left)
				return 0;
		return res;
}

int rbtree_insert(struct rbtree *rbtree, void *data)
{
		struct rbtree_node *parent = rbtree_find_if(
				rbtree, data, rbtree_find_place_for_data_compare_cb);
		return 0;
}

int rbtree_remove(struct rbtree *rbtree)
{
}

struct rbtree_node *rbtree_find(struct rbtree *rbtree, void *opaque_ptr)
{
		if (!rbtree->_compare_data_cb)
				return NULL;
		return rbtree_find_if(rbtree, opaque_ptr, rbtree->_compare_data_cb);
}

struct rbtree_node *rbtree_find_if(struct rbtree *rbtree, void *opaque_ptr,
								   rbtree_comparator compare_cb)
{
		assert(compare_cb != NULL);
		struct rbtree_node *curr = rbtree->_root;
		while (curr) {
				int res = (*compare_cb)(rbtree, curr, opaque_ptr);
				if (res == 0)
						return curr;
				if (res > 0)
						curr = curr->_right;
				else
						curr = curr->_left;
		}

		return NULL;
}

struct rbtree_iterator rbtree_find_it(struct rbtree *rbtree,
									  rbtree_comparator cb)
{
		struct rbtree_node *node = rbtree_find(rbtree, cb);
		struct rbtree_iterator it = {
				._ptr = node,
				._tree = rbtree,
		};
		return it;
}
struct rbtree_iterator rbtree_begin(struct rbtree *rbtree)
{
}
struct rbtree_iterator rbtree_end(struct rbtree *rbtree)
{
}
int rbtree_next(struct rbtree_iterator *rbtree_it)
{
}
int rbtree_prev(struct rbtree_iterator *rbtree_it)
{
}

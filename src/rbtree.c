#include <assert.h>
#include <stdlib.h>

#include <equilibrium/rbtree.h>

static void rotate_subtree_left(struct rbtree_node *root,
								struct rbtree_node *pivot)
{
}
static void rotate_subtree_right(struct rbtree_node *root,
								 struct rbtree_node *pivot)
{
}

int rbtree_init(struct rbtree *rbtree)
{
}
int rbtree_destroy(struct rbtree *)
{
}
int rbtree_copy(struct rbtree *)
{
}
int rbtree_insert(struct rbtree *)
{
}
int rbtree_remove(struct rbtree *)
{
}
int rbtree_find(struct rbtree *, rbtree_node_compare)
{
}
struct rbtree_iterator rbtree_find_it(struct rbtree *, rbtree_node_compare)
{
}
struct rbtree_iterator rbtree_begin(struct rbtree *)
{
}
struct rbtree_iterator rbtree_end(struct rbtree *)
{
}
int rbtree_next(struct rbtree_iterator *)
{
}
int rbtree_prev(struct rbtree_iterator *)
{
}

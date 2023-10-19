#include "rbtree.h"

rbtree_t rb_root;
int main(void)
{
    rbtree_node_t n1 = {.key = 3}, n2 = {.key = 2}, n3 = {.key = 7}, n4 = {.key = 1};
    rbtree_init(&rb_root);
    rbtree_insert(&rb_root, &n1);
    rbtree_insert(&rb_root, &n2);
    rbtree_insert(&rb_root, &n3);
    rbtree_insert(&rb_root, &n4);

    return 0;
}
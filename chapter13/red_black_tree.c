#include <stdio.h>
#include <stdlib.h>

struct rb_root {
        struct rb_node *rb_node;
};

struct rb_node {
        struct rb_node *rb_parent;
        int color;
#define RB_RED          0
#define RB_BLACK        1
        struct rb_node *rb_left;
        struct rb_node *rb_right;
        int value;
};

struct rb_root *create()
{
        return calloc(1, sizeof(struct rb_root));
}

void destroy_node(struct rb_node *rb_node)
{
        if (rb_node == NULL) return;
        destroy_node(rb_node->rb_left);
        destroy_node(rb_node->rb_right);
        free(rb_node);
}

int destroy(struct rb_root *rb_root)
{
        if (rb_root == NULL)
                return -1;
        destroy_node(rb_root->rb_node);
        free(rb_root);
        return 0;
}

static struct rb_node * _search(struct rb_node *rb_node, int key) {
        if ((rb_node == NULL) || (rb_node->value == key)) return rb_node;
        if (rb_node->value > key) return _search(rb_node->rb_left, key);
        return _search(rb_node->rb_right, key);
}

struct rb_node * search(struct rb_root *rb_root, int key) {
        return _search(rb_root->rb_node, key);
}

static void _insert(struct rb_node **rb_node_p, struct rb_node *rb_node_parent, \
                struct rb_node *rb_node)
{
        if (*rb_node_p == NULL) {
                *rb_node_p = rb_node;
                rb_node->rb_parent = rb_node_parent;
                return;
        }
        if ((*rb_node_p)->value > rb_node->value)
                return _insert(&((*rb_node_p)->rb_left), *rb_node_p, rb_node);
        else
                return _insert(&((*rb_node_p)->rb_right), *rb_node_p, rb_node);
}

void rotate_left(struct rb_node *node, struct rb_root *root)
{
        struct rb_node *right = node->rb_right;
        if (node->rb_right = right->rb_left)
                node->rb_right->rb_parent = node;

        if (right->rb_parent = node->rb_parent) {
                if (right->rb_parent->rb_left == node)
                        right->rb_parent->rb_left = right;
                else
                        right->rb_parent->rb_right = right;

        } else {
                root->rb_node = right;
        }

        right->rb_left = node;
        node->rb_parent = right;
}

void rotate_right(struct rb_node *node, struct rb_root *root)
{
        struct rb_node *left = node->rb_left;
        if (node->rb_left = left->rb_right)
                node->rb_left->rb_parent = node;

        if (left->rb_parent = node->rb_parent) {
                if (left->rb_parent->rb_left == node)
                        left->rb_parent->rb_left = left;
                else
                        left->rb_parent->rb_right = left;

        } else {
                root->rb_node = left;
        }

        left->rb_right = node;
        node->rb_parent = left;
}

static void insert_rebalance(struct rb_node *node, struct rb_root *root)
{
        struct rb_node *parent, *gparent;
        while ((parent=node->rb_parent) && (parent->color == RB_RED)) {
                gparent = parent->rb_parent;
                if (gparent->rb_left == parent) {
                        struct rb_node *uncle = gparent->rb_right;
                        if (uncle && uncle->color == RB_RED) {
                                parent->color = uncle->color = RB_BLACK;
                                gparent->color = RB_RED;
                                node = gparent;
                                continue;
                        }
                        if (parent->rb_right == node) {
                                rotate_left(parent, root);
                                struct rb_node *tmp;
                                tmp = parent;
                                parent = node;
                                node = tmp;
                        }
                        rotate_right(parent, root);
                        parent->color = RB_BLACK;
                        gparent->color = RB_RED;
                } else {
                        struct rb_node *uncle = gparent->rb_left;
                        if (uncle && uncle->color == RB_RED) {
                                parent->color = uncle->color = RB_BLACK;
                                gparent->color = RB_RED;
                                node = gparent;
                                continue;
                        }
                        if (parent->rb_left == node) {
                                rotate_right(parent, root);
                                struct rb_node *tmp;
                                tmp = parent;
                                parent = node;
                                node = tmp;
                        }
                        rotate_left(parent, root);
                        parent->color = RB_BLACK;
                        gparent->color = RB_RED;
                }

        }
}

void insert(struct rb_root *root, int key)
{
        struct rb_node *node = malloc(sizeof(*node));
        node->value = key;
        _insert((struct rb_node **)root, NULL, node);
        node->color = RB_RED;
        insert_rebalance(node, root);
}

delete_rebalance(struct rb_root *root, struct rb_node *node, struct rb_node *parent)
{

}

struct rb_node *delete(struct rb_root *root, int key)
{
        struct rb_node *node = search(root, key);
        if (node == NULL) return node;
        if (node->rb_left == NULL) {
                struct rb_node *right;
                if (right = node->rb_right) {
                        if (right0>

         

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

void delete_rebalance(struct rb_root *root, struct rb_node *node, struct rb_node *parent)
{
	struct rb_node *sibling;
	while ((node==NULL || node->color == RB_BLACK) && root->rb_node != node) {
		if (parent->rb_left == node) {
			sibling = parent->rb_right;
			//case 4
			if (sibling->color == RB_RED) {
				rotate_left(parent, root);
				parent->color = RB_RED;
				sibling->color = RB_BLACK;
				sibling = parent->rb_right;
			}
			//case 2
			if (sibling->rb_left && sibling->rb_left->color == RB_RED) {
				rotate_right(sibling, root);
				sibling->color = RB_RED;
				sibling = sibling->rb_parent;
				sibling->color = RB_BLACK;
			}
			//case 3
			if (sibling->rb_right && sibling->rb_right->color == RB_RED) {
				rotate_left(parent, root);
				sibling->color = parent->color;
				parent->color = RB_BLACK;
				sibling->rb_right->color = RB_BLACK;
				break;
			}
			//case 1
			sibling->color = RB_RED;
			node = parent;
			parent = node->rb_parent;
		} else {

		}
	}
	node->color = RB_BLACK;
}

void rb_transplant(struct rb_root *root, struct rb_node *from, struct rb_node *to)
{
	struct rb_node _save = *from, *save = &_save;
	if (from->rb_parent = to->rb_parent) {
		if (from->rb_parent->rb_left == to)
			from->rb_parent->rb_left = from;
		else
			from->rb_parent->rb_right = from; 
	} else {
		root->rb_node = from;
	}
	if (from->rb_left = to->rb_left)
		from->rb_left->rb_parent = from;
	if (from->rb_right = to->rb_right)
		from->rb_right->rb_parent = from;
	from->color = to->color;

	if (to->rb_parent = save->rb_parent) {
		if (to->rb_parent->rb_left == save)
			to->rb_parent->rb_left = to;
		else
			to->rb_parent->rb_right = to; 
	} else {
		root->rb_node = to;
	}
	if (to->rb_left = save->rb_left)
		to->rb_left->rb_parent = to;
	if (to->rb_right = save->rb_right)
		to->rb_right->rb_parent = to;
	to->color = save->color;
}



struct rb_node *delete(struct rb_root *root, int key)
{
        struct rb_node *node, *parent;
	node = search(root, key);
        if (node == NULL) return node;

	if (node->rb_left && node->rb_right) {
		struct rb_node *successor = node->rb_right;
		while (successor->rb_left) successor = successor->rb_left;
		rb_transplant(root, successor, node);
	}

        if (node->rb_left == NULL) {
                struct rb_node *right, *parent;
                if (right = node->rb_right)
			right->rb_parent = node->rb_parent;
		if (parent = node->rb_parent) {
			if (parent->rb_left == node)
				parent->rb_left = right;
			else
				parent->rb_right = right;
		} else {
			root->rb_node = right;
		}
		delete_rebalance(root, right, parent);
		return node;
	}
        if (node->rb_right == NULL) {
                struct rb_node *left, *parent;
                left = node->rb_left;
		left->rb_parent = node->rb_parent;
		if (parent = node->rb_parent) {
			if (parent->rb_left == node)
				parent->rb_left = left;
			else
				parent->rb_right = left;
		} else {
			root->rb_node = left;
		}
		delete_rebalance(root, left, parent);
		return node;
	}
}


         

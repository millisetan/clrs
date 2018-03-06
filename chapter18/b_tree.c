#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
#include <string.h>

struct bt_node {
        int leaf;
        int nkey;
        int *bt_keys;
        struct bt_node **bt_child;
};

struct bt_root {
        struct bt_node *bt_node;
        int t;
};

struct bt_node *bt_node_alloc(struct bt_root *root)
{
        //check return of malloc
        struct bt_node *node = malloc(sizeof(*node));
        memset(node, 0, sizeof(*node));
        node->bt_keys = malloc(sizeof(*(node->bt_keys)) * (2*root->t-1));
        node->bt_child =  malloc(sizeof(*(node->bt_child)) * (2*root->t));
}

void bt_node_free(struct bt_root *root, struct bt_node *node)
{
        free(node->bt_child);
        free(node->bt_keys);
        free(node);
}

void bt_split(struct bt_root *root, struct bt_node *node, struct bt_node *parent, int index)
{
        if (!parent) {
                parent = bt_node_alloc(root);
                //index = 0;
                root->bt_node = parent;
        }
        struct bt_node *new_node = bt_node_alloc(root);
        new_node->leaf = node->leaf;
        new_node->nkey = node->nkey = root->t -1;
        memcpy(new_node->bt_keys, node->bt_keys+root->t, (root->t-1)*sizeof(node->bt_keys[0]));
        memcpy(new_node->bt_child, node->bt_child+root->t, (root->t)*sizeof(node->bt_child[0]));

        int i;
        for (i=parent->nkey; i>index; --i) {
                parent->bt_keys[i] = parent->bt_keys[i-1];
                parent->bt_child[i+1] = parent->bt_child[i];
        }
        int count = parent->nkey-index;
        if (count) {
                void *from = parent->bt_keys+index;
                void *to = parent->bt_keys+index+1;
                memmove(to, from, count*sizeof(parent->bt_keys[0]));
                from = parent->bt_child+index+1;
                to = parent->bt_child+index+2;
                memmove(to, from, count*sizeof(parent->bt_child[0]));
        }
        parent->nkey++;
        parent->bt_keys[index] = node->bt_keys[root->t-1];
        parent->bt_child[index+1] = new_node;
=======

struct bt_node {
	int t;
	int leaf;
	int nkey;
	int *keys;
	struct bt_node **childs;
}

struct bt_root {
	struct bt_node *bt_node;
}

struct bt_node *search(struct bt_root *root, int key)
{
	struct bt_node *node = root->bt_node;
	while (node) {
		int i;
		for (i=0; i<node->nkey; ++i) {
			if (key == node->keys[i]) {
				return node;
			}
			if (key < node->keys[i]) {
				break;
			}
		}
		if (node->leaf)
			return NULL;
		node = node->childs[i];
	}
	return node;
>>>>>>> refs/remotes/origin/master
}

void insert(struct bt_root *root, int key)
{
<<<<<<< HEAD
        struct bt_node *node = root->bt_node;
        if (!node) {
                node = bt_node_alloc(root);
                node->bt_keys[node->nkey++] = key;
                node->leaf = 1;
                return;
        }

        struct bt_node *parent = NULL;
        int index = 0;
        while (1) {
                if (node->nkey == 2*root->t-1) {
                        bt_split(root, node, parent, index);
                        if (!parent) parent = root->bt_node;
                        int new_key = parent->bt_keys[index];
                        if (key == new_key) {
                                return;
                        }
                        if (key > new_key) {
                                node = parent->bt_child[index+1];
                        }
                }
                int i;
                for (i=0; i<node->nkey; ++i) {
                        if (key == node->bt_keys[i])
                                return;
                        if (key < node->bt_keys[i])
                                break;
                }
                if (node->leaf) {
                        int count = node->nkey - i;
                        if (count) {
                                void *from = parent->bt_keys+i;
                                void *to = parent->bt_keys+i+1;
                                memmove(to, from, count*sizeof(node->bt_keys[0]));
                        }
                        node->bt_keys[i] = key;
                        return;
                } else {
                        parent = node;
                        index = i;
                        node = parent->bt_child[i];
                }
        }
}

void bt_borrow_left(struct bt_root *root, struct bt_node *node, int index)
{
        struct bt_node *left = node->bt_child[index];
        struct bt_node *right = node->bt_child[index+1];
        //right
        memmove(right->bt_keys+1, right->bt_keys, right->nkey*sizeof(right->bt_keys[0]));
        right->bt_keys[0] = node->bt_keys[index];
        if (!right->leaf) {
                memmove(right->bt_child+1, right->bt_child, (right->nkey+1)*sizeof(right->bt_child[0]));
                right->bt_child[0] = left->bt_child[left->nkey];
        }
        right->nkey++;
        //node && left
        node->bt_keys[index] = left->bt_keys[--left->nkey];
}

void bt_merge(struct bt_root *root, struct bt_node *node, int index)
{
        struct bt_node *left = node->bt_child[index];
        struct bt_node *right = node->bt_child[index+1];
        void *from, *to;
        //left
        left->bt_keys[left->nkey] = node->bt_keys[index];
        from = right->bt_keys;
        to = left->bt_keys+left->nkey+1;
        memmove(to, from, (right->nkey)*sizeof(left->bt_keys[0]));
        if (!left->leaf) {
                from = right->bt_child;
                to = left->bt_child + left->nkey + 1;
                memmove(to, from, (right->nkey+1)*sizeof(left->bt_child[0]));
        }
        //node
        int count = node->nkey - index - 1;
        if (count) {
                from = node->bt_keys+index+1;
                to = node->bt_keys+index;
                memmove(to, from, count*sizeof(node->bt_keys[0]));
                from = node->bt_child+index+2;
                to = node->bt_child+index+1;
                memmove(to, from, count*sizeof(node->bt_child[0]));
        }
        node->nkey--;
        //right
        bt_node_free(root, right);
}



void delete(struct bt_root *root, int key)
{
        struct bt_node *node = root->bt_node;
        while (node) {
                int i;
                for (i=0; i<node->nkey; ++i) {
                        if (key == node->bt_keys[i]) {
                                if (node->leaf) {
                                        //delete key..
                                        return;
                                }
                                struct bt_node *victim;
                                victim = node->bt_child[i];
                                if (victim->nkey > root->t - 1) {
                                        while (1) {
                                                if (victim->leaf) {
                                                        //transplant;
                                                        node->bt_keys[i] \
                                                                = victim->bt_keys[--victim->nkey];
                                                        return;
                                                }
                                                struct bt_node *child, *sibling;
                                                child = victim->bt_child[victim->nkey];
                                                if (child->nkey > root->t - 1) {
                                                        victim = child;
                                                        continue;
                                                }
                                                sibling = victim->bt_child[victim->nkey-1];
                                                if (sibling->nkey > root->t - 1) {
                                                        bt_borrow()

                                                } else {
                                                        bt_merge()

                                                }
                                                victim = child;
                                        }
                                }
                                victim = node->bt_child[i+1];
                                if (victim->nkey > root->t - 1) {

                                }
                                rb_merge();
                        }
                        if (key < node->bt_keys[i])
                                break;
                }


}
=======
	struct bt_node *node = root->bt_node;
	struct bt_node *parent = NULL;
	int index = 0;
	struct bt_node *node = root->bt_node;
	while (node) {
		if (node->nkey == 2*node->t-1) {
			bt_split(root, node, parent, index);
		}
		int i;
		for (i=0; i<node->nkey; ++i) {
			if (key == node->keys[i]) {
				return node;
			}
			if (key < node->keys[i]) {
				break;
			}
		}
		if (node->leaf)
			return NULL;
		node = node->childs[i];
	}
	return node;
	while (node) {
		if (node->nkey == 2*node->t-1) {
			bt_split(root, node, parent, index);
		}
		int i;
		for (i=0; i<node->nkey; ++i) {
			if (key < node->keys[i]) {
				break;
			}
			if (key = node->keys[i]) {
				return node;
			}
		}
		parent = node;
		index = i;
		node = node->childs[i];
	}
	return node;
}

		


>>>>>>> refs/remotes/origin/master


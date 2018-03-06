#include <stdio.h>
#include <stdlib.h>

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
}

void insert(struct bt_root *root, int key)
{
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

		




#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct bs_root {
        struct bs_node *bs_node;
};

struct bs_node {
        struct bs_node *parent;
        int value;
        struct bs_node *left, *right;
};

struct bs_root *create()
{
        return calloc(1, sizeof(struct bs_root));
}

void destroy_node(struct bs_node *bs_node)
{
        if (bs_node == NULL) return;
        destroy_node(bs_node->left);
        destroy_node(bs_node->right);
        free(bs_node);
}

int destroy(struct bs_root *bs_root)
{
        if (bs_root == NULL)
                return -1;
        destroy_node(bs_root->bs_node);
        free(bs_root);
        return 0;
}

static struct bs_node * _search(struct bs_node *bs_node, int key) {
        if ((bs_node == NULL) || (bs_node->value == key)) return bs_node;
        if (bs_node->value > key) return _search(bs_node->left, key);
        return _search(bs_node->right, key);
}

struct bs_node * search(struct bs_root *bs_root, int key) {
        return _search(bs_root->bs_node, key);
}

static void _insert(struct bs_node **bs_node_p, struct bs_node *bs_node_parent, \
                struct bs_node *bs_node)
{
        if (*bs_node_p == NULL) {
                *bs_node_p = bs_node;
                bs_node->parent = bs_node_parent;
                return;
        }
        if ((*bs_node_p)->value > bs_node->value)
                return _insert(&((*bs_node_p)->left), *bs_node_p, bs_node);
        else
                return _insert(&((*bs_node_p)->right), *bs_node_p, bs_node);
}

void insert(struct bs_root *bs_root, int key)
{
        struct bs_node *bs_node = malloc(sizeof(*bs_node));
        bs_node->value = key;
        _insert((struct bs_node **)bs_root, NULL, bs_node);
}

struct bs_node * delete(struct bs_root *bs_root, int key)
{
        struct bs_node *target = search(bs_root, key);
        if (target == NULL) return NULL;
        if (target->left == NULL) {
                if (target->right)
                        target->right->parent = target->parent;
                if (target->parent) {
                        if (target->parent->left == target)
                                target->parent->left = target->right;
                        else
                                target->parent->right = target->right;
                }
                target->right = NULL;
                target->parent = NULL;
                return target;
        }
        if (target->right == NULL) {
                target->left->parent = target->parent;
                if (target->parent) {
                        if (target->parent->left == target)
                                target->parent->left = target->left;
                        else
                                target->parent->right = target->left;
                }
                return target;
        }

        //find successor 
        struct bs_node *bs_node_next = target->right;
        while (bs_node_next->left)
                bs_node_next=bs_node_next->left;
        
        //strip successor
        if (bs_node_next->right)
                bs_node_next->right->parent=bs_node_next->parent;
        if (bs_node_next->parent->left == bs_node_next)
                bs_node_next->parent->left = bs_node_next->right;
        if (bs_node_next->parent->right == bs_node_next)
                bs_node_next->parent->right = bs_node_next->right;

        //replace target with successor
        bs_node_next->parent = target->parent;
        bs_node_next->right = target->right;
        bs_node_next->left = target->left;
        if (bs_node_next->left)
                bs_node_next->left->parent = bs_node_next;
        if (bs_node_next->right)
                bs_node_next->right->parent = bs_node_next;
        if (bs_node_next->parent) {
                if (bs_node_next->parent->left == target)
                        bs_node_next->parent->left = bs_node_next;
                if (bs_node_next->parent->right == target)
                        bs_node_next->parent->right = bs_node_next;
        }
        return target;
}

int _tree_depth(struct bs_node *bs_node) {
        if (bs_node == NULL) return 0;
        int left = _tree_depth(bs_node->left);
        int right = _tree_depth(bs_node->right);
        return (left > right) ? left+1: right+1;
}

int tree_depth(struct bs_root *bs_root) {
        if (bs_root == NULL) return 0;
        return _tree_depth(bs_root->bs_node);
}

void _print_tree(struct bs_node *bs_node, char **map, \
                int level, int offset, int item_len)
{

        if (bs_node == NULL) return;
        int shift = (1 << (level-1)) * item_len / 2;
        _print_tree(bs_node->left, map, level-1, offset-shift, item_len);
        _print_tree(bs_node->right, map, level-1, offset+shift, item_len);
        char tmp[5];
        int value_len = sprintf(tmp, "%d", bs_node->value);
        if (value_len > 4) {
                printf("oops!\n");
                exit(1);
        }
        if (bs_node->left)
                memset(map[level]+offset-shift-1, '-', shift);
        if (bs_node->right)
                memset(map[level]+offset, '-', shift);
        int my_sh = (1+(value_len>2));
        memcpy(map[level]+offset-my_sh, tmp, value_len);
}


void print_tree(struct bs_root *bs_root)
{
        int depth = tree_depth(bs_root);
        if (depth == 0) return;
        int item_len = 2*2;
        int offset = ((1 << (depth-1)) * item_len / 2);
        int line_len = (1 << (depth-1)) * item_len + 1;
        char **map = malloc(sizeof(*map)*depth);
        char *_map = malloc(depth*line_len);
        memset(_map, ' ', depth*line_len);
        int i;
        for (i=0; i<depth; ++i) {
                map[i] = _map + i*line_len;
        }
        struct bs_node *bs_node = bs_root->bs_node;
        _print_tree(bs_root->bs_node, map, depth-1, offset, item_len);
        printf("\n");
        for (i=depth-1; i>=0; --i) {
                map[i][line_len-1] = 0;
                printf("%s\n", map[i]);
        }
}

int main()
{
        struct bs_root *tree_root = create();
        insert(tree_root, 6);
        insert(tree_root, 7);
        insert(tree_root, 2);
        insert(tree_root, 4);
        //insert(tree_root, 3);
        insert(tree_root, 5);
        insert(tree_root, 1);
        print_tree(tree_root);
        delete(tree_root, 2);
        print_tree(tree_root);
}


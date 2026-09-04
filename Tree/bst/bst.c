#include<stdio.h>
#include<stdlib.h>

typedef struct treeNode {
    int value;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert a new value into the BST
TreeNode* insert(TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

int is_Leaf(TreeNode* node) {
    return (node != NULL && node->left == NULL && node->right == NULL);
}

void print_leaves(TreeNode* root, int level) {
    if (root == NULL) {
        return;
    }
    if (is_Leaf(root)) {
        printf("%d %d\n", root->value, level);
        return;  // stop further recursion since it's a leaf node
    }
    print_leaves(root->left, level + 1);
    print_leaves(root->right, level + 1);
}

void free_tree(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        root = insert(root, value);
    }
    print_leaves(root, 1);
    free_tree(root);
    return 0;
}
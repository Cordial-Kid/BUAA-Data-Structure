#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 100

typedef struct treeNode {
    char word[MAX_SIZE];
    int cnt;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode* createNode(char* word) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    strcpy(newNode->word, word);
    newNode->cnt = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insert(TreeNode* root, char* word) {
    if (root == NULL) {
        return createNode(word);
    }
    int cmp = strcmp(word, root->word);
    if (cmp < 0) {
        root->left = insert(root->left, word);
    } else if (cmp > 0) {
        root->right = insert(root->right, word);
    } else {
        root->cnt++;
    }
    return root;
}

void print_inorder(TreeNode* root) {
    if (root == NULL) {
        return;
    }
    print_inorder(root->left);
    printf("%s %d\n", root->word, root->cnt);
    print_inorder(root->right);
}

void print_right_chain(TreeNode* root, int n) {
    TreeNode* current = root;
    for (int i = 0; i < n && current != NULL; i++) {
        printf("%s ", current->word);
        current = current->right;
    }
    printf("\n");
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
    FILE* source = fopen("article.txt", "r");

    if (source == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    
    int ch;
    char word[MAX_SIZE];
    int len = 0;
    TreeNode* root = NULL;
    while ((ch = fgetc(source)) != EOF) {
        if (isalpha((unsigned char) ch)) {
            word[len++] = tolower((unsigned char) ch);
        } else if (len > 0) {    // in case an empty word is inserted into the tree
            word[len] = '\0';
            root = insert(root, word);
            len = 0;
            memset(word, 0, sizeof(word));
        }
    }
    if (len > 0) {    // handle the last word if the file doesn't end with a non-alphabetic character
        word[len] = '\0';
        root = insert(root, word);
    }
    print_right_chain(root, 3);
    print_inorder(root);
    free_tree(root);
    fclose(source);
    return 0;
}
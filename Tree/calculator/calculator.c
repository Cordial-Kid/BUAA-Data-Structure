#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_SIZE 512

typedef struct token {
    int is_num;
    int num;
    char op;
} Token;

typedef struct treeNode {
    Token token;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

TreeNode* createNode(Token token) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->token = token;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 返回运算符的优先级
int priority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// convert infix expression to postfix expression (new array needs length count)
int to_postfix(const char* expr, Token postfix[]) {
    char op_stack[MAX_SIZE];
    int op_top = -1;
    int postfix_index = 0;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' ') {
            continue;
        } else if (expr[i] == '=') {
            break;
        } else if (isdigit((unsigned char) expr[i])) {
            int num = 0;
            while (isdigit((unsigned char) expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            postfix[postfix_index].is_num = 1;
            postfix[postfix_index].num = num;
            postfix_index++;
            i--; // step back to re-evaluate the current character
        } else {
            if (expr[i] == '(') {
                op_stack[++op_top] = expr[i];
            } else if (expr[i] == ')') {
                while (op_top >= 0 && op_stack[op_top] != '(') {
                    postfix[postfix_index].is_num = 0;
                    postfix[postfix_index].op = op_stack[op_top--];
                    postfix_index++;
                }
                op_top--; // pop '('
            } else {
                while (op_top >= 0 && op_stack[op_top] != '(' && priority(op_stack[op_top]) >= priority(expr[i])) {
                    postfix[postfix_index].is_num = 0;
                    postfix[postfix_index].op = op_stack[op_top--];
                    postfix_index++;
                }
                op_stack[++op_top] = expr[i];
            }
        }
    }
    while (op_top >= 0) {
        postfix[postfix_index].is_num = 0;
        postfix[postfix_index].op = op_stack[op_top--];
        postfix_index++;
    }
    return postfix_index;
}

TreeNode* build_expression_tree(Token* postfix, int length) {
    if (length == 0) {
        return NULL;
    }
    int top = -1;
    TreeNode* stack[length];
    for (int i = 0; i < length; i++) {
        if (postfix[i].is_num) {
            stack[++top] = createNode(postfix[i]);
        } else {
            TreeNode* right = stack[top--];
            TreeNode* left = stack[top--];
            TreeNode* newNode = createNode(postfix[i]);
            newNode->left = left;
            newNode->right = right;
            stack[++top] = newNode;
        }
    }
    return stack[top];
}

int calculate_expression_tree(TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->token.is_num) {
        return root->token.num;
    }
    int left_val = calculate_expression_tree(root->left);
    int right_val = calculate_expression_tree(root->right);
    switch (root->token.op) {
        case '+':
            return left_val + right_val;
        case '-':
            return left_val - right_val;
        case '*':
            return left_val * right_val;
        case '/':
            return left_val / right_val;
        default:
            return 0;
    }
}

int main() {
    char expr[MAX_SIZE];
    fgets(expr, MAX_SIZE, stdin);
    Token postfix[MAX_SIZE];
    int length = to_postfix(expr, postfix);
    TreeNode* root = build_expression_tree(postfix, length);
    int result = calculate_expression_tree(root);
    printf("%d\n", result);
    return 0;
}
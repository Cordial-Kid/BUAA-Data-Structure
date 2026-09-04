#include<stdio.h>
#include<stdlib.h>
#define MAX_DEGREE 3
#define MAX_NODES 100

typedef struct flow {
    int gate;
    int passenger;
} Flow;

typedef struct treeNode {
    int id;
    int num;
    struct treeNode* children[MAX_DEGREE];
} TreeNode;

TreeNode* createNode(int id) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->id = id;
    newNode->num = 0;
    for (int i = 0; i < MAX_DEGREE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

TreeNode* addChild(TreeNode* parent, int childId) {
    TreeNode* newChild = createNode(childId);
    parent->children[parent->num] = newChild;
    parent->num++;
    return newChild;
}

int compareFlows(const void* a, const void* b) {
    Flow* flowA = (Flow*)a;
    Flow* flowB = (Flow*)b;
    if (flowA->passenger != flowB->passenger) {
        return flowB->passenger - flowA->passenger; // descending order of passengers
    } else {
        return flowA->gate - flowB->gate; // ascending order of gate numbers
    }
}

int BFS(TreeNode* root, int* positions) {
    if (root == NULL) {
        return 0;
    }
    TreeNode* queue[MAX_NODES];  // queue for BFS
    int front = 0, rear = 0;
    int len = 0;
    queue[rear++] = root;    // 根节点入队
    while (front < rear) {
        // as long as front < rear, pop
        TreeNode* current = queue[front++];
        if (current->id < 100) {
            positions[len++] = current->id;
        }
        for (int i = 0; i < current->num; i++) {
            if (current->children[i] != NULL) {
                queue[rear++] = current->children[i];
            }
        }
    }
    return len;  // return the number of nodes with id < 100
}

TreeNode* findNode(TreeNode* root, int id) {
    if (root == NULL) {
        return NULL;
    }
    if (root->id == id) {
        return root;
    }
    for (int i = 0; i < root->num; i++) {
        TreeNode* found = findNode(root->children[i], id);
        if (found != NULL) {    // if found, return it
            return found;
        }
    }
    return NULL;    
}

int main() {
    int parent_id;
    TreeNode* root = NULL;
    while(1) {
        scanf("%d", &parent_id);
        if (parent_id == -1) {
            break;
        } else {
            TreeNode* parent = NULL;
            if (root == NULL) {
                root = createNode(parent_id);
                parent = root;
            } else {
                parent = findNode(root, parent_id);
            }
            while(1) {
                int child_id;
                scanf("%d", &child_id);
                if (child_id == -1) {
                    break;
                } else {
                    addChild(parent, child_id);
                }
            }
        }
    }
    int positions[MAX_NODES];
    int pos_count = BFS(root, positions);    // get the positions of the nodes -> flow
    Flow flows[MAX_NODES];
    for (int i = 0; i < pos_count; i++) {
        scanf("%d%d", &flows[i].gate, &flows[i].passenger);
    }
    qsort(flows, pos_count, sizeof(Flow), compareFlows);
    for (int i = 0; i < pos_count; i++) {
        printf("%d->%d\n", flows[i].gate, positions[i]);
    }
    return 0;
}
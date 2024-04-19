#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node in the binary search tree
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new node
struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the index of a value in an array
int findIndex(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1; // Value not found
}

// Function to construct the binary search tree from in-order and post-order traversals
struct TreeNode* bst_construct(int inOrder[], int postOrder[], int inStart, int inEnd, int postStart, int postEnd) {
    if (inStart > inEnd || postStart > postEnd) {
        return NULL;
    }

    // Create the root node
    struct TreeNode* root = newNode(postOrder[postEnd]);

    // Find index of root in in-order traversal
    int rootIndex = findIndex(inOrder, inStart, inEnd, root->data);

    // Recursively construct left and right subtrees
    root->left = bst_construct(inOrder, postOrder, inStart, rootIndex - 1, postStart, postStart + rootIndex - inStart - 1);
    root->right = bst_construct(inOrder, postOrder, rootIndex + 1, inEnd, postStart + rootIndex - inStart, postEnd - 1);

    return root;
}

// Function to traverse the binary search tree using breadth-first search
void bfs_traversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    // Create a queue for BFS traversal
    struct QueueNode {
        struct TreeNode* treeNode;
        struct QueueNode* next;
    };

    struct Queue {
        struct QueueNode *front, *rear;
    };

    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;

    // Enqueue the root node
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = root;
    newNode->next = NULL;
    queue->rear = queue->front = newNode;

    while (queue->front != NULL) {
        // Dequeue a node
        struct TreeNode* current = queue->front->treeNode;
        struct QueueNode* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);

        // Print the data of the dequeued node
        printf("%d ", current->data);

        // Enqueue the left child
        if (current->left != NULL) {
            struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
            newNode->treeNode = current->left;
            newNode->next = NULL;
            if (queue->front == NULL) {
                queue->front = newNode;
            } else {
                queue->rear->next = newNode;
            }
            queue->rear = newNode;
        }

        // Enqueue the right child
        if (current->right != NULL) {
            struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
            newNode->treeNode = current->right;
            newNode->next = NULL;
            if (queue->front == NULL) {
                queue->front = newNode;
            } else {
                queue->rear->next = newNode;
            }
            queue->rear = newNode;
        }
    }

    // Free the memory allocated for the queue
    free(queue);
}

int main() {
    // Given in-order and post-order traversal arrays
    int inOrder[] = {5, 10, 15, 20, 25, 30, 45};
    int postOrder[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(inOrder) / sizeof(inOrder[0]);

    // Construct the binary search tree
    struct TreeNode* root = bst_construct(inOrder, postOrder, 0, n - 1, 0, n - 1);

    // Traverse the binary search tree using BFS and print each element
    printf("BFS Traversal: ");
    bfs_traversal(root);

    return 0;
}

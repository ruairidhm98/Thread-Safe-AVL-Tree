#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

/* Returns the maximum between two values */
#define MAX(a, b) a > b ? a : b

/* Helper function, performs a left-left rotation */
Node *right_rotate(Node *y);
/* Helper function, performs a right-right test */
Node *left_rotate(Node *x);
/* Helper function, used to help with insertions */
Node *avl_insert_node(AVL *, Node *, int);
/* Helper function, used to get height balance */
static int get_Balance(Node *);
/* Helper function, return height of node */
static int height(Node *);
/* Helper function, deletes nodes in the tree */
static void delete_nodes(Node *);

/* Node in tree */
struct node {
    int key; // data stored at node
    struct node *left; // pointer to left child
    struct node *right; // pointer to right child
    int height; // height of node
};

/* AVL tree structure */
struct avltree {
    Node *root; // pointer to root node
    int size; // size counter
};

/* Creates an empty AVL tree. Returns a pointer to the tree if successfull, NULL otherwise */
AVL *avl_init() {

    AVL *tree;

    tree = malloc(sizeof(AVL));
    /* Return NULL and print error message if memory fails to allocate */
    if (!tree) {
        fprintf(stderr, "Error: memory failed to allocate. avl_init failed.\n");
        return NULL;
    }
    tree -> root = NULL;
    tree -> size = 0;

    return tree;
}

/* Returns a pointer to a new node object */
Node *newNode(int key) {

    Node *node;
    
    node = (Node *) malloc(sizeof(Node));
    node -> key = key;
    node -> left = NULL;
    node -> right = NULL;
    node -> height = 1;
    
    return node;
}

/* Inserts node into tree, returns 1 for sucess/failure */
int avl_insert(AVL *tree, int data) {
    
    int temp;

    temp = tree -> size;
    tree -> root = avl_insert_node(tree, tree -> root, data);
    if (temp == tree -> size - 1) return 1;
    return 0;
}

Node *avl_insert_node(AVL *tree, Node *node, int key) {

    int balance;

    /* Perform the normal BST insertion */
    if (!node) {
        tree -> size++;
        return newNode(key);
    }
    if (key < node -> key)
        node -> left = avl_insert_node(tree, node -> left, key);
    else if (key > node -> key)
        node -> right = avl_insert_node(tree, node -> right, key);
    /* Equal keys are not allowed in BST */
    else return node;

    /* Update height of this ancestor node */
    node -> height = 1 + MAX(height(node -> left), height(node -> right));

    /* 
     * Get the balance factor of this ancestor node to check 
     * whether this node became unbalanced 
     */
    balance = get_Balance(node);

    /*Left Left Case */
    if (balance > 1 && key < node -> left -> key)
        return right_rotate(node);
    /* Right Right Case */
    if (balance < -1 && key > node -> right -> key)
        return left_rotate(node);
    /* Left Right Case */
    if (balance > 1 && key > node -> left -> key) {
        node -> left = left_rotate(node -> left);
        return right_rotate(node);
    }
    /* Right Left Case */
    if (balance < -1 && key < node->right->key) {
        node -> right = right_rotate(node -> right);
        return left_rotate(node);
    }

    return node;
}

/* Return the height balance of the node */
static int get_Balance(Node *n) {
    if (!n) return 0;
    return height(n -> left) - height(n -> right);
}

static int height(Node *n) { return n ? n -> height : 0; }

/* A utility function to right rotate subtree rooted with y */
Node *right_rotate(Node *y) {
    
    Node *x, *T2;
    
    x = y -> left;
    T2 = x -> right;

    /* Perform rotation */
    x -> right = y;
    y -> left = T2;

    /* Update heights */
    y -> height = MAX(height(y -> left), height(y -> right)) + 1;
    x -> height = MAX(height(x -> left), height(x -> right)) + 1;

    /* Return new root */
    return x;
}

/* A utility function to left rotate subtree rooted with x */
Node *left_rotate(Node *x) {
    
    Node *y, *T2;
    
    y = x -> right;
    T2 = y -> left;

    /*Perform rotation */
    y -> left = x;
    x -> right = T2;

    /* Update heights */
    x -> height = MAX(height(x -> left), height(x -> right)) + 1;
    y -> height = MAX(height(y -> left), height(y -> right)) + 1;

    /* Return new root */
    return y;
}

/* Print the contents of the avl tree using the preorder traversal */
void avl_display(AVL *tree, Node *node) {
    if (node) {
        printf("%d ", node -> key);
        avl_display(tree, node -> left);
        avl_display(tree, node -> right);
    }
}

/* Delete an avl tree object */
void avl_delete(AVL *avl) {
    delete_nodes(avl -> root);
    free((void *) avl);
}

static void delete_nodes(Node *node) {

    if (node) {
        delete_nodes(node -> right);
        delete_nodes(node -> left);
        free((void *) node);
    }

}

int main(int argc, char **argv) {

    AVL *tree;

    tree = avl_init();
    avl_insert(tree, 10);
    avl_display(tree, tree -> root);
    printf("\n");
    avl_insert(tree, 20);
    avl_display(tree, tree -> root);
    printf("\n");
    avl_insert(tree, 30);
    avl_display(tree, tree -> root);
    printf("\n");   
    avl_insert(tree, 40);
    avl_display(tree, tree -> root);
    printf("\n");
    avl_insert(tree, 50);
    avl_display(tree, tree -> root);
    printf("\n");
    avl_insert(tree, 25);
    avl_display(tree, tree -> root);
    printf("\nroot = %d\ntree size = %d\n", tree -> root -> key, tree -> size);
    avl_delete(tree);

    return 0;
}
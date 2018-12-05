#ifndef __AVL__
#define __AVL__

typedef struct avltree AVL;
typedef struct node Node;

/* Creates an empty AVL tree */
AVL *avl_init();
/* Binary search */
int binary_search(AVL *, Node *, char *);
/* Returns a pointer to node */
Node *avl_get(AVL *, Node *, char *);
/* Inserts data into AVL tree */
int avl_insert(AVL *, int);
/* Prints contents of avl tree */
void avl_display(AVL *, Node *);

#endif
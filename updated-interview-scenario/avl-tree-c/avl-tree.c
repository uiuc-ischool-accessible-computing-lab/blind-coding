// AVL tree implementation in C

#include <stdio.h>
#include <stdlib.h>

/******************************************************
 *****************STRUCT DECLARATION*******************
 ******************************************************/
struct Node {
  int key;
  struct Node *left;
  struct Node *right;
  int height;
};


/******************************************************
 ****************FUNCTION DEFINITIONS******************
 ******************************************************/

/*
    Function to calculate the height of the tree

    @param N the current tree node
    @return the height of the tree from the node N
  */
int height(struct Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

/*
    Function to get the maximum integer

    @param a first integer
    @param b second integer
    @return the maximum integer
  */
int max(int a, int b) {
  return (a > b) ? a : b;
}

/*
    Function to create a new tree node

    @param key the value of the new node to be inserted
    @return the created tree node
  */
struct Node *newNode(int key) {
  struct Node *node = (struct Node *)
    malloc(sizeof(struct Node));
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

/*
    Function to do a right rotation to a node

    @param y the current tree node to be rotated
    @return the node at the original position of y
  */
struct Node *rightRotate(struct Node *y) {
  struct Node *x = y->left;
  struct Node *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

/*
    Function to do a left rotation to a node

    @param x the current tree node to be rotated
    @return the node at the original position of x
  */
struct Node *leftRotate(struct Node *x) {
  struct Node *y = x->right;
  struct Node *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

/*
    Function to get the balance factor of a node

    @param N the current tree node
    @return the balance of the node N
  */
int getBalance(struct Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

/*
    Function to insert a value into the tree

    @param node the current tree node that would be the new node's parent
    @param key the value of the new node to be inserted
    @return the current tree node
  */
struct Node *insertNode(struct Node *node, int key) {
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return (newNode(key));

  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && key < node->left->key)
    return rightRotate(node);

  if (balance < -1 && key > node->right->key)
    return leftRotate(node);

  if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

/*
    Function to insert a value into the tree

    @param node the current tree node
    @return the node with the minimum value
  */
struct Node *minValueNode(struct Node *node) {
  struct Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

/*
    Method to delete a value from the tree

    @param root the current tree node in the recursive call
    @param key the value of the new node to be deleted
    @return the current tree node
  */
struct Node *deleteNode(struct Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (key < root->key)
    root->left = deleteNode(root->left, key);

  else if (key > root->key)
    root->right = deleteNode(root->right, key);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      struct Node *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      struct Node *temp = minValueNode(root->right);

      root->key = temp->key;

      root->right = deleteNode(root->right, temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root)

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

/*
    Function to print the value of the tree nodes through preorder traversal

    @param root the current tree node in the recursive call
  */
void printPreOrder(struct Node *root) {
  if (root != NULL) {
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}

/******************************************************
 ********************MAIN FUNCTION*********************
 ******************************************************/

int main() {
  struct Node *root = NULL;

  root = insertNode(root, 2);
  root = insertNode(root, 1);
  root = insertNode(root, 7);
  root = insertNode(root, 4);
  root = insertNode(root, 5);
  root = insertNode(root, 3);
  root = insertNode(root, 8);

  printPreOrder(root);

  root = deleteNode(root, 3);

  printf("\nAfter deletion: ");
  printPreOrder(root);

  return 0;
}
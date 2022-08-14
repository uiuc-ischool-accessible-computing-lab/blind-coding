// AVL tree implementation in C++

#include <iostream>
using namespace std;

/******************************************************
 ******************CLASS DECLARATION*******************
 ******************************************************/
class Node {
   public:
  int key;
  Node *left;
  Node *right;
  int height;
};

/******************************************************
 ***************FUNCTION DECLARATIONS******************
 ******************************************************/

/*
    Wrapper function to calculate the height of the tree

    @param N the current tree node
    @return the height of the tree
  */
int height(Node *N);

/*
    Wrapper function to get the maximum integer

    @param a first integer
    @param b second integer
    @return the maximum integer
  */
int max(int a, int b);

/*
    Wrapper function to create a new tree node

    @param key the value of the new node to be inserted
    @return the created tree node
  */
Node *newNode(int key);

/*
    Wrapper function to do a right rotation to a node

    @param y the current tree node to be rotated
    @return the node at the original position of y
  */
Node *rightRotate(Node *y);

/*
    Wrapper function to do a left rotation to a node

    @param x the current tree node to be rotated
    @return the node at the original position of x
  */
Node *leftRotate(Node *x);

/*
    Wrapper function to get the balance factor of a node

    @param N the current tree node
    @return the balance of the node N
  */
int getBalanceFactor(Node *N);

/*
    Wrapper function to insert a value into the tree

    @param node the current tree node that would be the new node's parent
    @param key the value of the new node to be inserted
    @return the current tree node
  */
Node *insertNode(Node *node, int key);

/*
    Wrapper function to insert a value into the tree

    @param node the current tree node
    @return the node with the minimum value
  */
Node *nodeWithMimumValue(Node *node);

/*
    Wrapper function to delete a value from the tree

    @param root the current tree node in the recursive call
    @param key the value of the new node to be deleted
    @return the current tree node
  */
Node *deleteNode(Node *root, int key);

/*
  Prints the structure of tree in terminal

  @param root the current tree node in the recursive call
  @param indent space format
  @param last true if the current node in the recursive call is the last element of its branch
  */
void printTree(Node *root, string indent, bool last);


/******************************************************
 ********************MAIN FUNCTION*********************
 ******************************************************/ 
int main() {
  Node *root = NULL;
  root = insertNode(root, 33);
  root = insertNode(root, 13);
  root = insertNode(root, 53);
  root = insertNode(root, 9);
  root = insertNode(root, 21);
  root = insertNode(root, 61);
  root = insertNode(root, 8);
  root = insertNode(root, 11);
  printTree(root, "", true);
  root = deleteNode(root, 13);
  cout << "After deleting " << endl;
  printTree(root, "", true);
}

/******************************************************
 ****************FUNCTION DEFINITIONS******************
 ******************************************************/
int height(Node *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

Node *newNode(int key) {
  Node *node = new Node();
  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return (node);
}

Node *rightRotate(Node *y) {
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  return x;
}

Node *leftRotate(Node *x) {
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left),
          height(x->right)) +
        1;
  y->height = max(height(y->left),
          height(y->right)) +
        1;
  return y;
}

int getBalanceFactor(Node *N) {
  if (N == NULL)
    return 0;
  return height(N->left) -
       height(N->right);
}

Node *insertNode(Node *node, int key) {
  // Find the correct postion and insert the node
  if (node == NULL)
    return (newNode(key));
  if (key < node->key)
    node->left = insertNode(node->left, key);
  else if (key > node->key)
    node->right = insertNode(node->right, key);
  else
    return node;

  // Update the balance factor of each node and
  // balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));
  int balanceFactor = getBalanceFactor(node);
  if (balanceFactor > 1) {
    if (key < node->left->key) {
      return rightRotate(node);
    } else if (key > node->left->key) {
      node->left = leftRotate(node->left);
      return rightRotate(node);
    }
  }
  if (balanceFactor < -1) {
    if (key > node->right->key) {
      return leftRotate(node);
    } else if (key < node->right->key) {
      node->right = rightRotate(node->right);
      return leftRotate(node);
    }
  }
  return node;
}

Node *nodeWithMimumValue(Node *node) {
  Node *current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

Node *deleteNode(Node *root, int key) {
  // Find the node and delete it
  if (root == NULL)
    return root;
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    if ((root->left == NULL) ||
      (root->right == NULL)) {
      Node *temp = root->left ? root->left : root->right;
      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      Node *temp = nodeWithMimumValue(root->right);
      root->key = temp->key
      root->right = deleteNode(root->right,
                   temp->key);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));
  int balanceFactor = getBalanceFactor(root);
  if (balanceFactor > 1) {
    if (getBalanceFactor(root->left) >= 0) {
      return rightRotate(root);
    } else {
      root->left = leftRotate(root->left);
      return rightRotate(root);
    }
  }
  if (balanceFactor < -1) {
    if (getBalanceFactor(root->right) <= 0) {
      return leftRotate(root);
    } else {
      root->right = rightRotate(root->right);
      return leftRotate(root);
    }
  }
  return root;
}

void printTree(Node *root, string indent, bool last) {
  if (root != nullptr) {
    cout << indent;
    if (last) {
      cout << "R----";
      indent += "   ";
    } else {
      cout << "L----";
      indent += "|  ";
    }
    cout << root->key << endl;
    printTree(root->left, indent, false);
    printTree(root->right, indent, true);
  }
}
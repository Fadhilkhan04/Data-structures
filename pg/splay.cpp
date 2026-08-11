#include <iostream>
using namespace std;

// Node structure
struct Node
{
  int data;
  Node *left;
  Node *right;
};

// Create a new node
Node *createNode(int value)
{
  Node *newNode = new Node();

  newNode->data = value;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

// Right Rotation
Node *rightRotate(Node *x)
{
  Node *y = x->left;

  x->left = y->right;
  y->right = x;

  return y;
}

// Left Rotation
Node *leftRotate(Node *x)
{
  Node *y = x->right;

  x->right = y->left;
  y->left = x;

  return y;
}

// Splay Operation
Node *splay(Node *root, int key)
{
  // Tree is empty or key is already at root
  if (root == NULL || root->data == key)
    return root;

  // Key is in left subtree
  if (key < root->data)
  {
    // Key does not exist
    if (root->left == NULL)
      return root;

    // Zig-Zig (Left-Left)
    if (key < root->left->data)
    {
      root->left->left = splay(root->left->left, key);

      root = rightRotate(root);
    }

    // Zig-Zag (Left-Right)
    else if (key > root->left->data)
    {
      root->left->right = splay(root->left->right, key);

      if (root->left->right != NULL)
        root->left = leftRotate(root->left);
    }

    // Zig
    if (root->left == NULL)
      return root;

    return rightRotate(root);
  }

  // Key is in right subtree
  else
  {
    // Key does not exist
    if (root->right == NULL)
      return root;

    // Zig-Zig (Right-Right)
    if (key > root->right->data)
    {
      root->right->right = splay(root->right->right, key);

      root = leftRotate(root);
    }

    // Zig-Zag (Right-Left)
    else if (key < root->right->data)
    {
      root->right->left = splay(root->right->left, key);

      if (root->right->left != NULL)
        root->right = rightRotate(root->right);
    }

    // Zig
    if (root->right == NULL)
      return root;

    return leftRotate(root);
  }
}

// Insert a node
Node *insert(Node *root, int key)
{
  // Empty tree
  if (root == NULL)
    return createNode(key);

  // Splay the key
  root = splay(root, key);

  // Duplicate value
  if (root->data == key)
  {
    cout << "Value already exists!\n";
    return root;
  }

  Node *newNode = createNode(key);

  // Key is smaller than root
  if (key < root->data)
  {
    newNode->right = root;
    newNode->left = root->left;

    root->left = NULL;
  }

  // Key is greater than root
  else
  {
    newNode->left = root;
    newNode->right = root->right;

    root->right = NULL;
  }

  return newNode;
}

// Search for a node
Node *search(Node *root, int key)
{
  if (root == NULL)
  {
    cout << "Tree is empty!\n";
    return NULL;
  }

  // Splay the searched value
  root = splay(root, key);

  if (root->data == key)
    cout << "Value found!\n";
  else
    cout << "Value not found!\n";

  return root;
}

// Delete a node
Node *deleteNode(Node *root, int key)
{
  if (root == NULL)
  {
    cout << "Tree is empty!\n";
    return NULL;
  }

  // Bring the node to be deleted to root
  root = splay(root, key);

  // Value not found
  if (root->data != key)
  {
    cout << "Value not found!\n";
    return root;
  }

  Node *temp = root;

  // No left subtree
  if (root->left == NULL)
  {
    root = root->right;
  }

  // Left subtree exists
  else
  {
    Node *leftSubtree = root->left;

    // Splay the largest node of left subtree
    leftSubtree = splay(leftSubtree, key);

    // Attach right subtree
    leftSubtree->right = root->right;

    root = leftSubtree;
  }

  delete temp;

  cout << "Value deleted successfully!\n";

  return root;
}

// Inorder traversal
void inorder(Node *root)
{
  if (root == NULL)
    return;

  inorder(root->left);

  cout << root->data << " ";

  inorder(root->right);
}

// Display tree structure
void display(Node *root, int space = 0)
{
  if (root == NULL)
    return;

  space += 5;

  // Display right subtree
  display(root->right, space);

  cout << endl;

  for (int i = 5; i < space; i++)
    cout << " ";

  cout << root->data << endl;

  // Display left subtree
  display(root->left, space);
}

// Main function
int main()
{
  Node *root = NULL;

  int choice;
  int value;

  do
  {
    cout << "\n===== SPLAY TREE =====\n";
    cout << "1. Insert\n";
    cout << "2. Search\n";
    cout << "3. Delete\n";
    cout << "4. Display Inorder\n";
    cout << "5. Display Tree\n";
    cout << "6. Exit\n";

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter value: ";
      cin >> value;

      root = insert(root, value);
      break;

    case 2:
      cout << "Enter value to search: ";
      cin >> value;

      root = search(root, value);
      break;

    case 3:
      cout << "Enter value to delete: ";
      cin >> value;

      root = deleteNode(root, value);
      break;

    case 4:
      cout << "Inorder Traversal: ";
      inorder(root);
      cout << endl;
      break;

    case 5:
      cout << "\nSplay Tree:\n";
      display(root);
      cout << endl;
      break;

    case 6:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice!\n";
    }

  } while (choice != 6);

  return 0;
}
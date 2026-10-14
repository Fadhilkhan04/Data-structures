
#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *left, *right;
};

Node *root = nullptr;

Node *createNode(int x)
{
  Node *temp = new Node;
  temp->data = x;
  temp->left = nullptr;
  temp->right = nullptr;
  return temp;
}

// Right rotation
Node *rightRotate(Node *root)
{
  Node *temp = root->left;
  root->left = temp->right;
  temp->right = root;
  return temp;
}

// Left rotation
Node *leftRotate(Node *root)
{
  Node *temp = root->right;
  root->right = temp->left;
  temp->left = root;
  return temp;
}

// Splay operation
Node *splay(Node *root, int x)
{
  if (root == nullptr || root->data == x)
    return root;

  // Key is in the left subtree
  if (x < root->data)
  {
    if (root->left == nullptr)
      return root;

    // Zig-Zig: Left Left
    if (x < root->left->data)
    {
      root->left->left =
          splay(root->left->left, x);

      root = rightRotate(root);
    }

    // Zig-Zag: Left Right
    else if (x > root->left->data)
    {
      root->left->right =
          splay(root->left->right, x);

      if (root->left->right != nullptr)
        root->left = leftRotate(root->left);
    }

    if (root->left == nullptr)
      return root;
    else
      return rightRotate(root);
  }

  // Key is in the right subtree
  else
  {
    if (root->right == nullptr)
      return root;

    // Zig-Zag: Right Left
    if (x < root->right->data)
    {
      root->right->left =
          splay(root->right->left, x);

      if (root->right->left != nullptr)
        root->right = rightRotate(root->right);
    }

    // Zig-Zig: Right Right
    else if (x > root->right->data)
    {
      root->right->right =
          splay(root->right->right, x);

      root = leftRotate(root);
    }

    if (root->right == nullptr)
      return root;
    else
      return leftRotate(root);
  }
}

// Insertion
void insert(int x)
{
  if (root == nullptr)
  {
    root = createNode(x);
    return;
  }

  root = splay(root, x);

  if (root->data == x)
  {
    cout << "Duplicate element\n";
    return;
  }

  Node *temp = createNode(x);

  if (x < root->data)
  {
    temp->right = root;
    temp->left = root->left;
    root->left = nullptr;
  }
  else
  {
    temp->left = root;
    temp->right = root->right;
    root->right = nullptr;
  }

  root = temp;
}

// Searching
void search(int x)
{
  root = splay(root, x);

  if (root != nullptr && root->data == x)
    cout << "Element found\n";
  else
    cout << "Element not found\n";
}

// Deletion
void deleteNode(int x)
{
  if (root == nullptr)
  {
    cout << "Tree is empty\n";
    return;
  }

  root = splay(root, x);

  if (root->data != x)
  {
    cout << "Element not found\n";
    return;
  }

  Node *temp = root;

  if (root->left == nullptr)
  {
    root = root->right;
  }
  else
  {
    Node *rightSubtree = root->right;

    root = splay(root->left, x);
    root->right = rightSubtree;
  }

  delete temp;
  cout << "Element deleted\n";
}

// Display tree sideways
void displayTree(Node *root, int level = 0)
{
  if (root == nullptr)
    return;

  displayTree(root->right, level + 1);

  for (int i = 0; i < level; i++)
    cout << "    ";

  cout << root->data << endl;

  displayTree(root->left, level + 1);
}

int main()
{
  int choice, x;

  while (true)
  {
    cout << "\n1. Insert"
         << "\n2. Delete"
         << "\n3. Search"
         << "\n4. Display Tree"
         << "\n5. Exit\n";

    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter element: ";
      cin >> x;
      insert(x);
      break;

    case 2:
      cout << "Enter element to delete: ";
      cin >> x;
      deleteNode(x);
      break;

    case 3:
      cout << "Enter element to search: ";
      cin >> x;
      search(x);
      break;

    case 4:
      if (root == nullptr)
        cout << "Tree is empty\n";
      else
        displayTree(root);
      break;

    case 5:
      return 0;

    default:
      cout << "Invalid choice\n";
    }
  }
}

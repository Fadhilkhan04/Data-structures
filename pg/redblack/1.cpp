#include <iostream>
using namespace std;

struct Node
{
  int data;
  char color; // R = Red, B = Black
  Node *left;
  Node *right;
  Node *parent;
};

// --------------------------------------------------
// CREATE NEW NODE
// --------------------------------------------------

Node *createNode(int data)
{
  Node *newNode = new Node;

  newNode->data = data;
  newNode->color = 'R'; // New node is always Red
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->parent = NULL;

  return newNode;
}

// --------------------------------------------------
// LEFT ROTATION
// --------------------------------------------------

void leftRotate(Node *&root, Node *x)
{
  Node *y = x->right;

  x->right = y->left;

  if (y->left != NULL)
    y->left->parent = x;

  y->parent = x->parent;

  if (x->parent == NULL)
  {
    root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }

  y->left = x;
  x->parent = y;
}

// --------------------------------------------------
// RIGHT ROTATION
// --------------------------------------------------

void rightRotate(Node *&root, Node *x)
{
  Node *y = x->left;

  x->left = y->right;

  if (y->right != NULL)
    y->right->parent = x;

  y->parent = x->parent;

  if (x->parent == NULL)
  {
    root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }

  y->right = x;
  x->parent = y;
}

// --------------------------------------------------
// FIX INSERTION
// --------------------------------------------------

void fixInsert(Node *&root, Node *z)
{
  while (z != root && z->parent->color == 'R')
  {
    Node *parent = z->parent;
    Node *grandparent = parent->parent;

    // Parent is left child
    if (parent == grandparent->left)
    {
      Node *uncle = grandparent->right;

      // Case 1: Uncle is Red
      if (uncle != NULL && uncle->color == 'R')
      {
        parent->color = 'B';
        uncle->color = 'B';
        grandparent->color = 'R';

        z = grandparent;
      }
      else
      {
        // Case 2: LR
        if (z == parent->right)
        {
          z = parent;
          leftRotate(root, z);

          parent = z->parent;
          grandparent = parent->parent;
        }

        // Case 3: LL
        parent->color = 'B';
        grandparent->color = 'R';

        rightRotate(root, grandparent);
      }
    }

    // Parent is right child
    else
    {
      Node *uncle = grandparent->left;

      // Case 1: Uncle is Red
      if (uncle != NULL && uncle->color == 'R')
      {
        parent->color = 'B';
        uncle->color = 'B';
        grandparent->color = 'R';

        z = grandparent;
      }
      else
      {
        // Case 2: RL
        if (z == parent->left)
        {
          z = parent;
          rightRotate(root, z);

          parent = z->parent;
          grandparent = parent->parent;
        }

        // Case 3: RR
        parent->color = 'B';
        grandparent->color = 'R';

        leftRotate(root, grandparent);
      }
    }
  }

  // Root must always be Black
  root->color = 'B';
}

// --------------------------------------------------
// INSERT
// --------------------------------------------------

void insert(Node *&root, int data)
{
  Node *newNode = createNode(data);

  // Empty tree
  if (root == NULL)
  {
    root = newNode;
    root->color = 'B';
    return;
  }

  Node *parent = NULL;
  Node *current = root;

  // Normal BST insertion
  while (current != NULL)
  {
    parent = current;

    if (data < current->data)
    {
      current = current->left;
    }
    else if (data > current->data)
    {
      current = current->right;
    }
    else
    {
      cout << "Duplicate value not allowed.\n";
      delete newNode;
      return;
    }
  }

  newNode->parent = parent;

  if (data < parent->data)
    parent->left = newNode;
  else
    parent->right = newNode;

  // Fix Red-Black properties
  fixInsert(root, newNode);
}

// --------------------------------------------------
// SEARCH
// --------------------------------------------------

Node *search(Node *root, int data)
{
  Node *current = root;

  while (current != NULL)
  {
    if (data == current->data)
      return current;

    if (data < current->data)
      current = current->left;
    else
      current = current->right;
  }

  return NULL;
}

// --------------------------------------------------
// FIND MINIMUM NODE
// --------------------------------------------------

Node *minimum(Node *node)
{
  Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// --------------------------------------------------
// TRANSPLANT
// Replaces one subtree with another
// --------------------------------------------------

void transplant(Node *&root, Node *u, Node *v)
{
  if (u->parent == NULL)
  {
    root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }

  if (v != NULL)
    v->parent = u->parent;
}

// --------------------------------------------------
// FIX DELETION
// --------------------------------------------------

void fixDelete(Node *&root, Node *x, Node *parent)
{
  while (x != root && (x == NULL || x->color == 'B'))
  {
    // x is left child
    if (x == (parent != NULL ? parent->left : NULL))
    {
      Node *sibling = parent->right;

      // Case 1: Sibling is Red
      if (sibling != NULL && sibling->color == 'R')
      {
        sibling->color = 'B';
        parent->color = 'R';

        leftRotate(root, parent);

        sibling = parent->right;
      }

      // Case 2, 3 and 4
      if (sibling == NULL)
      {
        x = parent;
        parent = x->parent;
      }
      else
      {
        bool leftBlack =
            (sibling->left == NULL ||
             sibling->left->color == 'B');

        bool rightBlack =
            (sibling->right == NULL ||
             sibling->right->color == 'B');

        // Case 2: Both sibling children are Black
        if (leftBlack && rightBlack)
        {
          sibling->color = 'R';

          x = parent;
          parent = x->parent;
        }
        else
        {
          // Case 3: Near child is Red,
          // far child is Black
          if (sibling->right == NULL ||
              sibling->right->color == 'B')
          {
            if (sibling->left != NULL)
              sibling->left->color = 'B';

            sibling->color = 'R';

            rightRotate(root, sibling);

            sibling = parent->right;
          }

          // Case 4: Far child is Red
          sibling->color = parent->color;
          parent->color = 'B';

          if (sibling->right != NULL)
            sibling->right->color = 'B';

          leftRotate(root, parent);

          x = root;
          parent = NULL;
        }
      }
    }

    // x is right child
    else
    {
      Node *sibling = parent->left;

      // Case 1: Sibling is Red
      if (sibling != NULL && sibling->color == 'R')
      {
        sibling->color = 'B';
        parent->color = 'R';

        rightRotate(root, parent);

        sibling = parent->left;
      }

      // Case 2, 3 and 4
      if (sibling == NULL)
      {
        x = parent;
        parent = x->parent;
      }
      else
      {
        bool leftBlack =
            (sibling->left == NULL ||
             sibling->left->color == 'B');

        bool rightBlack =
            (sibling->right == NULL ||
             sibling->right->color == 'B');

        // Case 2: Both sibling children are Black
        if (leftBlack && rightBlack)
        {
          sibling->color = 'R';

          x = parent;
          parent = x->parent;
        }
        else
        {
          // Case 3: Near child is Red,
          // far child is Black
          if (sibling->left == NULL ||
              sibling->left->color == 'B')
          {
            if (sibling->right != NULL)
              sibling->right->color = 'B';

            sibling->color = 'R';

            leftRotate(root, sibling);

            sibling = parent->left;
          }

          // Case 4: Far child is Red
          sibling->color = parent->color;
          parent->color = 'B';

          if (sibling->left != NULL)
            sibling->left->color = 'B';

          rightRotate(root, parent);

          x = root;
          parent = NULL;
        }
      }
    }
  }

  if (x != NULL)
    x->color = 'B';
}

// --------------------------------------------------
// DELETE
// --------------------------------------------------

void deleteNode(Node *&root, int data)
{
  Node *z = search(root, data);

  if (z == NULL)
  {
    cout << "Value not found.\n";
    return;
  }

  Node *y = z;
  Node *x = NULL;

  char originalColor = y->color;

  // Case 1: No left child
  if (z->left == NULL)
  {
    x = z->right;

    Node *xParent = z->parent;

    transplant(root, z, z->right);

    if (originalColor == 'B')
      fixDelete(root, x, xParent);
  }

  // Case 2: No right child
  else if (z->right == NULL)
  {
    x = z->left;

    Node *xParent = z->parent;

    transplant(root, z, z->left);

    if (originalColor == 'B')
      fixDelete(root, x, xParent);
  }

  // Case 3: Two children
  else
  {
    y = minimum(z->right);

    originalColor = y->color;

    x = y->right;

    if (y->parent == z)
    {
      if (x != NULL)
        x->parent = y;

      if (originalColor == 'B')
        fixDelete(root, x, y);
    }
    else
    {
      Node *yParent = y->parent;

      transplant(root, y, y->right);

      y->right = z->right;
      y->right->parent = y;

      if (originalColor == 'B')
        fixDelete(root, x, yParent);
    }

    transplant(root, z, y);

    y->left = z->left;
    y->left->parent = y;

    y->color = z->color;
  }

  delete z;

  cout << "Value deleted successfully.\n";
}

// --------------------------------------------------
// INORDER TRAVERSAL
// --------------------------------------------------

void inorder(Node *root)
{
  if (root == NULL)
    return;

  inorder(root->left);

  cout << root->data << "(" << root->color << ") ";

  inorder(root->right);
}

// --------------------------------------------------
// DISPLAY TREE
// --------------------------------------------------

void display(Node *root, int space = 0)
{
  if (root == NULL)
    return;

  space += 6;

  // Display right subtree first
  display(root->right, space);

  cout << endl;

  for (int i = 6; i < space; i++)
    cout << " ";

  cout << root->data << "(" << root->color << ")";

  // Display left subtree
  display(root->left, space);
}

// --------------------------------------------------
// MAIN
// --------------------------------------------------

int main()
{
  Node *root = NULL;

  int choice;
  int value;

  do
  {
    cout << "\n\n=================================\n";
    cout << "       RED-BLACK TREE\n";
    cout << "=================================\n";
    cout << "1. Insert\n";
    cout << "2. Delete\n";
    cout << "3. Search\n";
    cout << "4. Inorder Traversal\n";
    cout << "5. Display Tree\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "Enter value to insert: ";
      cin >> value;

      insert(root, value);

      cout << "Value inserted successfully.\n";
      break;

    case 2:
      cout << "Enter value to delete: ";
      cin >> value;

      deleteNode(root, value);
      break;

    case 3:
    {
      cout << "Enter value to search: ";
      cin >> value;

      Node *result = search(root, value);

      if (result != NULL)
      {
        cout << "Value found.\n";
        cout << "Data: " << result->data << endl;
        cout << "Color: " << result->color << endl;
      }
      else
      {
        cout << "Value not found.\n";
      }

      break;
    }

    case 4:
      cout << "\nInorder Traversal:\n";
      inorder(root);
      cout << endl;
      break;

    case 5:
      cout << "\nRed-Black Tree:\n";
      display(root);
      cout << endl;
      break;

    case 6:
      cout << "Exiting...\n";
      break;

    default:
      cout << "Invalid choice.\n";
    }

  } while (choice != 6);

  return 0;
}
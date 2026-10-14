#include <iostream>
using namespace std;

struct Node
{
  int data;
  char color;
  Node *left, *right, *parent;
};

Node *root = nullptr;

// Statistics
int insertCount = 0;
int leftRotations = 0;
int rightRotations = 0;
int recolorCount = 0;
int validationCount = 0;
int validCount = 0;
int invalidCount = 0;

// Change color and count actual changes
void setColor(Node *node, char color)
{
  if (node != nullptr && node->color != color)
  {
    node->color = color;
    recolorCount++;
  }
}

char getColor(Node *node)
{
  if (node == nullptr)
    return 'B';

  return node->color;
}

Node *createNode(int x)
{
  Node *temp = new Node;

  temp->data = x;
  temp->color = 'R';
  temp->left = nullptr;
  temp->right = nullptr;
  temp->parent = nullptr;

  return temp;
}

// Left rotation
void leftRotate(Node *x)
{
  leftRotations++;

  Node *y = x->right;
  x->right = y->left;

  if (y->left != nullptr)
    y->left->parent = x;

  y->parent = x->parent;

  if (x->parent == nullptr)
    root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;

  y->left = x;
  x->parent = y;
}

// Right rotation
void rightRotate(Node *y)
{
  rightRotations++;

  Node *x = y->left;
  y->left = x->right;

  if (x->right != nullptr)
    x->right->parent = y;

  x->parent = y->parent;

  if (y->parent == nullptr)
    root = x;
  else if (y == y->parent->left)
    y->parent->left = x;
  else
    y->parent->right = x;

  x->right = y;
  y->parent = x;
}

// Fix Red-Black Tree after insertion
void fixInsert(Node *z)
{
  while (z != root &&
         getColor(z->parent) == 'R')
  {

    Node *parent = z->parent;
    Node *grandparent = parent->parent;

    if (parent == grandparent->left)
    {
      Node *uncle = grandparent->right;

      // Case 1: Uncle is red
      if (getColor(uncle) == 'R')
      {
        setColor(parent, 'B');
        setColor(uncle, 'B');
        setColor(grandparent, 'R');

        z = grandparent;
      }
      else
      {
        // Case 2: Left-Right
        if (z == parent->right)
        {
          z = parent;
          leftRotate(z);
        }

        // Case 3: Left-Left
        setColor(z->parent, 'B');
        setColor(z->parent->parent, 'R');
        rightRotate(z->parent->parent);
      }
    }
    else
    {
      Node *uncle = grandparent->left;

      // Case 1: Uncle is red
      if (getColor(uncle) == 'R')
      {
        setColor(parent, 'B');
        setColor(uncle, 'B');
        setColor(grandparent, 'R');

        z = grandparent;
      }
      else
      {
        // Case 2: Right-Left
        if (z == parent->left)
        {
          z = parent;
          rightRotate(z);
        }

        // Case 3: Right-Right
        setColor(z->parent, 'B');
        setColor(z->parent->parent, 'R');
        leftRotate(z->parent->parent);
      }
    }
  }

  setColor(root, 'B');
}

// Insert a node
void insert(int x)
{
  Node *temp = createNode(x);
  Node *parent = nullptr;
  Node *curr = root;

  while (curr != nullptr)
  {
    parent = curr;

    if (x < curr->data)
      curr = curr->left;
    else if (x > curr->data)
      curr = curr->right;
    else
    {
      cout << "Duplicate element\n";
      delete temp;
      return;
    }
  }

  temp->parent = parent;

  if (parent == nullptr)
    root = temp;
  else if (x < parent->data)
    parent->left = temp;
  else
    parent->right = temp;

  insertCount++;

  fixInsert(temp);

  cout << "Element inserted\n";
}

// Validate all Red-Black properties recursively
int validate(Node *node, long long low,
             long long high, bool &ok)
{
  if (node == nullptr)
    return 1; // Null leaves are black

  // Check BST ordering
  if (node->data <= low || node->data >= high)
    ok = false;

  // Check node color
  if (node->color != 'R' && node->color != 'B')
    ok = false;

  // Check red node's children are black
  if (node->color == 'R')
  {
    if (getColor(node->left) == 'R' ||
        getColor(node->right) == 'R')
      ok = false;
  }

  // Check parent pointers
  if (node->left != nullptr &&
      node->left->parent != node)
    ok = false;

  if (node->right != nullptr &&
      node->right->parent != node)
    ok = false;

  int leftHeight = validate(
      node->left, low, node->data, ok);

  int rightHeight = validate(
      node->right, node->data, high, ok);

  // Check equal black height
  if (leftHeight != rightHeight)
    ok = false;

  return leftHeight +
         (node->color == 'B' ? 1 : 0);
}

void checkValidation()
{
  validationCount++;

  bool ok = true;

  // Root must be black
  if (root != nullptr && root->color != 'B')
    ok = false;

  validate(root, -2147483649LL,
           2147483648LL, ok);

  if (ok)
  {
    cout << "VALID Red-Black Tree\n";
    cout << "All properties are satisfied\n";
    validCount++;
  }
  else
  {
    cout << "INVALID Red-Black Tree\n";
    cout << "One or more properties are violated\n";
    invalidCount++;
  }
}

// Display tree sideways
void displayTree(Node *node, int level = 0)
{
  if (node == nullptr)
    return;

  displayTree(node->right, level + 1);

  for (int i = 0; i < level; i++)
    cout << "    ";

  cout << node->data
       << "(" << node->color << ")" << endl;

  displayTree(node->left, level + 1);
}

// Show statistics
void showStatistics()
{
  cout << "\n--- RED-BLACK TREE STATISTICS ---\n";

  cout << "Successful insertions: "
       << insertCount << endl;

  cout << "Left rotations: "
       << leftRotations << endl;

  cout << "Right rotations: "
       << rightRotations << endl;

  cout << "Total rotations: "
       << leftRotations + rightRotations << endl;

  cout << "Recolor operations: "
       << recolorCount << endl;

  cout << "Validation attempts: "
       << validationCount << endl;

  cout << "Valid results: "
       << validCount << endl;

  cout << "Invalid results: "
       << invalidCount << endl;
}

int main()
{
  int choice, x;

  while (true)
  {
    cout << "\n1. Insert"
         << "\n2. Display Tree"
         << "\n3. Validate Red-Black Tree"
         << "\n4. Statistics"
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
      if (root == nullptr)
        cout << "Tree is empty\n";
      else
        displayTree(root);
      break;

    case 3:
      checkValidation();
      break;

    case 4:
      showStatistics();
      break;

    case 5:
      return 0;

    default:
      cout << "Invalid choice\n";
    }
  }
}

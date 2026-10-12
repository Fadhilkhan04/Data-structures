#include <iostream>
using namespace std;

struct Node
{
  int data;
  int height;
  Node *left;
  Node *right;
};

Node *root = nullptr;

int getHeight(Node *root)
{
  if (root == nullptr)
  {
    return 0;
  }
  return root->height;
}

int getBalanceFactor(Node *root)
{
  if (root == nullptr)
  {
    return 0;
  }
  return getHeight(root->left) - getHeight(root->right);
}

Node *createNode(int x)
{
  Node *newNode = new Node();
  newNode->data = x;
  newNode->left = nullptr;
  newNode->right = nullptr;
  newNode->height = 1;
  return newNode;
}

Node *findMin(Node *root)
{
  while (root->left != nullptr)
  {
    root = root->left;
  }
  return root;
}

Node *rightRotate(Node *y)
{
  Node *x = y->left;
  Node *temp = x->right;

  x->right = y;
  y->left = temp;

  y->height = 1 + max(getHeight(y->left), getHeight(y->right));
  x->height = 1 + max(getHeight(x->left), getHeight(x->right));

  return x;
}

Node *leftRotate(Node *x)
{
  Node *y = x->right;
  Node *temp = y->left;

  y->left = x;
  x->right = temp;

  x->height = 1 + max(getHeight(x->left), getHeight(x->right));
  y->height = 1 + max(getHeight(y->left), getHeight(y->right));

  return y;
}

Node *insert(Node *root, int x)
{
  if (root == nullptr)
  {
    return createNode(x);
  }
  if (x < root->data)
  {
    root->left = insert(root->left, x);
  }
  else if (x > root->data)
  {
    root->right = insert(root->right, x);
  }
  else
  {
    return root;
  }

  root->height = 1 + max(getHeight(root->left), getHeight(root->right));
  int balance = getBalanceFactor(root);

  // ll case
  if (balance > 1 && x < root->left->data)
  {
    return rightRotate(root);
  }
  // rr case
  if (balance < -1 && x > root->right->data)
  {
    return leftRotate(root);
  }
  // lr
  if (balance > 1 && x > root->left->data)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }
  // rl
  if (balance < -1 && x < root->right->data)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

Node *deleteNode(Node *root, int x)
{
  if (root == nullptr)
    return nullptr;

  if (x < root->data)
    root->left = deleteNode(root->left, x);
  else if (x > root->data)
    root->right = deleteNode(root->right, x);
  /* else
  {
    if (root->left == nullptr ||
        root->right == nullptr)
    {
      Node *temp;

      if (root->left != nullptr)
        temp = root->left;
      else
        temp = root->right;

      delete root;
      return temp;
    }

    Node *temp = findMin(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  } */
  else
  {
    if (root->left == nullptr)
    {
      Node *temp = root->right;
      delete root;
      return temp;
    }
    else if (root->right == nullptr)
    {
      Node *temp = root->left;
      delete root;
      return temp;
    }
    Node *temp = findMin(root->right);
    root->data = temp->data;
    root->right = deleteNode(root->right, temp->data);
  }

  if (root == nullptr)
    return nullptr;

  root->height = 1 + max(getHeight(root->left),
                         getHeight(root->right));

  int balance = getBalanceFactor(root);

  // LL Case
  if (balance > 1 && getBalanceFactor(root->left) >= 0)
    return rightRotate(root);

  // LR Case
  if (balance > 1 && getBalanceFactor(root->left) < 0)
  {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  // RR Case
  if (balance < -1 && getBalanceFactor(root->right) <= 0)
    return leftRotate(root);

  // RL Case
  if (balance < -1 && getBalanceFactor(root->right) > 0)
  {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}

Node *search(Node *root, int x)
{
  if (root == nullptr || root->data == x)
  {
    return root;
  }

  if (x < root->data)
  {
    return search(root->left, x);
  }
  return search(root->right, x);
}

void display(Node *root, int level = 0)
{
  if (root == nullptr)
  {
    return;
  }
  display(root->right, level + 1);

  for (int i = 0; i < level; i++)
  {
    cout << "   ";
  }
  cout << root->data << endl;
  display(root->left, level + 1);
}

int main()
{
  int ch, x;

  while (true)
  {
    cout << "\n1. Insert";
    cout << "\n2. Delete";
    cout << "\n3. Search";
    cout << "\n4. Display Tree";
    cout << "\n5. Exit";
    cout << "\nEnter choice: ";
    cin >> ch;

    switch (ch)
    {
    case 1:
      cout << "Enter value: ";
      cin >> x;
      root = insert(root, x);
      break;

    case 2:
      cout << "Enter value to delete: ";
      cin >> x;

      if (search(root, x) != nullptr)
      {
        root = deleteNode(root, x);
        cout << "Deleted successfully\n";
      }
      else
      {
        cout << "Value not found\n";
      }
      break;

    case 3:
      cout << "Enter value to search: ";
      cin >> x;

      if (search(root, x) != nullptr)
        cout << "Value found\n";
      else
        cout << "Value not found\n";
      break;

    case 4:
      display(root);
      break;

    case 5:
      cout << "Exiting program...\n";
      return 0;

    default:
      cout << "Invalid choice\n";
    }
  }
}

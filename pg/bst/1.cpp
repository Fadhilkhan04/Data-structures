#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *left;
  Node *right;
};

Node *root = nullptr;

Node *createNode(int x)
{
  Node *newNode = new Node();
  newNode->data = x;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
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

Node *findMin(Node *root)
{
  while (root->left != nullptr)
  {
    root = root->left;
  }
  return root;
}

Node *deleteNode(Node *root, int x)
{
  if (root == nullptr)
    return nullptr;

  if (x < root->data)
  {
    root->left = deleteNode(root->left, x);
  }
  else if (x > root->data)
  {
    root->right = deleteNode(root->right, x);
  }
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
  return root;
}

void display(Node *root, int level = 0)
{
  if (root == nullptr)
    return;

  display(root->right, level + 1);

  for (int i = 0; i < level; i++)
    cout << "    ";

  cout << root->data << endl;

  display(root->left, level + 1);
}

void inorder(Node *root)
{
  if (root != nullptr)
  {
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
  }
}

void preorder(Node *root)
{
  if (root != nullptr)
  {
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
  }
}

void postorder(Node *root)
{
  if (root != nullptr)
  {
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
  }
}

int main()
{
  int ch, x;

  while (true)
  {
    cout << "\n1. Insert";
    cout << "\n2. Delete";
    cout << "\n3. Search";
    cout << "\n4. Display Traversals";
    cout << "\n5. Display Tree";
    cout << "\n6. Exit";
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
      cout << "Inorder: ";
      inorder(root);
      cout << "\nPreorder: ";
      preorder(root);
      cout << "\nPostorder: ";
      postorder(root);
      cout << endl;
      break;

    case 5:
      display(root);
      break;

    case 6:
      cout << "Exiting program...\n";
      return 0;

    default:
      cout << "Invalid choice\n";
    }
  }

  return 0;
}

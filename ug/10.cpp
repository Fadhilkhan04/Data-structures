#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *left;
  Node *right;
  int height;
};

int max(int a, int b)
{
  return (a > b) ? a : b;
}

int height(Node *node)
{
  if (node == NULL)
    return 0;
  return node->height;
}
Node *createNode(int data)
{
  Node *newNode = new Node();
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  newNode->height = 1;
  return newNode;
}
Node *rotateRight(Node *y)
{
  Node *x = y->left;
  Node *T2 = x->right;
  x->right = y;
  y->left = T2;
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}
Node *rotateLeft(Node *x)
{
  Node *y = x->right;
  Node *T2 = y->left;
  y->left = x;
  x->right = T2;
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}
int getBalanceFactor(Node *node)
{
  if (node == NULL)
    return 0;
  return height(node->left) - height(node->right);
}
Node *minValueNode(Node *node)
{
  Node *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

Node *insert(Node *node, int data)
{
  if (node == NULL)
    return createNode(data);
  if (data < node->data)
    node->left = insert(node->left, data);
  else if (data > node->data)
    node->right = insert(node->right, data);
  else
    return node;
  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalanceFactor(node);
  if (balance > 1)
  {
    if (data < node->left->data)
      return rotateRight(node);
    else if (data > node->left->data)
    {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
  }
  if (balance < -1)
  {
    if (data > node->right->data)
      return rotateLeft(node);
    else if (data < node->right->data)
    {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
  }
  return node;
}
Node *deleteNode(Node *root, int data)
{
  if (root == NULL)
    return root;

  // Perform standard BST deletion
  if (data < root->data)
    root->left = deleteNode(root->left, data);

  else if (data > root->data)
    root->right = deleteNode(root->right, data);

  else
  {
    // Node with only one child or no child
    if ((root->left == NULL) || (root->right == NULL))
    {
      Node *temp;

      if (root->left != NULL)
        temp = root->left;
      else
        temp = root->right;

      // No child
      if (temp == NULL)
      {
        temp = root;
        root = NULL;
      }
      else
      {
        // One child
        *root = *temp;
      }

      delete temp;
    }

    // Node with two children
    else
    {
      Node *temp = minValueNode(root->right);

      root->data = temp->data;

      root->right = deleteNode(root->right, temp->data);
    }
  }

  // If tree had only one node
  if (root == NULL)
    return root;

  // Update height
  root->height = 1 + max(height(root->left), height(root->right));

  // Get balance factor
  int balance = getBalanceFactor(root);

  // LL Case
  if (balance > 1 && getBalanceFactor(root->left) >= 0)
    return rotateRight(root);

  // LR Case
  if (balance > 1 && getBalanceFactor(root->left) < 0)
  {
    root->left = rotateLeft(root->left);
    return rotateRight(root);
  }

  // RR Case
  if (balance < -1 && getBalanceFactor(root->right) <= 0)
    return rotateLeft(root);

  // RL Case
  if (balance < -1 && getBalanceFactor(root->right) > 0)
  {
    root->right = rotateRight(root->right);
    return rotateLeft(root);
  }

  return root;
}

void inorderTraversal(Node *node)
{
  if (node == NULL)
    return;
  inorderTraversal(node->left);
  cout << node->data << " ";
  inorderTraversal(node->right);
}
void preorderTraversal(Node *node)
{
  if (node == NULL)
    return;
  cout << node->data << " ";
  preorderTraversal(node->left);
  preorderTraversal(node->right);
}
void postorderTraversal(Node *node)
{
  if (node == NULL)
    return;
  postorderTraversal(node->left);
  postorderTraversal(node->right);
  cout << node->data << " ";
}
int main()
{
  Node *root = NULL;
  int numElements, data;
  cout << "AVL TREE" << endl;
  cout << "Enter the number of elements to insert: ";
  cin >> numElements;
  for (int i = 0; i < numElements; i++)
  {
    cout << "Enter element " << i + 1 << ": ";
    cin >> data;
    root = insert(root, data);
  }

  cout << "Inorder traversal: ";
  inorderTraversal(root);
  cout << endl;
  cout << "Preorder traversal: ";
  preorderTraversal(root);
  cout << endl;
  cout << "Postorder traversal: ";
  postorderTraversal(root);
  cout << endl
       << endl;
  int del;

  cout << "\nEnter the element to delete: ";
  cin >> del;

  root = deleteNode(root, del);
  cout << "Inorder traversal: ";
  inorderTraversal(root);
  cout << endl;
  cout << "Preorder traversal: ";
  preorderTraversal(root);
  cout << endl;
  cout << "Postorder traversal: ";
  postorderTraversal(root);
  cout << endl
       << endl;
  return 0;
}
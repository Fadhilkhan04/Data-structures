#include <iostream>
using namespace std;

class node
{
public:
  int data;
  node *left;
  node *right;

  node(int val)
  {
    data = val;
    left = NULL;
    right = NULL;
  }
};

void insert(node *&root, int val)
{
  node *n = new node(val);
  node *current;
  node *parent;

  // if tree is empty

  if (root == NULL)
  {
    root = n;
  }
  else
  {
    current = root;
    parent = NULL;

    while (1)
    {
      parent = current;

      // go to left of tree
      if (val < parent->data)
      {
        current = current->left;
        // insert to left

        if (current == NULL)
        {
          parent->left = n;
          return;
        }
      } // go to right of tree
      else
      {
        current = current->right;
        // insert to right
        if (current == NULL)
        {
          parent->right = n;
          return;
        }
      }
    }
  }
}

void inorder(node *&root)
{
  if (root == NULL)
  {
    return;
  }
  inorder(root->left);
  cout << root->data << " ";
  inorder(root->right);
}

void preorder(node *&root)
{
  if (root == NULL)
  {
    return;
  }
  cout << root->data << " ";
  preorder(root->left);
  preorder(root->right);
}
void postorder(node *&root)
{
  if (root == NULL)
  {
    return;
  }
  postorder(root->left);
  postorder(root->right);
  cout << root->data << " ";
}

// main area

int main()
{

  int ch, val;
  node *root = NULL;
  while (true)
  {
    cout << endl;
    cout << "----------- BST Operation -----------" << endl;
    cout << "1. Insertion." << endl;
    cout << "2. Inorder traversal." << endl;
    cout << "3. Preorder traversal." << endl;
    cout << "4. postorder traversal" << endl;
    cout << "5. exit" << endl;
    cout << "Enter choice: ";
    cin >> ch;

    if (ch == 1)
    {
      cout << "enter the value:";
      cin >> val;
      insert(root, val);
      continue;
    }
    else if (ch == 2)
    {
      inorder(root);
      continue;
    }
    else if (ch == 3)
    {
      preorder(root);
      continue;
    }
    else if (ch == 4)
    {
      postorder(root);
      continue;
    }
    else if (ch == 5)
    {
      cout << "Fadhilkhan" << endl;
      cout << "RRN : 220071601060" << endl;
      cout << "B.Tech CSE - A" << endl;
      break;
    }
    else
    {
      cout << endl
           << "Invalid choice try again." << endl
           << endl;
      continue;
    }
  }
  return 0;
}
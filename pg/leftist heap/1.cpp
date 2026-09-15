#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
  int data;
  int npl;
  Node *left;
  Node *right;

  Node(int value)
  {
    data = value;
    npl = 0;
    left = nullptr;
    right = nullptr;
  }
};

class LeftistHeap
{
public:
  // Find NPL
  int getNPL(Node *node)
  {
    if (node == nullptr)
      return -1;

    return node->npl;
  }

  // Merge two Leftist Heaps
  Node *merge(Node *h1, Node *h2)
  {

    // If first heap is empty
    if (h1 == nullptr)
      return h2;

    // If second heap is empty
    if (h2 == nullptr)
      return h1;

    // Make h1 have the smaller root
    if (h1->data > h2->data)
    {
      swap(h1, h2);
    }

    // Merge h2 with right subtree of h1
    h1->right = merge(h1->right, h2);

    // Check Leftist Property
    if (getNPL(h1->left) < getNPL(h1->right))
    {
      swap(h1->left, h1->right);
    }

    // Update NPL
    h1->npl = 1 + min(getNPL(h1->left),
                      getNPL(h1->right));

    return h1;
  }

  // Insert an element
  Node *insert(Node *root, int value)
  {

    Node *newNode = new Node(value);

    // Merge existing heap with new node
    root = merge(root, newNode);

    return root;
  }

  // Find minimum element
  void findMin(Node *root)
  {

    if (root == nullptr)
    {
      cout << "Heap is empty!\n";
      return;
    }

    cout << "Minimum element = "
         << root->data << endl;
  }

  // Delete minimum element
  Node *deleteMin(Node *root)
  {

    if (root == nullptr)
    {
      cout << "Heap is empty!\n";
      return nullptr;
    }

    cout << "Deleted element = "
         << root->data << endl;

    Node *leftHeap = root->left;
    Node *rightHeap = root->right;

    delete root;

    // Merge left and right subtrees
    root = merge(leftHeap, rightHeap);

    return root;
  }

  // Display the heap
  void display(Node *root)
  {

    if (root == nullptr)
    {
      cout << "Heap is empty!\n";
      return;
    }

    cout << "\nHeap (Element, NPL):\n";
    displayTree(root, 0);

    cout << endl;
  }

  // Helper function to display tree
  void displayTree(Node *root, int space)
  {

    if (root == nullptr)
      return;

    // Display right subtree first
    displayTree(root->right, space + 5);

    // Print spaces
    for (int i = 0; i < space; i++)
      cout << " ";

    cout << root->data
         << "(" << root->npl << ")"
         << endl;

    // Display left subtree
    displayTree(root->left, space + 5);
  }
};

int main()
{

  LeftistHeap lh;

  Node *heap1 = nullptr;
  Node *heap2 = nullptr;
  Node *mergedHeap = nullptr;

  int choice;
  int value;

  do
  {

    cout << "\n========== LEFTIST HEAP ==========\n";
    cout << "1. Insert into Heap 1\n";
    cout << "2. Insert into Heap 2\n";
    cout << "3. Merge Heap 1 and Heap 2\n";
    cout << "4. Display Heap 1\n";
    cout << "5. Display Heap 2\n";
    cout << "6. Display Merged Heap\n";
    cout << "7. Find Minimum\n";
    cout << "8. Delete Minimum\n";
    cout << "9. Exit\n";

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {

    case 1:

      cout << "Enter value: ";
      cin >> value;

      heap1 = lh.insert(heap1, value);

      cout << "Inserted into Heap 1.\n";

      break;

    case 2:

      cout << "Enter value: ";
      cin >> value;

      heap2 = lh.insert(heap2, value);

      cout << "Inserted into Heap 2.\n";

      break;

    case 3:

      mergedHeap = lh.merge(heap1, heap2);

      cout << "Heap 1 and Heap 2 merged successfully.\n";

      break;

    case 4:

      cout << "\nHeap 1:\n";
      lh.display(heap1);

      break;

    case 5:

      cout << "\nHeap 2:\n";
      lh.display(heap2);

      break;

    case 6:

      cout << "\nMerged Heap:\n";
      lh.display(mergedHeap);

      break;

    case 7:

      cout << "\nMinimum element in merged heap:\n";
      lh.findMin(mergedHeap);

      break;

    case 8:

      mergedHeap = lh.deleteMin(mergedHeap);

      break;

    case 9:

      cout << "Exiting...\n";

      break;

    default:

      cout << "Invalid choice!\n";
    }

  } while (choice != 9);

  return 0;
}
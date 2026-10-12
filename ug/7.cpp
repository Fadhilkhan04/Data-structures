#include <iostream>
using namespace std;

class node
{
public:
  int data;
  node *next;

  node(int val)
  {
    data = val;
    next = NULL;
  }
};

void insertathead(node *&head, int val)
{
  node *n = new node(val);
  n->next = head;
  head = n;
}

void insertion(node *&head, int val, int pos)
{
  node *n = new node(val);
  node *temp = head;
  for (int i = 2; i < pos; i++)
  {
    if (temp->next != NULL)
    {
      temp = temp->next;
    }
  }
  n->next = temp->next;
  temp->next = n;
}

void insertatend(node *&head, int val)
{
  node *n = new node(val);

  if (head == NULL)
  {
    head = n;
    return;
  }
  node *temp = head;

  while (temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = n;
}

void display(node *head)
{
  node *temp = head;
  while (temp != NULL)
  {
    cout << temp->data << "->";
    temp = temp->next;
  }
  cout << "NULL" << endl;
}

void deleteathead(node *&head)
{
  node *todelete = head;
  head = head->next;

  delete todelete;
}

void deletion(node *&head, int pos)
{
  if (head == NULL)
  {
    return;
  }
  if (head->next == NULL)
  {
    deleteathead(head);
  }
  node *temp = head;

  for (int i = 2; i < pos; i++)
  {
    if (temp->next != NULL)
    {
      temp = temp->next;
    }
  }
  node *todelete = temp->next;
  temp->next = temp->next->next;
  delete todelete;
}

void deleteatend(node *head)
{
  node *temp = head;
  node *ptr;
  while (temp->next != NULL)
  {
    ptr = temp;
    temp = temp->next;
  }
  ptr->next = NULL;
  delete temp;
}

int main()
{
  int ch;
  int val, pos;
  node *head = NULL;
  while (true)
  {
    cout << endl;
    cout << "----------- linked list Operation -----------" << endl;
    cout << "1. Insert at the beginning." << endl;
    cout << "2. Insert at the middle." << endl;
    cout << "3. Insert at the end." << endl;
    cout << "4. Delete at the beginning" << endl;
    cout << "5. Delete at the middle." << endl;
    cout << "6. Delete at the end." << endl;
    cout << "7. Display." << endl;
    cout << "8. exit" << endl;
    cout << "Enter choice: ";
    cin >> ch;
    if (ch == 1)
    {
      cout << "Enter the value:";
      cin >> val;
      insertathead(head, val);
      continue;
    }
    else if (ch == 2)
    {
      cout << "Enter the value:";
      cin >> val;
      cout << "enter the position:";
      cin >> pos;
      insertion(head, val, pos);
      continue;
    }
    else if (ch == 3)
    {
      cout << "enter the value:";
      cin >> val;
      insertatend(head, val);
      continue;
    }
    else if (ch == 4)
    {
      deleteathead(head);
      continue;
    }
    else if (ch == 5)
    {
      cout << "enter the position:";
      cin >> pos;
      deletion(head, pos);
      continue;
    }
    else if (ch == 6)
    {
      deleteatend(head);
      continue;
    }
    else if (ch == 7)
    {
      display(head);
      continue;
    }
    else if (ch == 8)
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
#include <iostream>
#include <queue>
using namespace std;

struct Node
{
    int data;
    Node* eldestChild;
    Node* nextSibling;
    Node(int x)
    {
        data = x;
        eldestChild = NULL;
        nextSibling = NULL;
    }
};

Node* addDirectChild(Node* parent, int newData)
{
    Node* newChild = new Node(newData);
    if (!parent)return newChild;
    if (!parent->eldestChild) { parent->eldestChild = newChild; return parent; }
    Node* temp = parent->eldestChild;
    while (temp->nextSibling)temp = temp->nextSibling;
    temp->nextSibling = newChild;
    return parent;
}

Node* addDirectChild(Node* parent, Node* newChild)
{
    if (!parent)return newChild;
    if (!parent->eldestChild) { parent->eldestChild = newChild; return parent; }
    Node* temp = parent->eldestChild;
    while (temp->nextSibling)temp = temp->nextSibling;
    temp->nextSibling = newChild;
    return parent;
}

Node* addDirectSibling(Node* sibling, int newData)
{
    if (!sibling) { cout << "No brother yet!" << endl; return sibling; }
    Node* newSibling = new Node(newData);
    Node* temp = sibling;
    while (temp->nextSibling) temp = temp->nextSibling;
    temp->nextSibling = newSibling;
    return sibling;
}

Node* addDirectSibling(Node* sibling, Node* newSibling)
{
    if (!sibling) { cout << "No brother yet!" << endl; return sibling; }
    Node* temp = sibling;
    while (temp->nextSibling) temp = temp->nextSibling;
    temp->nextSibling = newSibling;
    return sibling;
}


Node* findNode(Node* root, int x)
{
    if (!root) return NULL;
    queue<Node*> q;
    while (root)
    {
        q.push(root);
        root = root->nextSibling;
    }
    while (!q.empty())
    {
        Node* temp = q.front();
        if (temp->data == x) return temp;
        q.pop();
        temp = temp->eldestChild;
        while (temp)
        {
            q.push(temp);
            temp = temp->nextSibling;
        }
    }
    return NULL;
}



Node* deleteNode(Node* root)
{
    if (root->nextSibling)
    {
        Node* temp = root; root = root->nextSibling;
        addDirectChild(root, temp->eldestChild);
        delete temp;
    }
    else if (!root->nextSibling && root->eldestChild)
    {
        Node* temp = root, *child=root->eldestChild;
        root = child;
        addDirectChild(root, child->nextSibling);
        child->nextSibling = NULL;
        delete temp;
    }
    else
    {
        delete root; return NULL;
    }
    return root;
}

Node* deleteManyNode(Node* root, int x)
{
    if (!root) return NULL;
    while (root && root->data == x)
    {
        root = deleteNode(root);
    }
    if (!root) return NULL;
    Node* prev = root, * curr = root->nextSibling;
    queue<Node*> q;
    q.push(root);
    while (curr)
    {
        if (curr->data == x)
        {
            Node* temp = curr;
            prev->nextSibling = curr->nextSibling;
            curr = curr->nextSibling;
            addDirectChild(prev, temp->eldestChild);
            delete temp;
        }
        else
        {
            q.push(curr);
            prev = prev->nextSibling;
            curr = curr->nextSibling;
        }
    }
    while (!q.empty())
    {
        Node* current = q.front();
        q.pop();
        while (current->eldestChild && current->eldestChild->data == x)
        {
            current->eldestChild = deleteNode(current->eldestChild);
        }
        if (!current || !current->eldestChild) continue;
        Node* prev = current->eldestChild, * curr = current->eldestChild->nextSibling;
        q.push(current->eldestChild);
        while (curr)
        {
            if (curr->data == x)
            {
                Node* temp = curr;
                prev->nextSibling = curr->nextSibling;
                curr = curr->nextSibling;
                addDirectChild(prev, temp->eldestChild);
                delete temp;
            }
            else
            {
                q.push(curr);
                prev = prev->nextSibling;
                curr = curr->nextSibling;
            }
        }
    }
    return root;
}

int getHeight(Node* root)
{
    if (!root) return 0;
    int height = 0;
    Node* curr = root->eldestChild;
    while (curr)
    {
        int childHeight = getHeight(curr);
        if (childHeight > height)
            height = childHeight;
        curr = curr->nextSibling;
    }
    return height + 1;
}

void printTree(Node* root)
{
    queue<Node*> q;
    Node* temp = root;
    while (temp)
    {
        q.push(temp);
        temp = temp->nextSibling;
    }
    while (!q.empty()) 
    {
        Node* curr = q.front();
        q.pop();
        cout << curr->data << " ";
        if (curr->eldestChild)
        {
            Node* temp = curr->eldestChild;
            while (temp)
            {
                q.push(temp);
                temp = temp->nextSibling;
            }
        }
    }
    cout << endl;
}

Node* generalAdd(Node* root, int key)
{
    Node* newNode = new Node(key);
    if (!root) return newNode;
    queue<Node* > q;
    q.push(root);
    while (!q.empty())
    {
        Node* curr = q.front();
        q.pop();
        if (!curr->eldestChild)
        {
            curr->eldestChild = newNode; return root;
        }
        if (!curr->nextSibling)
        {
            curr->nextSibling = newNode; return root;
        }
        q.push(curr->eldestChild);
        q.push(curr->nextSibling);
    }
    return root;
}

void levelPrint(Node* root)
{   
    if (!root) return;
    int height = getHeight(root);
    vector<int> levelLength(height,0);
    levelLength[0]=1;
    int levelFlag=0;
    int counter=0;
    cout << root->data << endl;
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        Node* curr = q.front()->eldestChild;
        q.pop();
        counter++;
        int temp = 0;
        while (curr)
        {
            q.push(curr);
            cout << curr->data << " ";
            curr=curr->nextSibling;
            temp++;
        }
        if(levelFlag+1<height) levelLength[levelFlag + 1] += temp;
        if (counter == levelLength[levelFlag])
        {
            if(levelFlag+1<height) levelFlag++;
            counter = 0;
            cout << endl;
        }
        else
        {
            cout << "/ ";
        }
    }

}

int main()
{
    // Create root node with duplicate value
    Node* root = new Node(3);

    // Add children with duplicate values
    root = addDirectChild(root, 2);
    root = addDirectChild(root, 3);
    root = addDirectChild(root, 3); // duplicate
    root = addDirectChild(root, 4);

    // Add siblings with duplicate values
    Node* child2 = root->eldestChild;
    child2 = addDirectSibling(child2, 3); // duplicate as sibling
    child2 = addDirectSibling(child2, 5);

    // Add children to node 3 (first occurrence)
    Node* child3 = child2->nextSibling;
    child3 = addDirectChild(child3, 6);
    child3 = addDirectChild(child3, 3); // duplicate as child

    // Add more duplicates deeper in the tree
    Node* child6 = child3->eldestChild;
    child6 = addDirectChild(child6, 3); // duplicate as grandchild

    // Add a duplicate as a child of the second 3
    Node* second3 = root->eldestChild->nextSibling;
    second3 = addDirectChild(second3, 3);

    // Add a duplicate as a child of the third 3
    Node* third3 = second3->nextSibling;
    third3 = addDirectChild(third3, 3);

    // Add a duplicate as a child of 4
    Node* child4 = third3->nextSibling;
    child4 = addDirectChild(child4, 3);

    // Print tree in level order before deletion
    cout << "Level order traversal before deletion:" << endl;
    levelPrint(root);

    // Delete all nodes with value 3
    root = deleteManyNode(root, 3);

    // Print tree in level order after deletion
    cout << "Level order traversal after deleting all 3s:" << endl;
    levelPrint(root);

    // Clean up memory (not exhaustive, for demo only)
    // In production, implement a proper tree destructor

    return 0;
}




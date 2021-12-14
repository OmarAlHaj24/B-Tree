#include <iostream>
#include <algorithm>
using namespace std;

class BTreeNode{
private:
    int *keys;
    BTreeNode **children;
    BTreeNode *parent;
    int currSize; //Number of keys
    int order; //Tree order
    bool leaf;
public:
    friend class BTree;
    BTreeNode(int order)
    {
        parent = NULL;
        currSize = 0;
        this->order = order;
        leaf = true;
        keys = new int [order];
        children = new BTreeNode* [order + 1];
        for(int i = 0; i < order; i++){
            keys[i] = NULL;
            children[i] = NULL;
        }
        children[order] = NULL;
    }
    ~BTreeNode()
    {
        delete [] keys;
        for(int i = 0; i < order + 1; i++){
            delete children[i];
        }
        delete [] children;
    }
    void splitNode(BTreeNode*& root);
    void traverse()
    {
        for(int i = 0; i < currSize; i++)
        {
            cout << keys[i] << " ";
        }
        cout << endl;
        if(this->leaf) return;
        for(int i = 0; i < currSize + 1; i++)
        {
            children[i]->traverse();
        }
    }
    friend bool compareNodes(const BTreeNode* a, const BTreeNode* b);
};

bool compareNodes(const BTreeNode* a, const BTreeNode* b)
{
    if(a->keys[0] < b->keys[0]) return true;
    else return false;
}

void BTreeNode::splitNode(BTreeNode *&root)
{
    if(this->currSize <= this->order - 1)
    {
        return;
    }
    int idx = this->currSize / 2;
    BTreeNode* newNode = new BTreeNode(order);
    int i = idx + 1, j = 0;
    while(i < this->currSize)
    {
        newNode->keys[j] = this->keys[i];
        newNode->currSize++;
        i++; j++;
    }
    i = idx + 1, j = 0;
    while(i < currSize + 1)
    {
        newNode->children[j] = children[i];
        if(children[i] != NULL)
        {
            newNode->children[j]->parent = newNode;
        }
        if(children[i] != NULL)
        {
            newNode->leaf = false;
        }
        i++; j++;
    }
    this->currSize = idx;
    if(this->parent == NULL)
    {
        parent = new BTreeNode(order);
        parent->children[0] = this;
        root = parent;
        root->leaf = false;
    }
    parent->children[parent->currSize + 1] = newNode;
    parent->keys[parent->currSize] = keys[idx];
    parent->currSize++;
    newNode->parent = parent;
    sort(parent->keys, parent->keys + parent->currSize);
    sort(parent->children, parent->children + parent->currSize + 1, compareNodes);
    parent->splitNode(root);
}

class BTree{
private:
    BTreeNode* root; //The root of the tree
    int order; //The degree of the tree
public:
    BTree(int order)
    {
        root = NULL;
        this->order = order;
    }
    ~BTree()
    {
        delete root;
    }
    void Insert(int key)
    {
        BTreeNode* currNode = root;
        if(root == NULL)
        {
            root = new BTreeNode(order);
            root->keys[root->currSize] = key;
            root->currSize++;
        }
        else
        {
            int nodeToTraverse = 0;
            while(!currNode->leaf)
            {
                nodeToTraverse = currNode->currSize;
                for(int i = 0; i < currNode->currSize; i++)
                {
                    if(currNode->keys[i] > key)
                    {
                        nodeToTraverse = i;
                        break;
                    }
                }
                currNode = currNode->children[nodeToTraverse];
            }
            currNode->keys[currNode->currSize] = key;
            currNode->currSize++;
            sort(currNode->keys, currNode->keys + currNode->currSize);
            currNode->splitNode(root);
        }
    }
    void Print()
    {
        if(root == NULL) return;
        root->traverse();
    }
};

int main() {
    BTree t1(3);
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print();
}
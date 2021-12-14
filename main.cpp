#include <iostream>
#include <algorithm>
using namespace std;

class BTreeNode{
private:
    char *keys;
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
        keys = new char [order];
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

bool compareNodes(const BTreeNode* a, const BTreeNode* b){
    if(a->keys[0] < b->keys[0]) return true;
    else return false;
}

void BTreeNode::splitNode(BTreeNode *&root) {
    if(this->currSize <= this->order - 1){
        return;
    }
    int idx = this->currSize / 2;
    BTreeNode* newNode = new BTreeNode(order);
    for(int i = idx + 1, j = 0; i < this->currSize; i++, j++){
        newNode->keys[j] = this->keys[i];
        newNode->currSize++;
    }
    this->currSize = idx;
    if(this->parent == NULL){
        parent = new BTreeNode(order);
        parent->children[0] = this;
        root = parent;
        root->leaf = false;
    }
    for(int i = 0; i < order + 1; i++){
        if(parent->children[i] == NULL){
            parent->children[i] = newNode;
            break;
        }
    }
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
            while(!currNode->leaf){
                nodeToTraverse = currNode->currSize;
                for(int i = 0; i < currNode->currSize; i++){
                    if(currNode->keys[i] > key){
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

int main()
{
    BTree t(5);
    // Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');//
    t.Insert('T');//
    t.Insert('R');
    t.Insert('L');//
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');//
    t.Insert('N');
    t.Insert('P');//
    t.Insert('Q');//
    t.Print(); // Should output the following on the screen:
    /*
    K
      C,G
        A,B
        D,E,F
        H,I,J
      N,R
        L,M
        P,Q
        S,T
    */
    return 0;
}

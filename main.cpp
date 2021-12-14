#include <iostream>
#include <algorithm>
using namespace std;

class BTreeNode{
private:
    int *keys;
    BTreeNode **children;
    int currSize; //Number of keys
    int order; //Tree order
    bool leaf;
public:
    friend class BTree;
    BTreeNode(int order)
    {
        currSize = 0;
        this->order = order;
        leaf = true;
        keys = new int [order - 1];
        children = new BTreeNode* [order];
    }
    ~BTreeNode()
    {

    }
    void splitNode()
    {

    }
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
};

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
                for(int i = 0; i < currNode->currSize; i++){
                    nodeToTraverse = i;
                    if(currNode->keys[i] > key){
                        break;
                    }
                }
                currNode = currNode->children[nodeToTraverse];
            }
            if(currNode->currSize < order - 1){
                currNode->keys[currNode->currSize] = key;
                currNode->currSize++;
                sort(currNode->keys, currNode->keys + currNode->currSize);
            }else{

            }
        }
    }
    void Print()
    {
        root->traverse();
    }
};

int main()
{
    // Construct a BTree of order 3, which stores int data
    BTree t1(3);
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print(); // Should output the following on the screen:
    /*
    1,4
      0
      2,3
      5
    */
    return 0;
}

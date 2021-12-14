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
        keys = new int [order];
        children = new BTreeNode* [order];
    }
    ~BTreeNode()
    {
        delete [] keys;
        delete [] children;
    }
    void splitNode(BTreeNode* root, BTreeNode* node)
    {
//        while(!currNode->leaf){
//            nodeToTraverse = currNode->currSize;
//            for(int i = 0; i < currNode->currSize; i++){
//                if(currNode->keys[i] > key){
//                    nodeToTraverse = i;
//                    break;
//                }
//            }
//            currNode = currNode->children[nodeToTraverse];
//        }
        
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
            currNode->splitNode(root, currNode);
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

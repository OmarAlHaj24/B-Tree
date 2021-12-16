#include <iostream>

using namespace std;
/**
 * Omar Khaled Al Haj 20190351
 * Rana Ihab Ahmed 20190207
 * Alaa Mahmoud Ebrahim 20190105
 * */
template<class T,int order>
class BTree;

template<class T,int order>
class BTreeNode{
private:
    T *keys;
    BTreeNode **children;
    BTreeNode *parent;
    int currSize; //Number of keys
    bool leaf;
public:
    friend class BTree<T, order>;
    BTreeNode()
    {
        parent = NULL;
        currSize = 0;
        leaf = true;
        keys = new T [order];
        children = new BTreeNode* [order + 1];
        for(int i = 0; i < order; i++)
        {
            children[i] = NULL;
        }
        children[order] = NULL;
    }
    ~BTreeNode()
    {
        delete [] keys;
        for(int i = 0; i < order + 1; i++)
        {
            delete children[i];
        }
        delete [] children;
    }
    void splitNode(BTreeNode*& root);
    void traverse(int level)
    {
        for(int i = 0; i < level; i++)
        {
            cout<<" ";
        }
        for(int i = 0; i < currSize; i++)
        {
            if(i != 0)
            {
                cout << ",";
            }
            cout << keys[i];
        }
        cout << endl;
        if(this->leaf) return;
        for(int i = 0; i < currSize + 1; i++)
        {
            children[i]->traverse(level+2);
        }
    }

};

template<class T,int order>
void BTreeNode<T, order>::splitNode(BTreeNode<T, order> *&root)
{
    if(this->currSize <= order - 1)
    {
        return;
    }
    int idx = this->currSize / 2;
    BTreeNode* newNode = new BTreeNode();
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
        parent = new BTreeNode();
        parent->children[0] = this;
        root = parent;
        root->leaf = false;
    }
    for(int i = parent->currSize; i>=0; i--)
    {
        if(i == 0 || parent->keys[i-1]<=keys[idx])
        {
            parent->keys[i] = keys[idx];
            parent->children[i+1] = newNode;
            break;
        }
        else if(parent->keys[i-1]>keys[idx])
        {
            parent->keys[i] = parent->keys[i -1];
            parent->children[i+1] = parent->children[i];
        }
    }
    parent->currSize++;
    newNode->parent = parent;
    parent->splitNode(root);
}

template<class T,int order>
class BTree{
private:
    BTreeNode<T, order>* root; //The root of the tree
    //int order; //The degree of the tree
public:
    BTree()
    {
        root = NULL;
        //this->order = order;
    }
    ~BTree()
    {
        delete root;
    }
    void Insert(int key)
    {
        BTreeNode<T, order>* currNode = root;
        if(root == NULL)
        {
            root = new BTreeNode<T, order>();
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
            for(int i = currNode->currSize; i>=1; i--)
            {
                if(currNode->keys[i-1]>key)
                {
                    currNode->keys[i] = currNode->keys[i -1];
                    currNode->keys[i-1] = key;
                }
                else
                {
                    currNode->keys[i] = key;
                    break;
                }
            }
            currNode->currSize++;
            currNode->splitNode(root);
        }
    }
    void Print()
    {
        if(root == NULL) return;
        root->traverse(0);
    }
};


int main() {
    // Construct a BTree of order 3, which stores int data
    BTree<int, 3> t1;

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

    // Construct a BTree of order 5, which stores char data
    BTree<char, 5> t;

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
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');

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
#ifndef __MYBST_H__
#define __MYBST_H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

enum TreeTravOrderType
{
    PreOrder,
    InOrder,
    PostOrder
};

enum NodePosType
{
    Left,
    Right,
    Root
};

template <typename ComparableType>
class MyBST
{
  private:
    struct BinaryNode
    {
        ComparableType element;
        size_t height;
        BinaryNode *left;
        BinaryNode *right;
        
        BinaryNode(const ComparableType & x, const size_t h, BinaryNode *l, BinaryNode *r) : 
            element{x}, 
            height{h},
            left{l}, 
            right{r} 
        { 
            ;
        }

        BinaryNode(ComparableType && x, const size_t h, BinaryNode *l, BinaryNode *r) : 
            element{move(x)}, 
            height{h},
            left{l},
            right{r}
        {
            ;
        }
    };

    BinaryNode *root;       // the root node
    size_t theSize = 0;         // the number of data elements in the tree

    // finds the minimum data element from the tree rooted at t
    BinaryNode* findMin(BinaryNode *t) const
    {
        // code begins
        if (t == nullptr) {
            return nullptr; 
            }
        if(t->left == nullptr){
            return t;
        }
        return findMin(t->left);
        // code ends
    }

    // finds the maximum data element from the tree rooted at t
    BinaryNode* findMax(BinaryNode *t) const
    {
        // code begins
        if (t == nullptr) {
            return nullptr; 
            }
    
        while (t->right != nullptr) {
            t = t->right; 
            }
    
        return t;
        // code ends
    }

    // checks if x is contained in the tree rooted at t
    bool contains(const ComparableType& x, BinaryNode *t) const
    {
        // code begins
         if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left); 
            } 
        else if (t->element < x) {
            return contains(x, t->right); 
        } else {
            return true; 
            }
         // code ends
    }

    // deletes the tree rooted at t
    void clear(BinaryNode*& t)
    {
        // code begins
        if (t != nullptr) {
            clear(t->left); 
            clear(t->right); 
            delete t; 
            t = nullptr;
        }
        // code ends
    }

    // returns the height of the node
    // leave nodes have a height of 1
    size_t height(BinaryNode* t) const
    {
        return (t == nullptr ? 0 : t->height);
    }

    // balances tree node t
    void balance(BinaryNode*& t)
    {
        // code begins
        if(t == nullptr){
            return;
        }
        else if(int( height(t->left) - height(t->right)_ > 1){
            if(height(t->left->left) >= height( t->left->right)){
                rotateLeft(t);
            }
            else{
                doubleRotateLeft(t);
            }
        }else{
            if( height(t->right) - height(t->left) > 1){
                if( height(t->right->right) >= height(t->right->left)){
                    rotateRight(t);
                }
                else{
                    doubleRotateRight(t);
                }
            }
        }
        t->height = max(height(t->left), height(t->right))+1;
        // code ends
    }
    
    // single rotation that reduces left branch depth
    void rotateLeft(BinaryNode*& t)
    {
        // code begins
        BinaryNode *t1 = t->left;
        t->left = t1->right;
        t1->right = t;
        t->height = max(height(t->left), height(t->right))+1;
        t1->height = max(height(t1->left), height(t))+1;
        t = t1;
        
        // code ends
    }

    // single rotation that reduces right branch depth
    void rotateRight(BinaryNode*& t)
    {
        // code begins
        BinaryNode *t1 = t->right;
        t->right = t1->left;
        t1->left = t;
        t->height = max(height(t->right), height(t->left))+1;
        t1->height = max(height(t1->right), height(t))+1;
        t = t1;
        // code ends
    }

    // double rotation that reduces left branch depth
    void doubleRotateLeft(BinaryNode*& t)
    {
        // code begins
        rotateRight(t->left);
        rotateLeft(t);
        // code ends
    }

    // double rotation that reduces right branch depth
    void doubleRotateRight(BinaryNode*& t)
    {
        // code begins
        rotateLeft(t->right);
        rotateRight(t);
        // code ends
    }

    // inserts x to the tree rooted at t (copy)
    // if x exists, the do nothing
    void insert(const ComparableType& x, BinaryNode*& t)
    {
        // code begins
        if(empty() == true){
            root = new BinaryNode(x, 1, nullptr, nullptr);
            ++theSize;
        }
        else{
        if(t == nullptr){
            t = new BinaryNode(x, 1, nullptr, nullptr);
            ++theSize;
        }
        else if(t->element == x){
            return;
        }
        else if(x< t->element){
            insert(x,t->left);
        }
        else if(t->element < x){
            insert(x,t->right);
        }
        balance(t);
        }
        // code ends
    }

    // inserts x to the tree rooted at t (move)
    void insert(ComparableType && x, BinaryNode*& t)
    {
        // code begins
        if(empty() == true){
            root = new BinaryNode(move(x), 1, nullptr, nullptr);
            ++theSize;
        }
        else{
        if(t == nullptr){
            t = new BinaryNode(move(x), 1, nullptr, nullptr);
            ++theSize;
        }
        else if(t->element == x){
            return;
        }
        else if(x< t->element){
            insert(x,t->left);
        }
        else if(t->element < x){
            insert(x,t->right);
        }
        balance(t);
        }
    }

    // removes x from the tree rooted at t
    // when deleting a node with two children, replace it with the smallest child of the right subtree
    void remove(const ComparableType& x, BinaryNode*& t)
    {
        // code begins
        if ( t == nullptr ){
            return;
        }
        if( x < t->element){
            remove(x, t->left);
        }
        else if(t->element < x){
            remove(x, t->right);
        }
        else if( t->left != nullptr && t->right != nullptr){
            t->element = (findMin(t->right))->element;
            remove(t->element, t->right);
        }
        else{
            BinaryNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
        // code ends
    }

    // clones the node t and returns the clone
    BinaryNode* clone(BinaryNode* t) const
    {
        if( t == nullptr ) return nullptr;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

    // prints all data elements rooted at t pre-order
    void printPreOrder(BinaryNode* t, ostream& out) const
    {
        const char delim = ' ';
        if(t != nullptr)
        {
            out << t->element<< delim;
            printPreOrder(t->left, out);
            printPreOrder(t->right, out);
        }
        return;
    }

    // prints all data elements rooted at t in-order
    void printInOrder(BinaryNode* t, ostream& out) const    
    {
        const char delim = ' ';
        if(t != nullptr)
        {
            printInOrder(t->left, out);
            out << t->element<< delim;
            printInOrder(t->right, out);
        }
        return;
    }

    // prints all data elements rooted at t post-order
    void printPostOrder(BinaryNode* t, ostream& out) const
    {
        const char delim = ' ';
        if(t != nullptr)
        {
            printPostOrder(t->left, out);
            printPostOrder(t->right, out);
            out << t->element << delim;
        }
        return;
    }

    // prints the subtree rooted at t
    // lv is the level of t (the root corresponds to level 0)
    // p is the relative topological position of t (left/right/root) 
    void printTree(BinaryNode* t, const int lv, const NodePosType p)
    {
        if(t == nullptr)
            return;

        char pos;
        switch(p)
        {
            case Left:
                pos = 'L';
                break;
            case Right:
                pos = 'R';
                break;
            case Root:
                pos = 'T';
                break;
            default:
                cout << "Error: MyBST::printTree: unrecognized position type." << endl;
        }        
        cout << t->element << "|" << lv << "|" << pos <<endl;
        printTree(t->left, lv + 1, Left);
        printTree(t->right, lv + 1, Right);
    }

  public:

    // default constructor
    MyBST() : 
        root{nullptr},
        theSize{0}
    {
        ;
    }

    // copy constructor
    MyBST(const MyBST& rhs) : 
        root{nullptr},
        theSize{rhs.theSize}
    {
        root = clone(rhs.root);
    }

    // move constructor
    MyBST(MyBST && rhs) : 
        root{rhs.root},
        theSize{rhs.theSize}
    {
        rhs.root = nullptr;
    }
      
    // destructor
    ~MyBST()
    {
        clear();
    }

    // finds the minimum data element in the tree
    const ComparableType& findMin() const
    {
        // code begins
       return findMin(root)->element;

        // code ends
    }

    // finds the maximum data element in the tree
    const ComparableType& findMax( ) const
    {
        // code begins
        return findMax(root)->element;
        // code ends
    }

    // checks whether x is contained in the tree
    bool contains(const ComparableType& x) const
    {
        // code begins
        return contains(x,root);
        // code ends
    }
    
    // returns the number of data elements in the tree
    size_t size(void) const
    {
        // code begins
        return theSize;
        // code ends
    }

    // returns the depth of the tree
    // depth defined as the longest path length from the root to any leaf
    // e.g. an empty tree has a depth of 0, a tree with a single node has a depth of 1
    size_t depth(void) const
        {
        return height(root);
        }

    /*size_t depth(BinaryNode* node) const
    {
        if (node == nullptr) {
            return 0;
        }
        size_t left_depth = depth(node->left);
        size_t right_depth = depth(node->right);
        return std::max(left_depth, right_depth) + 1;
    }*/

    // checks whether the tree is empty
    bool empty() const
    {
        // code begins
        return root == nullptr;
        // code ends
    }

    // delete all data elements in the tree
    void clear()
    {
        // code begins
        clear(root);
        // code ends
    }

    // insert x into the tree (copy)
    void insert(const ComparableType& x)
    {
        // code begins
        insert(x, root);
        // code ends
    }

    // insert x into the tree (move)
    void insert(ComparableType && x)
    {
        // code begins
        insert(x, root);
        // code ends
    }

    // removes x from the tree
    void remove(const ComparableType& x)
    {
        // code begins
        --theSize;
        remove(x, root);
        // code ends
    }

    // copy assignment
    MyBST& operator=(const MyBST& rhs)
    {
        // code begins
        MyBST copy= rhs; 
        swap(*this, copy);
        return *this;
        // code ends
    }

    // move assignment
    MyBST& operator=(MyBST && rhs)
    {
        // code begins
        
        swap(theSize, rhs.theSize);
        swap(root, rhs.root);
        return *this;
        // code ends
    }

    // finds the lowest common ancestor (LCA) of x and y
    // if x and y are both in the tree, return true and store their LCA in lca
    // otherwise, return false
    bool lowestCommonAncestor(const ComparableType& x, const ComparableType& y, ComparableType& lca)
    {
        // code begins
        bool containx = contains(x);
        bool containy = contains(y);
        if (containx == false || containy == false) {
            return false;
        }
        
        lca = root->element;
        BinaryNode* cur_node = root;
        while (true) {
            if (x < lca && y < lca) {
                cur_node = cur_node->left;
                lca = cur_node->element;
            } else if (x > lca && y > lca) {
                cur_node = cur_node->right;
                lca = cur_node->element;
            } else {
                break;
            }
        }
        return true;
        // code ends
    }

    // print all data elements in the tree
    void print(TreeTravOrderType order,ostream& out = cout) const
    {
        switch (order)
        {
            case PreOrder:
                printPreOrder(root, out);
                out << endl;
                break;
            case InOrder:
                printInOrder(root, out);
                out << endl;
                break;
            case PostOrder:
                printPostOrder(root, out);
                out << endl;
                break;
            default:
                out << "Error: MyBST::print: Unsupported print order." << endl;
                break;
        }
        return;
    }

    // print all data elements in the tree
    // including partial topological information (layer and relative position among siblings)
    void printTree(void)
    {
        printTree(root, 0, Root);
        return;
    }
      
};

#endif // __MYBST_H__
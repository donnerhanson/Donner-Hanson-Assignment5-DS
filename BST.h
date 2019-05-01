//
//  CustTree.h
//  DS_Trees
//
//  Created by Donner Hanson on 4/2/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#ifndef BST_h
#define BST_h
#include <iostream>
#include <string>
#include <sstream>
#include <type_traits>

#include "DoublyLinkedList.h"
#include "Error.h"
#include "Faculty.hpp"
#include "Student.hpp"


using std::cout;
template<typename U>
class TreeNode{
public:
    TreeNode() : key(NULL), left(nullptr), right(nullptr){};
    TreeNode(U key) : key(key), left(nullptr), right(nullptr){};
    TreeNode(const TreeNode<U> &source) : key(source.key)
    {
        ;
    }
    void operator = (TreeNode &source )
    {
        if(source == NULL)
            this->key = source->key;
    }
    virtual ~TreeNode()
    {
        left = nullptr;
        right = nullptr;
    }
    
    U key;
    TreeNode *left;
    TreeNode *right;
private:
};



template<typename U>
class BST{
public:
    BST() : root(nullptr){};
    ~BST()
    {
        // iterate and delete
          deleteTree(&root);
    }
    // https://stackoverflow.com/questions/10412385/binary-tree-copy-constructor
    // deep copy
    BST(BST<U> const &source)
    {
        if(source.root == NULL)
            root = NULL;
        else
        {
            TreeNode<U> * copy = source.root;
            root = copyTree(root, copy);
        }
        
    }
    // deep copy assignment operator
    BST &operator = (const BST<U> &source )
    {
        if(source.root == NULL)
            root = NULL;
        else
        {
                TreeNode<U> * copy = source.root;
                root = copyTree(root, copy);
        }
        return *this;
    }
    void operator = ( BST<U> *source )
    {
        if(source->root == NULL)
            root = NULL;
        else
            root = copyTree(this->root, source->root);
    }
    TreeNode<U>* copyTree(TreeNode<U> * thisNode, TreeNode<U>*& sourceNode)
    {
        
        if(sourceNode == nullptr)
        {
            thisNode = nullptr;
        }
        else
        {
            thisNode = new TreeNode<U>(*sourceNode);
            
            thisNode->left = copyTree(thisNode->left, sourceNode->left);
            thisNode->right = copyTree(thisNode->right, sourceNode->right);
        }
        return thisNode;
    }
//    void copyTreePtr(TreeNode<U> *& thisRoot, TreeNode<U>*& sourceRoot)
//    {
//
//        if(sourceRoot == nullptr)
//        {
//            thisRoot = nullptr;
//        }
//        else
//        {
//            thisRoot = new TreeNode<U>(*sourceRoot);
//
//            copyTreePtr(thisRoot->left, sourceRoot->left);
//            copyTreePtr(thisRoot->right, sourceRoot->right);
//        }
//    }
    void insert(U value)
    {
        // check if the value exists, if not continue
        TreeNode<U> *node = new TreeNode<U>(value);
        if (isEmpty())
        {
            root = node;
        }
        else
        {
            // not empty tree, add/insert elsewhere
            // keep track of current and parent
            TreeNode<U>* current = root;
            TreeNode<U>* parent = nullptr; // empty node ptr
            
            while(true)// lets look for insertion point
            {
                if(value < current->key) // go left
                {
                    parent = current;
                    current = current->left;
                    
                    if (current == nullptr) // found add point
                    {
                        parent->left = node;
                        break;
                    }
                }
                else if (value > current->key) // go right
                {
                    parent = current;

                    current = current->right;
                    if (current == nullptr) // found add point
                    {
                        parent->right = node;
                        break;
                    }
                }
                // create a case to throw error if the key is duplicate
                else if ( value == current->key)
                {
                    cout << "Duplicate Key...\n----------\n" << value << "\nReassign Key...\n----------\n";
                    break;
                }
                
            }
        }
    }
    bool contains(U value) const
    {
        if (isEmpty())
            return false;
        
        TreeNode<U>* current = root;
        while(current->key != value)
        {
            if(value < current->key)
                current = current->left;
            else
                current = current->right;
            
            if (current == nullptr) // value not in tree
                return false;
        }
        return true;
    }
    bool contains(int value) const
    {
        if (isEmpty())
            return false;
        
        TreeNode<U>* current = root;
        while(current->key != value)
        {
            if(value < current->key)
                current = current->left;
            else
                current = current->right;
            
            if (current == nullptr) // value not in tree
                return false;
        }
        return true;
    }
    // Return a readOnly version of the key in the tree
    U get(int value) const
    {
        if (isEmpty())
            return root->key;
        
        TreeNode<U>* current = root;
        while(current->key != value)
        {
            if(value < current->key)
                current = current->left;
            else
                current = current->right;
            
            if (current == nullptr) // value not in tree
                return root->key;
        }
        return current->key;
    }
    U deleter(U k)
    {
        // have to find the correct value to replace the deleted node to maintain the integrity of the tree
        if (!contains(k))
        {
            throw Error("not found\n");
        }
       if (isEmpty())
           throw Error("No Values");
        // check if key/value exists
        TreeNode<U>* current = root;
        TreeNode<U>* parent = root;
        bool isLeft = true;
        
        // now lets iterate and update our pointers
        while (current->key != k)
        {
            parent = current;
            if (k < current->key)
            {
                isLeft = true;
                current = current->left;
            }
            else
            {
                isLeft = false;
                current = current->right;
            }
            if (current == nullptr)
                return root->key;
        }
        
        // at this point we've found our node to be deleteNode
        // if leaf node
        if (current->left == nullptr &&
            current->right == nullptr)
        {
           if (current == root)
           {
               root = nullptr;
           }
            else if(isLeft)
            {
                parent->left = nullptr;
            }
            else
                parent->right = nullptr;
        }
        // we need to check if node to be deleted has one child
        else if (current->right == nullptr) // no right child
        {
            if (current == root)
            {
                root = current->left;
            }
            else if (isLeft)
            {
                // is a left child - parent to child points to this current's left
                parent->left = current->left;
            }
            else
            {
                parent->right = current->left;
            }
        }
        else if (current->left == nullptr) // no left child
        {
            if (current == root)
            {
                root = current->right;
            }
            else if (isLeft)
            {
                // is a left child - parent to child points to this current's right
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }
        }
        else
        {
            // THE NODE WE NEED HAS 2 CHILDREN
            TreeNode<U> *successor = getSuccessor(current);
            if (current == root)
                root = successor;
            else if (isLeft)
                parent->left = successor;
            else
                parent->right = successor;
            
            successor->left = current->left;
            
        }
        
        
        
        //remove the node
        U *temp = current->key;
        // DELETE THE NODE
        delete current;
        return temp;
    }
    
    // DELETE BASED ON INT COMPARISON
    U deleter(int k)
    {
        // have to find the correct value to replace the deleted node to maintain the integrity of the tree
        if (isEmpty())
            throw (Error ("No Values"));
        // check if key/value exists
        TreeNode<U>* current = root;
        TreeNode<U>* parent = root;
        bool isLeft = true;
        
        // now lets iterate and update our pointers
        while (k != current->key)
        {
            parent = current;
            if (k < current->key)
            {
                isLeft = true;
                current = current->left;
            }
            else
            {
                isLeft = false;
                current = current->right;
            }
            if (current == nullptr)
                throw (Error ("Value Does Not Exist\n"));
        }
        
        // at this point we've found our node to be deleteNode
        // if leaf node
        if (current->left == nullptr &&
            current->right == nullptr)
        {
            if (current == root)
            {
                root = nullptr;
            }
            else if(isLeft)
            {
                parent->left = nullptr;
            }
            else
                parent->right = nullptr;
        }
        // we need to check if node to be deleted has one child
        else if (current->right == nullptr) // no right child
        {
            if (current == root)
            {
                root = current->left;
            }
            else if (isLeft)
            {
                // is a left child - parent to child points to this current's left
                parent->left = current->left;
            }
            else
            {
                parent->right = current->left;
            }
        }
        else if (current->left == nullptr) // no left child
        {
            if (current == root)
            {
                root = current->right;
            }
            else if (isLeft)
            {
                // is a left child - parent to child points to this current's right
                parent->left = current->right;
            }
            else
            {
                parent->right = current->right;
            }
        }
        else
        {
            // THE NODE WE NEED HAS 2 CHILDREN
            TreeNode<U> *successor = getSuccessor(current);
            if (current == root)
                root = successor;
            else if (isLeft)
                parent->left = successor;
            else
                parent->right = successor;
            
            successor->left = current->left;
            
        }
        
        // DELETE THE NODE
        
        U Temp = current->key;
        delete current;
        
        return Temp;
    }
    
    
    
    
    
    
    // d is the node to be deleted
    // One right and all the way left - gets the most close in value to the node to be deleted
    TreeNode<U>* getSuccessor(TreeNode<U>* d)
    {
        // d is the current in deleter
        TreeNode<U>* sp = d; // successors Parent
        TreeNode<U>* successor = d;
        TreeNode<U>* current = d->right;
        
        while (current != nullptr)
        {
            sp = successor;
            successor = current;
            current = current->left;
        }
        
        // we need to check if successor is a descendant of right child
        if (successor != d->right)
        {
            sp->left = successor->right;
            successor->right = d->right;
        }
        return successor;
    }
    
    
    TreeNode<U>* getMin()
    {
        TreeNode<U>* curr = root;
        while(curr->left != nullptr)
        {
            curr = curr->left;
        }
        return curr;
    }
    TreeNode<U>* getMax()
    {
        TreeNode<U>* curr = root;
        while(curr->right != nullptr)
        {
            curr = curr->right;
        }
        return curr;
    }
    
    
    bool isEmpty() const
    {
        return root == nullptr;
    }
    void printTree() const // print entire tree
    {
        recPrint(root);
    }
    void recPrint(TreeNode<U>* node) const
    {
        if (node == nullptr)
            return;
        
        recPrint(node->left);
        std::cout << node->key << "\n";
        recPrint(node->right);
    }
    
    string TreeToString()
    {
        string s;
        s = recToString(root);
        return s;
    }
    string recToString(TreeNode<U>* node) const
    {
        string result = "";
        string temp = "";
        if (node == nullptr)
            return result;
        stringstream ss;
        temp = recToString(node->left);
        ss << node;
        temp = recToString(node->right);
        
        result += ss.str();
        return result;
    }
    
    
    
    
    void RemoveStudentFromTree(int studID)
    {
        // https://en.cppreference.com/w/cpp/types/is_same
        if (std::is_same<Faculty,U>::value)
            _RemoveStudentFromTree(root, studID);
    }
    void _RemoveStudentFromTree(TreeNode<U>*, int);
    
    
    bool isOnlyOneObject() const
    {
        return root->right==nullptr && root->left==nullptr;
    }
    
    void EraseTree()
    {
        deleteTree(&root);
    }
private:
    TreeNode<U>*root;
    
    
    // https://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/
    void _deleteTree(TreeNode<U>* node)
    {
        if (node == nullptr)
            return;
        
        // first delete both subtrees
        _deleteTree(node->left);
        _deleteTree(node->right);
        
        // then delete the node
        delete(node);
    }
    
    // Deletes a tree and sets the root as NULL
    void deleteTree(TreeNode<U>** inRoot)
    {
        _deleteTree(*inRoot);
        *inRoot = nullptr;
    }
    
};


//================================================//
//                 PRINT TO COUT
//================================================//
template<>
inline void BST<Student>::printTree() const
{
    cout << "All Students and Student info\n----------\n";
    recPrint(root);
}


template<>
inline void BST<Faculty>::printTree() const
{
    cout << "All Faculty information\n----------\n";
    recPrint(root);
    cout << "\n";
}
//================================================//
//            PRINT TO STRING - FOR SAVING        //
//================================================//

template<>
inline string BST<Faculty>::recToString(TreeNode<Faculty>* node) const
{
    string result = "";
    string temp = "";
    if (node == nullptr)
        return result;
    stringstream ss;
    result += recToString(node->left);
    ss << node->key;
    result += recToString(node->right);
    
    result.append(ss.str());
    return result;
}
template <>
inline string BST<Student>::recToString(TreeNode<Student>* node) const
{
    string result = "";
    string temp = "";
    if (node == nullptr)
        return result;
    stringstream ss;
    result += recToString(node->left);
    ss << node->key;
    result += recToString(node->right);
    
    result.append(ss.str());
    return result;
}

//================================================//
//                  STUDENT CONTAINS
//================================================//
template<>
inline bool BST<Student>::contains(int value) const
{
    if (isEmpty())
        return false;
    
    TreeNode<Student>* current = root;
    while(current->key != value)
    {
        if(value < current->key)
            current = current->left;
        else
            current = current->right;
        
        if (current == nullptr) // value not in tree
            return false;
    }
    return true;
}
//==================================
// UPDATE FACULTY STUDENT LIST
//==================================
template<>
inline void BST<Faculty>::_RemoveStudentFromTree(TreeNode<Faculty>* node, int studID)
{
    if (node == nullptr)
        return;
    _RemoveStudentFromTree(node->left, studID);
    if (node->key.getStudentIDList().findData(studID) && node != nullptr
        && !node->key.getStudentIDList().isEmpty())
    {
        node->key.RemoveStudent(studID);
    }
    _RemoveStudentFromTree(node->right, studID);
}
#endif /* CustTree_h */

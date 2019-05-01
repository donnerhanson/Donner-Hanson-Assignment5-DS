//
//  DoublyLinkedList_Custom.h
//  DoublyLinkedListDS
//
//  Created by Donner Hanson on 3/7/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>

#include <string>
#include <sstream>

using std::cout;
using std::string;
using std::stringstream;

template <typename U>
class Node{
public:
    // default constructor
    // set ptr to NULL/nullptr/0
    Node(): data(0), next(NULL), prev (NULL){};
    Node(U data): data(data), next(0), prev(0){}; // overloaded
    Node(Node<U> *data, Node<U> *n, Node<U>*p): data(data->getData()), next(n), prev(p){};
    // https://stackoverflow.com/questions/13668252/how-do-you-perform-a-deep-copy-on-a-doubly-linked-list
    Node(const Node<U> &other)
    {
        // set the nodes data
        this->data = other.data;
        if(other.next)
        {
            // recursively create new nodes
            Node<U> *p = new Node<U>(*other.next);
            append(*p);
        }
        
    }
    
    void append(Node &n) {
        // set the new nodes pointers
        next = &n; n.prev = this;
    }

    ~Node(){
       
    };
    Node<U> *next, *prev;
    U getData()
    {
            return data;
    }
    U* getDataptr()
    {
        return *data;
    }
private:
    U data;
};
template <typename U>
class DoublyLinkedList{
public:
    DoublyLinkedList() : size(0), front(nullptr), back(nullptr){};
    ~DoublyLinkedList()
    {
        Node<U>* current = front;
        
        while(current)
        {
            current->prev = nullptr;
            Node<U>* next = current->next;
            delete current;
            current = next;
        }
        front = back = nullptr;
    }
    
    
    // copy constructor
    //https://stackoverflow.com/questions/13668252/how-do-you-perform-a-deep-copy-on-a-doubly-linked-list
    DoublyLinkedList(const DoublyLinkedList<U> &source):
    front(0), back(0), size(source.size)
    {
        if(source.front) {
            this->front = new Node<U>(*source.front);
            // find last item
            back = front;
            while(back->next)
                back = back->next;
        }
        
    }

    
    void insertFront(U data)
    {
        Node<U>* node = new Node<U>(data);
        
        if(isEmpty())
        {
            back = node;
        }
        else
        {
            node->next = front;
            front->prev = node;
            
        }
        front = node;
        size++;
    }
    U removeFront()
    {
        U temp = front->getData();
        Node<U>* node = front;
        if (isEmpty())
        {
            back = nullptr;
            // throw exception
        }
        else if (front->next == nullptr)
        {
            front = nullptr;
        }
        else
        {
            
            front->next->previous == nullptr;
            
        }
        front = front->next;
        node->next = nullptr;
        delete node;
        size--;
        return temp;
    }
    
    void insertBack(U data)
    {
        Node<U>* node = new Node<U>(data);
        
        if(isEmpty())
        {
            front = node;
        }
        else
        {
            back->next = node;
            node->prev = back;
            
        }
        back = node;
        size++;
    }
    
    /* REMOVE BACK HERE */
    
    U removeKey(U key)
    {
        // could use find() here
        
        Node<U>* curr = front;
        
        // look for val
        while (curr->getData()!=key)
        {
            curr = curr->next;
            if (curr == nullptr)
                return NULL;
        }
        if (curr == front) // front Node
        {
            front = curr->next;
            
        }
        else
        {
            // is in middle or back
            curr->prev->next = curr->next;
        }
        if (curr == back)
        {
            back = curr->prev;
        }
        else
        {
            curr->next->prev = curr -> prev;
        }
        curr->next = nullptr;
        curr->prev = nullptr;
        U temp = curr->getData();
        delete curr;
        size--;
        return temp;
    }
    
    // USE FOR INTS ONLY
    int removeIntKey(int key)
    {
        // could use find() here
        
        Node<U>* curr = front;
        
        // look for val
        while (curr->getData()!=key)
        {
            curr = curr->next;
            if (curr == nullptr)
                return -1;
        }
        if (curr == front) // front Node
        {
            front = curr->next;
            
        }
        else
        {
            // is in middle or back
            curr->prev->next = curr->next;
        }
        if (curr == back)
        {
            back = curr->prev;
        }
        else
        {
            curr->next->prev = curr -> prev;
        }
        curr->next = nullptr;
        curr->prev = nullptr;
        U temp = curr->getData();
        delete curr;
        size--;
        return temp;
    }

    
    
    
    U deletePos(int pos)
    {
        // assumes the value is known
        if (pos > 0)
        {
            int idx = 0;
            Node<U>* curr = front;
            Node<U>* prev = front;
            while (idx != pos)
            {
                prev = curr; // hangs back
                curr = curr->next;
                ++idx;
            }
            if(idx == pos)
            {
                prev->next = curr->next;
                curr->next = nullptr;
            }
            U temp = curr->getData();
            if(idx == pos)
            {
                delete curr;
                size--;
            }
            return temp;
        }
        else
        {
            if (front == nullptr || front->next == nullptr)
                return NULL;
            else
            {
                // Move the head pointer to the next node
                Node<U> *temp = front;
                front = front->next;
                delete temp;
                size--;
                return front->getData();
            }
        }
    }
    void printList()
    {
        Node<U>* curr = front;
        while (curr)
        {
            std::cout << curr->getData() << "\n";
            curr = curr->next;
        }
    }
    string printListToString()
    {
        Node<U>* curr = front;
        std::stringstream ss;
        while (curr)
        {
            if (curr->next != nullptr)
                ss << curr->getData() << " ";
            else
                ss << curr->getData();
            curr = curr->next;
        }
        string list(ss.str());
        return list;
    }
    // return position of data
    int findData(U val) const
    {
        int idx = -1;
        Node<U> *curr = front;
        while (curr != nullptr)
        {
            ++idx;
            if (curr->getData() == val)
            {
                break;
            }
            else
            {
                curr = curr->next;
            }
        }
        
        if (curr == nullptr)
            idx = -1;
        return idx;
    }
    // -1 = NONE, 0 means one, 1 means duplicate
    int findDuplicateData(U val) const
    {
        int idx = -1;
        int total = -1;
        Node<U> *curr = front;
        while (curr != nullptr)
        {
            ++idx;
            if (curr->getData() == val)
            {
                ++total;
                if (total == 1)
                {
                    break;
                }
                curr = curr->next;
            }
            else
            {
                curr = curr->next;
            }
        }
        
        if (curr == nullptr)
            total = -1;
        return total;
    }
    U getFrontData()
    {
        return front->getData();
    }
    
    U getDataAtPosition(int pos)
    {
        Node<U> *curr = front;
        int idx = 0;
        while (curr != nullptr)
        {
            
            if (pos == idx)
            {
                
                return curr->getData();
            }
            else
            {
                curr = curr->next;
            }
            ++idx;
        }
        //if (curr == nullptr)
            return curr->getData();
    }
    bool isEmpty() const {return size <= 0;}
    unsigned int getSize() const {return size;}
private:
    Node<U>* back;
    Node<U>* front;
    unsigned int size;
};


// U removeKey(U key)



#endif /* DoublyLinkedList_h */


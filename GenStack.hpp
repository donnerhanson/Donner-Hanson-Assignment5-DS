//
//  GenStack.hpp
//  GenStack
//
//  Created by Donner Hanson on 2/21/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#ifndef GenStack_hpp
#define GenStack_hpp

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <stdio.h>

// access 6 spots
const unsigned int ARR_MAX = 6;
const int STACK_INDEX_VAL = -1;

using namespace std;
template <typename T>
class GenStack{
public:
    GenStack() : sizeM(ARR_MAX), numElems (0), topElem(-1) // default constructor
    {
        // initialize size of array
        internalArr = new T[sizeM];
    }
    GenStack(unsigned int sz) : sizeM(sz), numElems(0), topElem(-1)
    {
        // initialize size of array
        internalArr = new T[sizeM];
    }
    ~GenStack()
    {
        delete [] internalArr;
    }
    
    void push(T d)
    {
        if (!isFull())
        {
            internalArr[++topElem] = d;
            numElems++;
        }
        else
        {
            resizeLarger();
            internalArr[++topElem] = d;
            numElems++;
        }
    }
    void push(T* d)
    {
        if (!isFull())
        {
            internalArr[++topElem] = *d;
            numElems++;
        }
        else
        {
            resizeLarger();
            internalArr[++topElem] = *d;
            numElems++;
        }
    }
    T pop()
    {
        try{
            if (isEmpty())
                throw runtime_error("Error: Can not pop from empty stack\n");
            numElems--;
            return internalArr[topElem--];
        }
        catch(runtime_error &e)
        {
            cout << e.what();
            throw e;
        }
    }
    
    T top() const // aka Peek
    {
        try{
            if (isEmpty())
                throw runtime_error("Error: No items in stack\n");
            return internalArr[topElem];
        }
        catch(runtime_error &e)
        {
            cout << e.what();
            throw e;
        }
    }
    bool isFull() const
    {
        return (numElems == sizeM - 1);
    }
    bool isEmpty() const
    {
        return (numElems == 0);
    }
    unsigned int getSize()
    {
        return numElems;
    }
    unsigned int getSizeM()
    {
        return sizeM;
    }
    
private:
    void resizeLarger()
    {
        // tempArr is + SIZE_M size
        T* tempArr = new T [sizeM + ARR_MAX];
        // copy elements from source, size source, into temp
        copy(internalArr, internalArr + sizeM, tempArr);
        // set size accessible to new size - 1
        sizeM += ARR_MAX - 1;
        // swap the two pointers
        swap(internalArr, tempArr);
        // delete the old array
        delete [] tempArr;
    }
    void resizeSmaller()
    {
        // tempArr is - ARR_MAX size
        T* tempArr = new T [numElems + 1];
        // copy elements from source, size source, into temp
        copy(internalArr, internalArr + numElems + 1, tempArr);
        // set size accessible to new size - 1
        sizeM = numElems + 1;
        // swap the two pointers
        swap(internalArr, tempArr);
        // delete the old array
        delete [] tempArr;
    }
    unsigned int sizeM;
    int topElem;
    T* internalArr;
    int numElems;
};
#endif /* GenStack_hpp */

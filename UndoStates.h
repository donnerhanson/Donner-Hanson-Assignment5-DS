//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : UndoStates.h
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : track any changes made to BSTs in the data base and
//               store the copies of the BSTs. Return copies when
//               called
//================================================================

#ifndef UndoStates_h
#define UndoStates_h

#include "BST.h"
#include "GenStack.hpp"
#include "Person.h"
#include "Student.hpp"
#include "Faculty.hpp"


class UndoStates {
    
    enum EnumStates{
        None,
        ChangedState
    };
    
public:
    UndoStates()
    {
        
        states.push(None);
    }
    ~UndoStates()
    {
        ;
    }

    bool CanUndo();
    
    void SaveState(BST<Student> studCopy, BST<Faculty> facCopy);
    
    int GetLastAction();
    BST<Student> GetLastStudentTree();
    BST<Faculty> GetLastFacultyTree();
    void removeLastState();
    

private:
    
    GenStack <BST<Student> > studentTreeCopy;
    GenStack <BST<Faculty> > facultyTreeCopy;
    
    GenStack<int> states;

};


#endif /* UndoStates_h */

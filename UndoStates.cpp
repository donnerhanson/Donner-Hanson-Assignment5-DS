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

#include <iostream>
using std::cout;

#include "UndoStates.h"
bool UndoStates::CanUndo()
{
    if (states.top() == None)
        cout << "\nNothing to Undo...\n";
    return states.top() != None;
}

void UndoStates::SaveState(BST<Student> studCopy, BST<Faculty> facCopy)
{
    BST<Student> tempStud(studCopy);
    studentTreeCopy.push(tempStud);
    facultyTreeCopy.push(facCopy);
    states.push(ChangedState);
}

int UndoStates::GetLastAction()
{
    return states.top();
}
BST<Student> UndoStates::GetLastStudentTree()
{
    return studentTreeCopy.pop();
}
BST<Faculty> UndoStates::GetLastFacultyTree()
{
    
    return facultyTreeCopy.pop();
}
void UndoStates::removeLastState()
{
    states.pop();
}


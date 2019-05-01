//
//  UndoStates.h
//  Assignment_5_DS
//
//  Created by Donner Hanson on 4/24/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

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

    bool CanUndo()
    {
        if (states.top() == None)
            cout << "\nNothing to Undo...\n";
        return states.top() != None;
    }
    
    void SaveState(BST<Student> studCopy, BST<Faculty> facCopy)
    {
        BST<Student> tempStud(studCopy);
        studentTreeCopy.push(tempStud);
        facultyTreeCopy.push(facCopy);
        states.push(ChangedState);
    }
    
    int GetLastAction()
    {
        return states.top();
    }
    BST<Student> GetLastStudentTree()
    {
        return studentTreeCopy.pop();
    }
    BST<Faculty> GetLastFacultyTree()
    {
        
        return facultyTreeCopy.pop();
    }
    void removeLastState()
    {
        states.pop();
    }
    

private:
    
    GenStack <BST<Student> > studentTreeCopy;
    GenStack <BST<Faculty> > facultyTreeCopy;
    
    GenStack<int> states;

};


#endif /* UndoStates_h */

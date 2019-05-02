//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : Faculty.hpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Faculty class
//================================================================

#ifndef Faculty_hpp
#define Faculty_hpp

#include <iostream>
#include <string>

#include "DoublyLinkedList.h"
#include "Person.h"
#include "Student.hpp"

using std::string;
using std::ostream;
class Faculty : public Person
{
    
    // compare to other Faculty
    friend bool operator== (const Faculty &c1, const Faculty &c2);
    friend bool operator!= (const Faculty &c1, const Faculty &c2);
    friend bool operator> (const Faculty &c1, const Faculty &c2);
    friend bool operator< (const Faculty &c1, const Faculty &c2);
    
    // compare to integers
    friend bool operator== (const int &c2, const Faculty &c1);
    friend bool operator!= (const int &c2, const Faculty &c1);
    friend bool operator> (const int &c2, const Faculty &c1);
    friend bool operator< (const int &c2, const Faculty &c1);
    
    friend bool operator== (const Faculty &c1, const int &c2);
    friend bool operator!= (const Faculty &c1, const int &c2);
    friend bool operator> (const Faculty &c1, const int &c2);
    friend bool operator< (const Faculty &c1, const int &c2);
    
    
    friend ostream& operator << (ostream& out, const Faculty& fac);
    
    
public:
    
    // Test Constructor
    Faculty(string name, int ID, string level): Person (name,ID, level){};
    
    // Full Constructor
    Faculty(string name, int ID, string level, string department, DoublyLinkedList<int>studentIDList): Person(name,ID, level), department(department), studentIDList(studentIDList){};
    // Constructor w/o List
    Faculty(string name, int ID, string level, string department): Person(name,ID, level), department(department){};
    
    
    Faculty(Faculty &source) : Person(source.getName(), source.getID(), source.getLevel()), studentIDList (source.studentIDList)
    {
        this->department = source.department;
    }
    Faculty(Faculty* &source) : Person(source->getName(), source->getID(), source->getLevel())
    {
        this->department = source->department;
        this->studentIDList = source->studentIDList;
    }
    Faculty(Faculty const &source) : Person(source.getName(), source.getID(), source.getLevel())
    {
        department = source.department;
        
        DoublyLinkedList <int> *temp = new DoublyLinkedList<int>(source.studentIDList);
        
        studentIDList = *temp;
    }
    
    
    virtual void printInfo()
    {
        cout << "Faculty Information\n----------\n";
        cout << "Faculty ID:" << getID() << "\n"
        << "Name: " << getName() << "\n"
        << "Level: " << getLevel() << "\n"
        << "Department: " << getDepartment() << "\n\n";
    }
    
    int getID() const
    {
        return Person::getID();
    }
    string getName() const
    {
        return Person::getName();
    }
    string getLevel() const
    {
        return Person::getLevel();
    }
    string getDepartment() const
    {
        return department;
    }
    // check to see if student exists in faculty Members list
    bool ContainsStudent(int studIDnum) const
    {
        // returns -1 if not in list
        return (studentIDList.findData(studIDnum) >= 0);
    }
    
    /* ADD */
    // add a new student to memberlist
    bool AddStudent(int studIDNum)
    {
        if (!(ContainsStudent(studIDNum)))
        {
            studentIDList.insertFront(studIDNum);
            return true;
        }
        //cout << "Student with that ID already exists\n";
        return false;
    }
    bool AddStudent(Student stud)
    {
        int studIDNum = stud.getID();
        if (!(ContainsStudent(studIDNum)))
        {
            studentIDList.insertFront(studIDNum);
            return true;
        }
        cout << "Student with that ID already exists\n";
        return false;
    }
    bool AddStudent(Student *stud)
    {
        int studIDNum = stud->getID();
        if (!(ContainsStudent(studIDNum)))
        {
            studentIDList.insertFront(studIDNum);
            return true;
        }
        cout << "Student with that ID already exists\n";
        return false;
    }
    
    
    /* REMOVE */
    // remove student from member list
    bool RemoveStudent(int studIDNum)
    {
        // removeIntKey returns -1 if student not in list
        if (studentIDList.removeIntKey(studIDNum) == -1)
        {
            cout << "Student not in list\n";
            return false;
        }
        return true;
    }
    bool RemoveStudent(Student stud)
    {
        int studIDNum = stud.getID();
        return RemoveStudent(studIDNum);
    }
    bool RemoveStudent(Student *stud)
    {
        int studIDNum = stud->getID();
        return RemoveStudent(studIDNum);
    }
    // ID LIST
    
    // returns the full list for reading
    DoublyLinkedList<int> getStudentIDList() const
    {
        return studentIDList;
    }
    void AddIDToList(int studentIDNum)
    {
        studentIDList.insertFront(studentIDNum);
    }
    void printStudentListIDs()
    {
        studentIDList.printList();
    }
    
private:
    /*Faculty records contain:
     an integer Faculty ID (base class),
     a String name (base class),
     a String level (base class)*/
    
    // String department
    string department;
    // list of integers corresponding to all of the faculty member’s advisees’ ids.*/
    DoublyLinkedList<int> studentIDList;
    
};

// compare to other Faculty
bool operator== (const Faculty &c1, const Faculty &c2);
bool operator!= (const Faculty &c1, const Faculty &c2);
bool operator> (const Faculty &c1, const Faculty &c2);
bool operator< (const Faculty &c1, const Faculty &c2);

// compare to integers
bool operator== (const int &c2, const Faculty &c1);
bool operator!= (const int &c2, const Faculty &c1);
bool operator> (const int &c2, const Faculty &c1);
bool operator< (const int &c2, const Faculty &c1);


bool operator== (const Faculty &c1, const int &c2);
bool operator!= (const Faculty &c1, const int &c2);
bool operator> (const Faculty &c1, const int &c2);
bool operator< (const Faculty &c1, const int &c2);

ostream& operator << (ostream& out, const Faculty& fac);

#endif /* Faculty_hpp */



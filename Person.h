//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : Person.h
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Base class for faculty and students
//================================================================

#ifndef Person_h
#define Person_h

#include <string>
using std::string;
class Person
{
public:
    explicit
    Person(string name, int ID, string level) : name(name), ID(ID), level(level){};
    
    ~Person(){}
    
    Person(const Person& source)
    {
        
        this->name = source.name;
        this->ID = source.ID;
        this->level = source.level;
        
    }
    virtual void printInfo() = 0;
    
    
    string getName()const {return name;}
    int getID()const {return ID;}
    string getLevel()const {return level;}
    
    
    
    
    
private:
    string name;
    int ID;
    string level;
};


#endif /* Person_h */

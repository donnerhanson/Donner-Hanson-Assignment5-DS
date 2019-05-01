//
//  Person.h
//  Assignment_5_DS
//
//  Created by Donner Hanson on 4/22/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

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

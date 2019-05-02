//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : Faculty.cpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Faculty class
//================================================================

#include <iostream>


#include "Faculty.hpp"
// compare to other Faculty
bool operator== (const Faculty &c1, const Faculty &c2)
{
    return c1.getID() == c2.getID();
}
bool operator!= (const Faculty &c1, const Faculty &c2)
{
    return !(c1 == c2);
}
bool operator> (const Faculty &c1, const Faculty &c2)
{
    return c1.getID() > c2.getID();
}
bool operator< (const Faculty &c1, const Faculty &c2)
{
    return c1.getID() < c2.getID();
}

// compare to integers
bool operator== (const int &c2, const Faculty &c1)
{
    return c2 == c1.getID();
}
bool operator!= (const int &c2, const Faculty &c1)
{
    return !(c2 == c1);
}
bool operator> (const int &c2, const Faculty &c1)
{
    return c2 > c1.getID();
}
bool operator< (const int &c2, const Faculty &c1)
{
    return c2 < c1.getID();
}

bool operator== (const Faculty &c1, const int &c2)
{
    return c1.getID() == c2;
}
bool operator!= (const Faculty &c1, const int &c2)
{
    return !(c1 == c2);
}
bool operator> (const Faculty &c1, const int &c2)
{
    return c1.getID() > c2;
}
bool operator< (const Faculty &c1, const int &c2)
{
    return c1.getID() > c2;
}


ostream& operator << (ostream& out, const Faculty& fac)
{
    // https://stackoverflow.com/questions/3318714/check-if-ostream-object-is-cout-or-ofstream-c
    // is the stream going to std out or not
    if (out.rdbuf() == cout.rdbuf())
    {
        out << "ID: " << fac.getID()
        << "\nName: " << fac.getName()
        << "\nOccupation: " << fac.getLevel()
        << "\nDepartment: " << fac.getDepartment()
        << "\n|" << fac.getStudentIDList().printListToString() << "|\n";
    }
    else
    {
        out << "ID: " << fac.getID()
        << "\nName: " << fac.getName()
        << "\nOccupation: " << fac.getLevel()
        << "\nDepartment: " << fac.getDepartment()
        << "\n|" << fac.getStudentIDList().printListToString() << "|\n";
    }
    
    return out;
}

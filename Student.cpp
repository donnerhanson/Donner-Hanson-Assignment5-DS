//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : Student.cpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Student class
//================================================================

#include <iostream>

#include "Student.hpp"

using std::ostream;

// compare to other student
bool operator== (const Student &c1, const Student &c2)
{
    return c1.getID()== c2.getID();
}
bool operator!= (const Student &c1, const Student &c2)
{
    return !(c1 == c2);
}
bool operator> (const Student &c1, const Student&c2)
{
    return c1.getID() > c2.getID();
}
bool operator< (const Student &c1, const Student&c2)
{
    return c1.getID() < c2.getID();
}

// compare to integer
bool operator== (const int &c2, const Student &c1)
{
    return c2 == c1.getID();
}
bool operator!= (const int &c2,const Student &c1)
{
    return !(c2 == c1);
}
bool operator> (const int &c2, const Student &c1)
{
    return c2 > c1.getID();
}
bool operator< (const int &c2, const Student &c1)
{
    return c2 < c1.getID();
}

bool operator== (const Student &c1, const int &c2)
{
    return c1.getID() == c2;
}
bool operator!= (const Student &c1, const int &c2)
{
    return !(c1 == c2);
}
bool operator> (const Student &c1, const int &c2)
{
    return c1.getID() > c2;
}
bool operator< (const Student &c1, const int &c2)
{
    return c1.getID() < c2;
}


ostream& operator << (ostream& out, const Student& student)
{
    if (out.rdbuf() == cout.rdbuf())
    {
    out << "ID: " << student.getID()
    << "\nName: " << student.getName()
    << "\nLevel: " << student.getLevel()
    << "\nMajor: " << student.maj
    << "\nGPA: " << student.GPA
    << "\nAdvisor: " << student.advisorID << "\n";
    }
    else
    {
        out << student.getID()
        << "\n" << student.getName()
        << "\n" << student.getLevel()
        << "\n" << student.maj
        << "\n" << student.GPA
        << "\n" << student.advisorID
        << "\n";
    }
    return out;
}


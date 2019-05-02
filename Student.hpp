//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : Student.hpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Student class
//================================================================

#ifndef Student_hpp
#define Student_hpp

#include <iostream>
#include <string>


#include "Person.h"

using std::string;
using std::ostream;
using std::cout;
using namespace std;
class Student : public Person
{
    // compare to other students
    friend bool operator== (const Student &c1, const Student &c2);
    friend bool operator!= (const Student &c1, const Student &c2);
    friend bool operator> (const Student &c1, const Student &c2);
    friend bool operator< (const Student &c1, const Student &c2);
    
    // compare to integers
    friend bool operator== (const int &c2, const Student &c1);
    friend bool operator!= (const int &c2, const Student &c1);
    friend bool operator> (const int &c2, const Student &c1);
    friend bool operator< (const int &c2, const Student &c1);
    friend bool operator== (const Student &c1, const int &c2);
    friend bool operator!= (const Student &c1, const int &c2);
    friend bool operator> (const Student &c1, const int &c2);
    friend bool operator< (const Student &c1, const int &c2);
    
    
    friend ostream& operator << (ostream& out, const Student& stud);
    
public:
    // Full Constructor
    Student(string name, int ID, string level,
            string maj, int advisorID, double GPA):
                Person(name,ID, level), maj(maj), GPA(GPA),
                    advisorID(advisorID){};

    Student(Student const &source) :
    Person(source.getName(), source.getID(), source.getLevel())
    {
        this->maj = source.maj;
        this->GPA= source.GPA;
        this->advisorID = source.advisorID;
    }
    
    
    virtual void printInfo()
    {
        cout << "Student ID:" << getID() << "\n"
        << "Name: " << getName() << "\n"
        << "Level: " << getLevel() << "\n"
        << "Major: " << getMajor() << "\n"
        << "Advisor ID: " << getAdvisorID() << "\n"
        << "GPA: " << getGPA() << "\n\n";
    }
    
    void setAdvisor(int inAdvisorID)
    {
        advisorID = inAdvisorID;
    }
    
    string getMajor(){return maj;}
    int getAdvisorID(){return advisorID;}
    double getGPA(){return GPA;}

    
private:
    /*
     unique student ID (an integer) (base class),
     String name field(base class)
     String level (base Class)
     */
     //String major field
    string maj;
     //double GPA field
    double GPA;
     //integer advisor field - which will contain the Faculty ID of their advisor
    int advisorID;
    
    
    
};

bool operator== (const Student &c1, const Student &c2);
bool operator!= (const Student &c1, const Student &c2);
bool operator> (const Student &c1, const Student &c2);
bool operator< (const Student &c1, const Student &c2);

bool operator== (const int &c2, const Student &c1);
bool operator!= (const int &c2, const Student &c1);
bool operator> (const int &c2, const Student &c1);
bool operator< (const int &c2, const Student &c1);

bool operator== (const Student &c1, const int &c2);
bool operator!= (const Student &c1, const int &c2);
bool operator> (const Student &c1, const int &c2);
bool operator< (const Student &c1, const int &c2);


ostream& operator << (ostream& out, const Student& Student);
#endif /* Student_hpp */

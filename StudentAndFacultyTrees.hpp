//
//  StudentAndFacultyTrees.hpp
//  Assignment_5_DS
//
//  Created by Donner Hanson on 4/25/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#ifndef StudentAndFacultyTrees_hpp
#define StudentAndFacultyTrees_hpp

#include <fstream>
#include <iomanip>      // std::setprecision
#include <iostream>
#include <limits.h> // INT_MAX
#include <stdio.h>
#include <sstream>
#include <string>


#include "BST.h"
#include "Error.h"
#include "FileHandler.hpp"
#include "Faculty.hpp"
#include "Student.hpp"
#include "UndoStates.h"



using namespace std;

const string STUDENT_FILE = "studentTable.txt";
const string FACULTY_FILE = "facultyTable.txt";




class StudentAndFacultyTrees
{
public:
    
    
    enum EnumStates{
        None,
        ChangedState
    };
    
    StudentAndFacultyTrees()
    {
        ;
    }
    int StringToInt(string &str)
    {
        int number;
        std::istringstream iss(str);
        iss >> number;
        return number;
    }
    double StringToDouble(string &str)
    {
        double number;
        std::istringstream iss(str);
        iss >> number;
        return number;
    }
    void FillStudentsFromFile()
    {
        // facultyTable.txt and studentTable.txt
        try {
            ifstream inFileStream;
            if (fh.SafeOpenForRead(inFileStream, STUDENT_FILE))
            {
                if (!fh.fileIsBlank(inFileStream))
                {
                    string name, major, level;
                    int ID = 0, advisorID = 0;
                    double GPA = 0;
                    
                    // Full Constructor Student(string name, int ID, string level, string major, int advisorID, double GPA)
                    int counter(0);
                    string str;
                    while (getline(inFileStream, str)) {
                        //str.pop_back();
                        
                        if (counter == 0)
                        {
                            ID = StringToInt(str);
                            while (ID < 1)
                            {
                                cout << "Stored ID is invalid.\n";
                                cout << "Student ID - ";
                                ID = EnterID();
                            }
                        }
                        if (counter == 1)
                        {
                            name = str;
                        }
                        if (counter == 2)
                        {
                            level = str;
                        }
                        if (counter == 3)
                        {
                            major = str;
                        }
                        if (counter == 4)
                        {
                            GPA = StringToDouble(str);
                        }
                        if (counter == 5)
                        {
                            advisorID = StringToInt(str);
                            while (advisorID < 1 || !facultyTree.contains(advisorID))
                            {
                                cout << "Stored Advisor ID is invalid.\nStudent reference to advisor may have been not set\nValid faculty: \n";
                                facultyTree.printTree();
                                cout << "Advisor ID - ";
                                advisorID = EnterID();
                            }
                            if (facultyTree.contains(advisorID))
                            {
                                // if the faculty member List has the student  and student tree doesnt contain the student and not a dup
                                if (facultyTree.get(advisorID).ContainsStudent(ID) && !studentTree.contains(ID) && !(facultyTree.get(advisorID).getStudentIDList().findDuplicateData(ID) > 0))
                                {
                                    // create an advisor copy
                                    Faculty* updatedNext = new Faculty(facultyTree.get(advisorID));
                                    // update advisors list
                                    updatedNext->AddStudent(ID);
                                    // remove advisor from list
                                    facultyTree.deleter(advisorID);
                                    // insert new faculty member
                                    facultyTree.insert(*updatedNext);
                                    //delete updatedNext; - tree cleans this
                                }
                                // Faculty member exists and wasn't updated - assign
                                else if (!facultyTree.get(advisorID).ContainsStudent(ID) && !studentTree.contains(ID) && !(facultyTree.get(advisorID).getStudentIDList().findDuplicateData(ID) > 0))
                                {
                                    
                                    if (!facultyTree.get(advisorID).ContainsStudent(ID))
                                    {
                                        facultyTree.RemoveStudentFromTree(ID);
                                        
                                    }
                                    // create an advisor copy
                                    Faculty* updatedNext = new Faculty(facultyTree.get(advisorID));
                                    // update advisors list
                                    updatedNext->AddStudent(ID);
                                    // remove advisor from list
                                    facultyTree.deleter(advisorID);
                                    // insert new faculty member
                                    facultyTree.insert(*updatedNext);
                                    
                                    //delete updatedNext; - tree cleans this
                                }
                                // -1 = NONE, 0 means one student, 1 means duplicate
                                // advisor has dup but student ID OK
                                else if (facultyTree.get(advisorID).getStudentIDList().findDuplicateData(ID) > 0 && !studentTree.contains(ID))
                                {
                                    cout << "Duplicate ID For Advisor - Enter new ID for " << name << " \n";
                                    cout << "Invalid IDs to assign: \n";
                                    facultyTree.get(advisorID).getStudentIDList().printList();
                                    while (facultyTree.get(advisorID).getStudentIDList().findDuplicateData(ID) > 0 && !studentTree.contains(ID))
                                        ID = EnterID();
                                    // create an advisor copy
                                    Faculty* updatedNext = new Faculty(facultyTree.get(advisorID));
                                    // update advisors list
                                    updatedNext->AddStudent(ID);
                                    // remove advisor from list
                                    facultyTree.deleter(advisorID);
                                    // insert new faculty member
                                    facultyTree.insert(*updatedNext);
                                    //delete updatedNext; - tree cleans this
                                }
                                else if (!(facultyTree.get(advisorID).getStudentIDList().findDuplicateData(ID) > 0) && studentTree.contains(ID)) // duplicate for studentTree
                                {
                                    cout << "Duplicate Student Tree ID - Enter new ID for " << name << " \n";
                                    facultyTree.get(advisorID).getStudentIDList().printList();
                                    
                                    while (facultyTree.get(advisorID).getStudentIDList().findDuplicateData(ID) > 0 && !studentTree.contains(ID))
                                        ID = EnterID();
                                    // create an advisor copy
                                    Faculty* updatedNext = new Faculty(facultyTree.get(advisorID));
                                    // update advisors list
                                    updatedNext->AddStudent(ID);
                                    // remove advisor from list
                                    facultyTree.deleter(advisorID);
                                    // insert new faculty member
                                    facultyTree.insert(*updatedNext);
                                    //delete updatedNext; - tree cleans this
                                }
                            }
                            else // faculty member does not exist
                            {
                                while (!(facultyTree.contains(advisorID)))
                                {
                                    cout << "Faculty member " << advisorID << " does not exist.\nEnter a valid advisor ID.\n";
                                    facultyTree.printTree();
                                    advisorID = EnterID();
                                    
                                }
                                // create an advisor copy
                                Faculty* updatedNext = new Faculty(facultyTree.get(advisorID));
                                // update advisors list
                                updatedNext->AddStudent(ID);
                                // remove advisor from list
                                facultyTree.deleter(advisorID);
                                // insert new faculty member
                                facultyTree.insert(*updatedNext);
                                //delete updatedNext; - tree cleans this
                                
                                
                            }
                            
                            Student* stud = new Student (name, ID, level, major, advisorID, GPA);
                            studentTree.insert(*stud);
                            // TEST - see if lists do cleanup
                            //delete stud;
                        }
                        counter++;
                        if (counter > 5)
                        {
                            counter = 0;
                        }
                        
                        
                        //name >> ID >> level >> major >> advisorID >> GPA
                    }
                    
                    if (inFileStream.bad())
                    {
                        throw Error("Infile stream bad");
                    }
                    else if (!inFileStream.eof())
                    {
                        // format error (not possible with getline but possible with operator>>)
                        throw Error("Formatting issue");
                    }
                    else if (counter != 0)
                    {
                        throw Error("File reached EOF with partially read student. Check file for integrity.\n");
                    }
                    
                }
                
            }
            if (inFileStream.is_open())
            {
                inFileStream.close();
            }
            else
            {
                cout << "ELSE:";
                cout << "Creating new file: " << STUDENT_FILE << "...\n";
                
                std::ofstream output( STUDENT_FILE, std::ios::out);
                if( !output.is_open() )
                {
                    throw Error("*** error: could not open output file!\n");
                }
                else if( output.is_open() )
                {
                    cout << "Outfile opened success..\n";
                    
                    output.close();
                }
            }
            cin.clear();
        }
        catch (Error &e)
        {
            // CATCH INPUT/STREAM ERROR
            
            cout << e.what() << "\n";
            cout << "Exiting\n";
            throw e;
        }
    }
    void FillAdvisorsFromFile()
    {
        // facultyTable.txt and studentTable.txt
        try {
            ifstream inFileStream;
            if (fh.SafeOpenForRead(inFileStream, FACULTY_FILE))
            {
                if (!fh.fileIsBlank(inFileStream))
                {
                    string name, department, level;
                    int ID = 0;
                    
                    // Faculty(string name, int ID, string level, string department): Person(name,ID, level), department(department){};
                    int counter(0);
                    string str;
                    while (getline(inFileStream, str)) {
                        //str.pop_back();
                        
                        if (counter == 0)
                        {
                            /*
                             ID: 1
                             */
                            str.erase(0, 4);
                            ID = StringToInt(str);
                        }
                        if (counter == 1)
                        {
                            /*
                             Name: Donner
                             */
                            str.erase(0, 6);
                            name = str;
                        }
                        if (counter == 2)
                        {
                            /*
                             Occupation: .....
                             */
                            str.erase(0, 12);
                            level = str;
                        }
                        if (counter == 3)
                        {
                            /*
                             Department: sf
                             */
                            str.erase(0, 12);
                            department = str;
                        }
                        if (counter == 4)
                        {
                            /*
                             |9 32 34 23 10|
                             */
                            // get a substring without the begin and ending || delimiters
                            str = str.substr(1, str.size() - 2);
                            DoublyLinkedList<int> *tempList = new DoublyLinkedList<int>();
                            stringstream stream(str);
                            int n;
                            while(stream >> n)
                            {
                                tempList->insertFront(n);
                            }
                            Faculty* fac = new Faculty( name, ID, level,  department, *tempList);
                            facultyTree.insert(*fac);
                            delete fac;
                            delete tempList;
                        }
                        counter++;
                        if (counter > 4)
                        {
                            counter = 0;
                        }
                    }
                    
                    if (inFileStream.bad())
                    {
                        throw Error("Infile stream bad...\n");
                    }
                    else if (!inFileStream.eof())
                    {
                        // format error (not possible with getline but possible with operator>>)
                        throw Error("Formatting issue...\n");
                    }
                    else if (counter != 0)
                    {
                        throw Error("File reached EOF with partially read Faculty. Check file for integrity...\n");
                    }
                    
                }
                
            }
            if (inFileStream.is_open())
            {
                inFileStream.close();
            }
            else
            {
                cout << "ELSE:";
                cout << "Creating new file: " << FACULTY_FILE << "\n";
                
                std::ofstream output( FACULTY_FILE, std::ios::out);
                if( !output.is_open() )
                {
                    cout << "*** error: could not open output file\n";
                }
                else if( output.is_open() )
                {
                    cout << "outfile opened success";
                    
                    output.close();
                    cout << "File Closed until exit";
                }
            }
        }
        catch (Error &e)
        {
            // CATCH INPUT/STREAM ERROR
            
            cout << e.what() << "\n";
            cout << "Exiting\n";
            throw e;
        }
    }
    void ChooseFunction();
    
private:
    
    // PRIVATE MEM FXNS
    
    //1. Print all students and their information (sorted by ascending id #)
    void PrintAllStudents() const;
    //2. Print all faculty and their information (sorted by ascending id #)
    void PrintAllFalculty() const;
    //3. Find and display student information given the students id
    void FindAndDisplayStudent(int IDnum) const;
    //4. Find and display faculty information given the faculty id
    void FindAndDisplayFaculty(int IDnum) const;
    //5. Given a student’s id, print the name and info of their faculty advisor
    void FindAndDisplayStudentsAdvisor(int IDnum) const;
    //6. Given a faculty id, print ALL the names and info of his/her advisees.
    void FindAndDisplayAdvisorsStudents(int IDnum) const;
    //7. Add a new student
    void AddStudent();
    //8. Delete a student given the id
    void DeleteStudent(int IDNum);
    //9. Add a new faculty member
    void AddFacultyMember();
    //10. Delete a faculty member given the id.
    void DeleteFacultyMember(int IDnum);
    //11. Change a student’s advisor given the student id and the new faculty id.
    void ChangeStudentAdvisor(int StudentID, int FacultyID);
    //12. Remove an advisee from a faculty member given the ids
    void RemoveStudentFromFacultyRef(int StudentID, int FacultyID);
    //13. Rollback
    void RollBack();
    //14. Exit
    void Exit();
    
    
    int EnterID()
    {
        // https://stackoverflow.com/questions/13212043/integer-input-validation-how
        int ID (-1);
        cout << "Enter a valid ID between 1 - " << INT_MAX - 1
        << " followed by <Return>: \n";
        std::string  line;
        while(std::getline(std::cin, line))   // read a line at a time for parsing.
        {
            std::stringstream linestream(line);
            if (!(linestream >> ID))
            {
                // input was not a number
                // Error message and try again
                cout << "Enter a valid ID between 1 - " << INT_MAX - 1
                << " followed by <Return>: \n";
                continue;
            }
            if (ID < 1 || ID >= INT_MAX)
            {
                // Error out of range
                // Message and try again
                cout << "Enter a valid ID between 1 - " <<  INT_MAX - 1
                << "followed by <Return>: \n";
                continue;
            }
            char errorTest;
            if (linestream >> errorTest)
            {
                // There was extra stuff on the same line.
                // ie sobody typed 2x<enter>
                // Error Message;
                cout << "Enter a valid ID between 1 - " << INT_MAX - 1
                << " followed by <Return>: \n";
                continue;
            }
            
            // it worked perfectly.
            // The value is now in input.
            // So break out of the loop.
            break;
        }
        return ID;
    }
    int EnterChoice()
    {
        // https://stackoverflow.com/questions/13212043/integer-input-validation-how
        int choice (-1);
        cout << "Enter a valid choice between 1 - 14 followed by <Return>: \n";
        std::string  line;
        while(std::getline(std::cin, line))   // read a line at a time for parsing.
        {
            std::stringstream linestream(line);
            if (!(linestream >> choice))
            {
                // input was not a number
                // Error message and try again
                cout << "Enter a valid choice between 1 - 14 followed by <Return>: \n";
                continue;
            }
            if (choice < 1 || choice > 14)
            {
                // Error out of range
                // Message and try again
                cout << "Enter a valid choice between 1 - 14 followed by <Return>: \n";
                continue;
            }
            char errorTest;
            if (linestream >> errorTest)
            {
                // There was extra stuff on the same line.
                // ie sobody typed 2x<enter>
                // Error Message;
                cout << "Enter a valid choice between 1 - 14 followed by <Return>: \n";
                continue;
            }
            
            // it worked perfectly.
            // The value is now in input.
            // So break out of the loop.
            break;
        }
        return choice;
    }
    
    bool studentInFacultyList(int studID, int facID)
    {
        bool found = false;
        if (!facultyTree.isEmpty() && facultyTree.contains(facID))
        {
            DoublyLinkedList<int>* studIDs = new DoublyLinkedList<int>(facultyTree.get(facID).getStudentIDList());
            if ( studIDs->findData(studID) != -1)
            {
                found = true;
            }
            else
            {
                cout << "Student ID not linked to a faculty member\n";
            }
            delete studIDs;
        }
        else
        {
            cout << "Faculty member does not exist\n";
        }
        return found;
    }
    
    int EnterIDOrAbort()
    {
        // https://stackoverflow.com/questions/13212043/integer-input-validation-how
        int ID (-10);
        cout << "Enter a valid ID between 1 - " << INT_MAX - 1
        << " or -1 to abort followed by <Return>: \n";
        std::string  line;
        cin.clear();
        while(std::getline(std::cin, line))   // read a line at a time for parsing.
        {
            std::stringstream linestream(line);
            if (!(linestream >> ID))
            {
                // input was not a number
                // Error message and try again
                cout << "Enter a valid ID between 1 - " << INT_MAX - 1
                << " or -1 to abort followed by <Return>: \n";
                continue;
            }
            if ((ID != -1) && (ID < 1 || ID >= INT_MAX))
            {
                // Error out of range
                // Message and try again
                cout << "Enter a valid ID between 1 - " << INT_MAX - 1
                << " or -1 to abort followed by <Return>: \n";
                continue;
            }
            char errorTest;
            if (linestream >> errorTest)
            {
                // There was extra stuff on the same line.
                // ie sobody typed 2x<enter>
                // Error Message;
                cout << "Enter a valid ID between 1 - " << INT_MAX - 1
                << " or -1 to abort followed by <Return>: \n";
                continue;
            }
            
            // it worked perfectly.
            // The value is now in input.
            // So break out of the loop.
            break;
        }
        return ID;
    }
    
    
    // PRIVATE MEMBERS
    UndoStates currUndo;
    BST<Student> studentTree;
    BST<Faculty> facultyTree;
    FileHandler fh;
};

#endif /* StudentAndFacultyTrees_hpp */

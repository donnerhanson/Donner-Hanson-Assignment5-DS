//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : StudentAndFacultyTrees.cpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Bulk of the program
/*
 Offer choices
 1. Print all students and their information (sorted by ascending id #)
 2. Print all faculty and their information (sorted by ascending id #)
 3. Find and display student information given the students id
 4. Find and display faculty information given the faculty id
 5. Given a student’s id, print the name and info of their faculty advisor
 6. Given a faculty id, print ALL the names and info of his/her advisees.
 7. Add a new student
 8. Delete a student given the id
 9. Add a new faculty member
 10. Delete a faculty member given the id.
 11. Change a student’s advisor given the student id and the new faculty id.
 12. Remove an advisee from a faculty member given the ids
 13. Rollback
 14. Exit
 */
//================================================================

#include <iostream>
#include <limits>
#include <string>

#include "DoublyLinkedList.h"
#include "StudentAndFacultyTrees.hpp"

using std::cin;
using std::cout;

using std::getline;
using std::string;


const string FUNCTION_OPTIONS = "1. Print all students and their information "
"(sorted by ascending id #)\n2. Print all faculty and their information"
" (sorted by ascending id #)\n3. Find and display student information given"
" the students id\n4. Find and display faculty information given "
"the faculty id\n5. Given a student’s id, print the name and info of their "
"faculty advisor\n6. Given a faculty id, print ALL the names and info of "
"his/her advisees.\n7. Add a new student\n8. Delete a student given the "
"id\n9. Add a new faculty member\n10. Delete a faculty member given the "
"id.\n11. Change a student’s advisor given the student id and the new "
"faculty id.\n12. Remove an advisee from a faculty member given the "
"ids\n13. Rollback\n14. Exit\n";

const string NO_ADVISORS = "\nNo current Advisors\n";
const string NO_STUDENTS = "\nNo current Students\n";
const string AFFECT_REFERENCES_ADV = "\nThis operation may remove references"
" within Advisor tree...\n";

const string ERROR_OUTFILE = "*** error: could not open output file\n";
const string OPENING_OUT = "Opening File To Overwrite: \n";
const string SAVED = "Save success...\n";
const string ADV_ID = "Advisor ID - ";
const string STUD_ID = "Student ID -";
const string CONT = "Continue?... (Y/N): ";
const string DNE = " does not exist...\n";
const string INV_ENTRY = "Invalid Entry...\n";

void getEnter()
{
    cout << "press <Return> to continue...\n";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
}

void StudentAndFacultyTrees::ChooseFunction()
{
    //BST<Faculty> FacultyTreeCopy;
    //FacultyTreeCopy.copyOf( facultyTree.root,);
    
    cin.clear();
    int choice = 0;
    while (choice != 14)
    {
        cout << FUNCTION_OPTIONS;
        choice = EnterChoice();
        cin.clear();
        
        if (choice >= 1 && choice <= 14)
        {
            switch (choice)
            {
                    //1. Print all students and their information
                    // (sorted by ascending id #)
                case 1:
                {
                    PrintAllStudents();
                    break;
                }
                    //2. Print all faculty and their information
                    // (sorted by ascending id #)
                case 2:
                {
                    if (!facultyTree.isEmpty())
                        PrintAllFalculty();
                    else
                    {
                        cout << NO_ADVISORS;
                    }
                    break;
                }
                    //3. Find and display student information
                    // given the students id
                case 3:
                {
                    if (!facultyTree.isEmpty())
                    {
                        if (!studentTree.isEmpty())
                        {
                            int IDnum;
                            IDnum = EnterID();
                            FindAndDisplayStudent(IDnum);
                        }
                        else
                        {
                            cout << "\nStudent Tree is empty\n\n";
                        }
                    }
                    if (facultyTree.isEmpty() && studentTree.isEmpty())
                    {
                        cout << NO_ADVISORS;
                    }
                    break;
                }
                    //4. Find and display faculty information
                    // given the faculty id
                case 4:
                {
                    if (!facultyTree.isEmpty())
                    {
                        int IDnum;
                        IDnum = EnterID();
                        FindAndDisplayFaculty(IDnum);
                    }
                    else
                    {
                        cout << NO_ADVISORS;
                    }
                    break;
                }
                    //5. Given a student’s id, print the name and info
                    // of their faculty advisor
                case 5:
                {
                    if (!facultyTree.isEmpty())
                    {
                        int IDnum;
                        IDnum = EnterID();
                        FindAndDisplayStudentsAdvisor(IDnum);
                    }
                    else
                        cout << NO_ADVISORS;
                    break;
                }
                    //6. Given a faculty id, print ALL the names and info
                    // of his/her advisees.
                case 6:
                {
                    if (!facultyTree.isEmpty())
                    {
                        
                        int IDnum;
                        IDnum = EnterID();
                        if (facultyTree.contains(IDnum))
                            FindAndDisplayAdvisorsStudents(IDnum);
                        else
                            cout << "\nFaculty Member" << DNE;
                        
                        
                    }
                    else
                        cout << NO_ADVISORS;
                    break;
                }
                    //7. Add a new student
                case 7:
                {
                    if (!facultyTree.isEmpty())
                    {
                        // SAVE
                        currUndo.SaveState(studentTree, facultyTree);
                        AddStudent();
                    }
                    else
                        cout << NO_ADVISORS;
                    break;
                }
                    //8. Delete a student given the id
                case 8:
                {
                    if (!facultyTree.isEmpty())
                    {
                        int IDnum;
                        cout << AFFECT_REFERENCES_ADV;
                        
                        char yesNo = '~';
                        while (yesNo != 'Y' && yesNo != 'y'
                               && yesNo != 'N' && yesNo != 'n')
                        {
                            cout << CONT;
                            cin >> yesNo;
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            if (yesNo == 'Y'||yesNo == 'y')
                            {
                                cout << STUD_ID;
                                IDnum = EnterID();
                                int count = 0;
                                char cont = '~';
                                while (!studentTree.contains(IDnum))
                                {
                                    cout << STUD_ID << IDnum << DNE;
                                    
                                    
                                    while (cont != 'Y' && cont != 'y'
                                           && cont != 'N' && cont != 'n')
                                    {
                                        
                                        cout << CONT;
                                        
                                        cin >> cont;
                                        cin.clear();
                                        cin.ignore(
                                                   numeric_limits
                                                   <streamsize>::max(),
                                                   '\n');
                                    }
                                    if (cont == 'n' || cont == 'N')
                                    {
                                        cout << "Aborting Operation...\n";
                                        break;
                                    }
                                    cont = '~';
                                    
                                    IDnum = EnterID();
                                    cin.clear();
                                    count++;
                                }
                                // SAVE - STUDENT EXISTS - DELETE
                                currUndo.SaveState(studentTree, facultyTree);
                                DeleteStudent(IDnum);
                            }
                        }
                    }
                    else
                    {
                        cout << NO_ADVISORS;
                    }
                    break;
                }
                    //9. Add a new faculty member
                case 9:
                {
                    // SAVE
                    currUndo.SaveState(studentTree, facultyTree);
                    AddFacultyMember();
                    break;
                }
                    //10. Delete a faculty member given the id.
                case 10:
                {
                    if (!facultyTree.isEmpty())
                    {
                        if (!facultyTree.isOnlyOneObject())
                        {
                            int IDnum= -10;
                            cout << ADV_ID << "TO DELETE - ";
                            while (!facultyTree.contains(IDnum))
                            {
                                if (IDnum == -1)
                                    break;
                                IDnum = EnterIDOrAbort();
                            }
                            if (IDnum != -1)
                            {
                                currUndo.SaveState(studentTree, facultyTree);
                                DeleteFacultyMember(IDnum);
                            }
                            else
                                cout << "Aborting...\n";
                        }
                        else
                        {
                            cout << "Only one advisor remains...\n"
                            << "Cannot delete...\n";
                        }
                        
                    }
                    else
                    {
                        cout << NO_ADVISORS;
                    }
                    break;
                }
                    //11. Change a student’s advisor given the student id
                    //    and the new faculty id.
                case 11:
                {
                    if (!facultyTree.isEmpty() && !facultyTree.isOnlyOneObject())
                    {
                        if (!studentTree.isEmpty())
                        {
                            int studentID = 0, advisorID = 0;
                            cout << ADV_ID;
                            advisorID = EnterID();
                            while (!facultyTree.contains(advisorID))
                            {
                                cout << "Advisor" << DNE;
                                cout << ADV_ID;
                                advisorID = EnterID();
                            }
                            cout << STUD_ID;
                            studentID = EnterID();
                            while (!studentTree.contains(studentID))
                            {
                                cout << "Student" << DNE;
                                cout << STUD_ID;
                                studentID = EnterID();
                            }
                            if (!studentTree.contains(studentID))
                            {
                                cout << "Student" << DNE
                                << "Operation aborted\n";
                                break;
                            }
                            currUndo.SaveState(studentTree, facultyTree);
                            ChangeStudentAdvisor(studentID, advisorID);
                        }
                        else
                            cout << NO_STUDENTS;
                    }
                    else if (facultyTree.isOnlyOneObject())
                        cout << "Only one advisor... can not reassign...\n";
                    else
                    {
                        cout << NO_ADVISORS;
                    }
                    break;
                }
                    //12. Remove an advisee from a faculty member given the ids
                case 12:
                {
                    if (!facultyTree.isEmpty())
                    {
                        if (!studentTree.isEmpty())
                        {
                            cout << AFFECT_REFERENCES_ADV;
                            cout << "\nStudents without advisors must"
                            << " be manually changed during"
                            <<" runtime or at program start...\n";
                            
                            char yesNo = '~';
                            while (yesNo != 'Y' && yesNo != 'y'
                                   && yesNo != 'N' && yesNo != 'n')
                            {
                                cout << CONT;
                                cin >> yesNo;
                                cin.clear();
                                cin.ignore(
                                           numeric_limits<streamsize>::max(),
                                           '\n');
                                if (yesNo == 'Y'|| yesNo == 'y')
                                {
                                    int studentID = 0, advisorID = 0;
                                    cout << ADV_ID;
                                    advisorID = EnterID();
                                    while (!facultyTree.contains(advisorID))
                                    {
                                        cout << "Advisor" << DNE;
                                        cout << ADV_ID;
                                        advisorID = EnterID();
                                    }
                                    cout << STUD_ID;
                                    studentID = EnterID();
                                    while (!studentTree.contains(studentID))
                                    {
                                        cout << "Student" << DNE;
                                        cout << STUD_ID;
                                        advisorID = EnterID();
                                    }
                                    // Will SAVE within function if found
                                    RemoveStudentFromFacultyRef(studentID,
                                                                advisorID);
                                }
                            }
                        }
                        else
                            cout << NO_STUDENTS;
                    }
                    else
                        cout << NO_ADVISORS;
                    break;
                }
                    //13. Rollback
                case 13:
                {
                    RollBack();
                    break;
                }
                    //14. Exit
                case 14:
                {
                    Exit();
                    break;
                }
                default:
                    break;
            }
            if (choice != 14)
            {
                cin.clear();
                getEnter();
            }
        }
        else
        {
            cout << "incorrect entry\n";
        }
    }
}
// =====================================================//
//                   PRINT FUNCTIONS                    //
//======================================================//

//1. Print all students and their information (sorted by ascending id #)
void StudentAndFacultyTrees::PrintAllStudents() const
{
    
    if (!studentTree.isEmpty())
        studentTree.printTree();
    else
        cout << "\nNo Students to print\n\n";
}
//2. Print all faculty and their information (sorted by ascending id #)
void StudentAndFacultyTrees::PrintAllFalculty() const
{
    if (!facultyTree.isEmpty())
        facultyTree.printTree();
    else
        cout << "\nNo Advisors\n\n";
}
//3. Find and display student information given the students id
void StudentAndFacultyTrees::FindAndDisplayStudent(int IDnum) const
{
    if (studentTree.contains(IDnum))
        studentTree.get(IDnum).printInfo();
    else
        cout << "\nStudent does not exist\n\n";
}
//4. Find and display faculty information given the faculty id
void StudentAndFacultyTrees::FindAndDisplayFaculty(int IDnum) const
{
    if (facultyTree.contains(IDnum))
        facultyTree.get(IDnum).printInfo();
}
//5. Given a student’s id, print the name and info of their faculty advisor
void StudentAndFacultyTrees::FindAndDisplayStudentsAdvisor(int IDnum) const
{
    if (studentTree.contains(IDnum))
    {
        int advisorID = studentTree.get(IDnum).getAdvisorID();
        FindAndDisplayFaculty(advisorID);
    }
}
//6. Given a faculty id, print ALL the names and info of his/her advisees.
void StudentAndFacultyTrees::FindAndDisplayAdvisorsStudents(int IDnum) const
{
    
    if (!facultyTree.isEmpty())
    {
        DoublyLinkedList<int>* studIDs = new DoublyLinkedList<int>(facultyTree.get(IDnum).getStudentIDList());
        if (!studIDs->isEmpty())
        {
            int DLLsize;
            DLLsize = studIDs->getSize() - 1;
            while (DLLsize != -1) {
                //return the position in the DLL
                int ID = studIDs->getDataAtPosition(DLLsize);
                
                FindAndDisplayStudent(ID);
                --DLLsize;
            }
        }
        else
            cout << NO_STUDENTS;
        delete studIDs;
    }
}

//========================================================//
//                    UPDATE FUNCTIONS                    //
//========================================================//
//=============================================
//=============================================
//7. Add a new student
void StudentAndFacultyTrees::AddStudent()
{
    // ask for info about new student
    // insert student object
    string name, level, major;
    int ID, advisorID;
    double GPA = -1.0;
    string str;
    cout << STUD_ID;
    ID = EnterID();
    while (studentTree.contains(ID))
    {
        cout << "Student ID currently in use\n";
        cout << STUD_ID;
        ID = EnterID();
        cin.clear();
    }
    cin.clear();
    cout << "Enter Student Name: ";
    getline(cin, str);
    cin.clear();
    name = str;
    cout << "Enter Student Year Standing: ";
    getline(cin, str);
    cin.clear();
    level = str;
    cout << "Enter Student Major: ";
    getline(cin, str);
    cin.clear();
    major = str;
    cout << "Enter Student GPA: ";
    while (GPA <= 0 || GPA >= 5.0)
    {
        getline(cin, str);
        cin.clear();
        GPA = StringToDouble(str);
        if (GPA <= 0.0 || GPA >= 5.0)
        {
            cout << "GPA MUST be between 0.0 and 5.0\n";
            cout << "Enter Student GPA: ";
        }
    }
    
    cout << ADV_ID;
    advisorID = EnterID();
    cin.clear();
    while (!(facultyTree.contains(advisorID)))
    {
        cout << "Faculty member " << advisorID << DNE
        << "Enter a valid advisor ID.\nValid Faculty Members Listed: \n";
        facultyTree.printTree();
        advisorID = EnterID();
        cin.clear();
    }
    cin.clear();
    
    if (facultyTree.contains(advisorID))
    {
        // if the faculty member List has the student
                // and student tree doesnt contain the student and not a dup
        if (facultyTree.get(advisorID).ContainsStudent(ID)
            && !studentTree.contains(ID)
            && !(facultyTree.get(advisorID).
                 getStudentIDList().findDuplicateData(ID) > 0))
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
        // Faculty member exists and studentTree does not contain ID and there is no duplicate
        else if (!facultyTree.get(advisorID).ContainsStudent(ID)
                 && !studentTree.contains(ID)
                 && !(facultyTree.get(advisorID).
                      getStudentIDList().findDuplicateData(ID) > 0))
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
        // -1 = NONE, 0 means one student, 1 means duplicate
        // advisor has dup but student ID OK
        else if (
                 facultyTree.get(advisorID).getStudentIDList().
                 findDuplicateData(ID) > 0 && !studentTree.contains(ID))
        {
            cout << "Duplicate ID For Advisor - Enter new ID for "
                << name << " \n";
            cout << "NON-valid IDs to assign: \n";
            facultyTree.get(advisorID).getStudentIDList().printList();
            while (facultyTree.get(advisorID).
                   getStudentIDList().findDuplicateData(ID) > 0
                   && !studentTree.contains(ID))
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
        else if (!(facultyTree.get(advisorID).
                   getStudentIDList().findDuplicateData(ID) > 0)
                 && studentTree.contains(ID)) // duplicate for studentTree
        {
            cout << "Duplicate Student Tree ID - Enter new ID for "
                << name << " \n";
            facultyTree.get(advisorID).getStudentIDList().printList();
            
            while (facultyTree.get(advisorID).
                   getStudentIDList().findDuplicateData(ID) > 0
                   && !studentTree.contains(ID))
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
            cout << "Faculty member " << advisorID
                    << DNE
                    << "Enter a valid advisor ID.\n"
                        " Valid Faculty Members Listed: \n";
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
    delete stud;
}

//=============================================
//=============================================
//8. Delete a student given the id
void StudentAndFacultyTrees::DeleteStudent(int IDnum)
{
    // find and remove student from faculty list IF advisor exists
    if (!facultyTree.isEmpty() && studentTree.contains(IDnum))
    {
        // get the max ID and then check all ID's less than max ID
        for (int i(facultyTree.getMax()->key.getID()); i >= 0;--i)
        {
            // if the faculty member exists
            if (facultyTree.contains(i))
            {
                // if that faculty member has the student ID
                if (facultyTree.get(i).ContainsStudent(IDnum))
                {
                    // SAVE
                    //currUndo.SaveState(studentTree, facultyTree);
                    
                    // copy the member
                    Faculty *temp = new Faculty(facultyTree.get(i));
                    // remove the student from the member
                    temp->RemoveStudent(IDnum);
                    // delete the faculty member
                    facultyTree.deleter(temp->getID());
                    // insert the updated faculty member
                    facultyTree.insert(*temp);
                    // found exit loop
                    break;
                }
            }
            
        }
    }
    if (studentTree.contains(IDnum))
        studentTree.deleter(IDnum);
}

//=============================================
//=============================================
//9. Add a new faculty member
void StudentAndFacultyTrees::AddFacultyMember()
{
    string name, occupation, department;
    int ID;
    
    // Full Constructor Student(string name, int ID, string level,
    //                          string major, int advisorID, double GPA)
    string str;
    cout << ADV_ID;
    ID = EnterID();
    cin.clear();
    while (facultyTree.contains(ID))
    {
        cout << "Faculty member " << ID
                << " already exists.\nEnter a valid advisor ID.\n"
                   "Invalid Faculty Members Listed: \n";
        facultyTree.printTree();
        ID = EnterID();
        cin.clear();
    }
    // SAVE - Faculty ID is open
    currUndo.SaveState(studentTree, facultyTree);
    cout << "Enter Advisor Name: ";
    getline(cin, str);
    cin.clear();
    name = str;
    cout << "Enter Advisor Occupation: ";
    getline(cin, str);
    cin.clear();
    occupation = str;
    cout << "Enter Advisor Department: ";
    getline(cin, str);
    cin.clear();
    department = str;
    
    if (!facultyTree.contains(ID))
    {
        // SAVE
        Faculty *temp = new Faculty(name, ID, occupation, department);

        currUndo.SaveState(studentTree, facultyTree);
        
        facultyTree.insert(*temp);
    }
    else
    {
        cout << "ID already exists in database\n";
    }
}
//=============================================
//=============================================
//10. Delete a faculty member given the id.
void StudentAndFacultyTrees::DeleteFacultyMember(int IDnum)
{
    
    // check existence
    if (facultyTree.contains(IDnum))
    {
        // Find if any student dependencies
        int replaceAdvisorID = -1000;
        if (facultyTree.get(IDnum).getStudentIDList().getSize() > 0)
        {
            // get confirmation
            cout << "This operation will affect students.\n";
            
            while (replaceAdvisorID != -1)
            {
                cout << "Replacement AdvisorID...\n";
                replaceAdvisorID = EnterIDOrAbort();
                
                if (replaceAdvisorID >= 1)
                {
                    if (facultyTree.contains(replaceAdvisorID))
                    {
                        break;
                    }
                }
            }
            // a teacher has been chosen or the operation aborted
            if(replaceAdvisorID != -1)
            {
                DoublyLinkedList<int>* studIDs =
                new DoublyLinkedList<int>(facultyTree.get(IDnum).
                                          getStudentIDList());
                int DLLsize;
                DLLsize = studIDs->getSize() - 1;
                while (DLLsize != -1)
                {
                    //return the data in the position in the DLL
                    int ID = studIDs->getDataAtPosition(DLLsize);
                    // THIS OPERATION WILL SAVE
                    ChangeStudentAdvisor(ID, replaceAdvisorID);
                    --DLLsize;
                }
                delete studIDs;
                
            }
        }
        if (replaceAdvisorID != -1)
        {
            // SAVE
            //currUndo.SaveState(studentTree, facultyTree);
            facultyTree.deleter(IDnum);
        }
    }
    else
        cout << "Faculty member does not exist...\n";
}
//=============================================
//=============================================
//11. Change a student’s advisor given the student id and the new faculty id.
void StudentAndFacultyTrees::ChangeStudentAdvisor(int StudentID, int FacultyID)
{
    
    if (studentTree.contains(StudentID) && facultyTree.contains(FacultyID) &&
        !facultyTree.get(FacultyID).ContainsStudent(StudentID))
    {
        
        // get previous advisors ID
        int studPrevAdvisorID = studentTree.get(StudentID).getAdvisorID();
        // REMOVE PREV
        if (facultyTree.contains(studPrevAdvisorID)
            && studPrevAdvisorID != FacultyID)
        {
            
            // create a temp copy
            Faculty* updated = new Faculty(facultyTree.get(studPrevAdvisorID));
            updated->RemoveStudent(StudentID);
            
            // remove from tree
            facultyTree.deleter(studPrevAdvisorID);
            // insert the updated member
            facultyTree.insert(*updated);
            delete updated;
        }
        // if the faculty member doesnt have the associated student already
        if (!facultyTree.get(FacultyID).ContainsStudent(StudentID))
        {
            // create an advisor copy
            Faculty* updatedNext = new Faculty(facultyTree.get(FacultyID));
            // update advisors list
            updatedNext->AddStudent(StudentID);
            // remove advisor from list
            facultyTree.deleter(FacultyID);
            // insert new faculty member
            facultyTree.insert(*updatedNext);
            // updated next will be cleaned by tree
            Student* updatedStudent = new Student(studentTree.get(StudentID));
            updatedStudent->setAdvisor(FacultyID);
            studentTree.deleter(StudentID);
            studentTree.insert(*updatedStudent);
        }
        // else the student already exists in that list
    }
}
//=============================================
//=============================================
//12. Remove an advisee from a faculty member given the ids
void StudentAndFacultyTrees::RemoveStudentFromFacultyRef(int StudentID, int FacultyID)
{
    if (studentInFacultyList(StudentID, FacultyID))
    {
        currUndo.SaveState(studentTree, facultyTree);
        cout << "Removing Student ID: " << StudentID
                << " from faculty member ID: " << FacultyID << "\n";
        // copy the member
        Faculty *temp = new Faculty(facultyTree.get(FacultyID));
        // remove the student from the member
        temp->RemoveStudent(StudentID);
        // delete the faculty member
        facultyTree.deleter(temp->getID());
        // insert the updated faculty member
        facultyTree.insert(*temp);
        delete temp;
        
        Student *tempStud = new Student(studentTree.get(StudentID));
        tempStud->setAdvisor(-1);
        studentTree.deleter(StudentID);
        studentTree.insert(*tempStud);
    }
    else
    {
        cout << "Student ID or Faculty Member not found\n";
    }
}
//=============================================
//=============================================
//13. Rollback
void StudentAndFacultyTrees::RollBack()
{
    cout << "Rolling Back...\n";
    cout << "Restored Trees:\n";
    // SOME FUNCTIONS create multiple saves
    // roll back as needed to get to desired position
    if (currUndo.CanUndo())
    {
        facultyTree.EraseTree();
        facultyTree = currUndo.GetLastFacultyTree();
        facultyTree.printTree();
        studentTree.EraseTree();
        studentTree = currUndo.GetLastStudentTree();
        studentTree.printTree();
        currUndo.removeLastState();
        
    }
}
//=============================================
//=============================================
//14. Exit - save data to file
void StudentAndFacultyTrees::Exit()
{
    cout << OPENING_OUT << FACULTY_FILE << "\n";
    
    std::ofstream outputFac(FACULTY_FILE, std::ios::out);
    if(!outputFac.is_open())
    {
        throw Error(ERROR_OUTFILE);
    }
    else if(outputFac.is_open())
    {
        outputFac << facultyTree.TreeToString();
        outputFac.close();
        cout << SAVED;
    }
    // OVERWRITE OLD FILE WITH NEW
    cout << OPENING_OUT << STUDENT_FILE << "\n";
    
    std::ofstream outputStud(STUDENT_FILE, std::ios::out);
    if(!outputStud.is_open())
    {
        throw Error(ERROR_OUTFILE);
    }
    else if(outputStud.is_open())
    {
        outputStud << studentTree.TreeToString();
        outputStud.close();
        cout << SAVED;
    }
}


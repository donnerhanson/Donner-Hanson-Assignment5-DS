//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : RunBSTProgram.cpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Run the program
//================================================================


#include "RunBSTProgram.hpp"
void RunBSTProgram::Run()
{
    StudentAndFacultyTrees *sft = new StudentAndFacultyTrees();
    sft->FillAdvisorsFromFile();
    sft->FillStudentsFromFile();
    
    
    // Get user input for program changes
    sft->ChooseFunction();
    
    delete sft;
    
}

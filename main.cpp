//================================================================
// Author      : Donner Hanson
// Date        : 05/01/2019
// Email       : hanso127@mail.chapman.edu
// Course      : Data Structures and Algorithms
// Course #    : CPSC-350-2
// Project Name: Student Faculty Database
// File Name   : main.cpp
// Assignment  : Assignment 5
// Version     : 0.0
// Instructor  : Rene German
// Description : Insert faculty and students and link and unlink
//               and have the ability to undo operations that change
//               state of the program
//================================================================

#include <iostream>

#include "Error.h"
#include "RunBSTProgram.hpp"

using std::cout;

int main(int argc, const char * argv[]) {
    try{
    RunBSTProgram theProgram;
    theProgram.Run();
    }
    catch(Error &e)
    {
        return EXIT_FAILURE;
    }
    catch(...)
    {
        cout << "Something unexpected occurred...\n";
        return 2;
    }
    return 0;
    
}

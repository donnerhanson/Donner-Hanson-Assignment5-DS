//
//  main.cpp
//  Assignment_5_DS
//
//  Created by Donner Hanson on 4/22/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

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

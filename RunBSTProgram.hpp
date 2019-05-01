//
//  RunBSTProgram.hpp
//  Assignment_5_DS
//
//  Created by Donner Hanson on 4/22/19.
//  Copyright © 2019 Donner Hanson. All rights reserved.
//

#ifndef RunBSTProgram_hpp
#define RunBSTProgram_hpp

#include "StudentAndFacultyTrees.hpp"

class RunBSTProgram
{
public:
    RunBSTProgram(){;}
    // if no files exist
    void Run()
    {
        StudentAndFacultyTrees *sft = new StudentAndFacultyTrees();
        sft->FillAdvisorsFromFile();
        sft->FillStudentsFromFile();
        
        
        // Get user input for program changes
        sft->ChooseFunction();
        
        delete sft;
        
    }

private:
    
    
};


#endif /* RunBSTProgram_hpp */

// Hadasim_LearnFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "LearnTheFile.h"
int main()
{
    std::cout <<
        "PLEASE ENTER NAME FILE WITH SUFFIX: ";
    std::string name_of_thefile = "";
    std::cin >> name_of_thefile;
   
    LearnTheFile ltf(name_of_thefile, "out_file.txt");

    ltf.PrintAllWords();
    
    std::cout << "\n\n=============\t=========\nCHECK YOUR BROWSER FOR FILE NAMED:  \"out_file.txt\"\n=============\t=========\n\n";
    std::cout << "\n\n=============\t=========\nplease...\nIF YOUR NOT GLAD FROM THE EXCLUSIVE WORDS JUST INSERT MORE WORDS IN LearnTheFile.h StringsArray\n=============\t=========\n\n";
    
    
    ltf.makeFileRequests();
    return 0;
}


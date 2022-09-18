/* 
 * main.cpp
 * This file is what the user will mainly interact with, and checks for 
 * misproper use of command line arguments and checks if the input file is bad.
 * by Rodrigo Campos, April 18th 2021
 */
#include <iostream>
#include "6degs.h"
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
    //check for imprroper command line
    if (argc != 2 and argc != 3 and argc != 4) { 
        cerr << "Usage: ./6degs dataFile [commandFile] [outputFile]\n";
        exit(EXIT_FAILURE);
    }
    
    if (argc == 3 or argc == 4) { //check to use input files.
        ifstream inputFile(argv[2]);
        if (inputFile.fail()) {
            cerr << argv[2] << " cannot be opened." << endl;
            exit(EXIT_FAILURE);
        }
        
        if (argc == 3) { //check if we use cout or outputfile UwU
            6degs six(argv[1]);
            six.play(inputFile, cout);
            
        } else {
            ofstream outputFile(argv[3]);
            6degs six(argv[1]);
            six.play(inputFile, outputFile);
        }
        inputFile.close();
        
    } else {
        6degs six(argv[1]);
        six.play(cin, cout);
    }
    return 0;
}
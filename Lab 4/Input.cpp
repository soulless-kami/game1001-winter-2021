#include <iostream> 
#include <fstream>
#include "Header.h"

using namespace std;

int main()
{
    ofstream OutputFile;

    OutputFile.open(" Haiku.txt ");


    OutputFile << (" Change always happens\n");
    OutputFile << (" Adapting is what follows\n");
    OutputFile << (" Acceptance is last.") << endl;


    OutputFile.close();

    write();

    return 0;
}

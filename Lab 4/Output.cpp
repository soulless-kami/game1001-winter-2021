#include <iostream> 
#include <string>
#include <fstream>
#include "Header.h"
using namespace std;

void write()
{

    ifstream OutputFile(" Haiku.txt ");
    string HaikuText;

    while (getline(OutputFile, HaikuText)) {

        cout << HaikuText << "\n";
    }

    OutputFile.close();

}

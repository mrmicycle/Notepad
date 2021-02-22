#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include "Node.h"
#include "Notepad.h"
using namespace std;

int main()
{
    // There is a file "myfile.txt" included with the program if you would like to load it!

    Notepad np;// create notepad object

    np.Title();

    np.run(); // run the program

    np.cleanPoint(); // delete nodes after program exits
    
    cout << "\nFarewell..." << endl;

    return 0;
}
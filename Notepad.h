#pragma once
#include <string>
#include "Node.h"
using namespace std;

class Notepad
{
public:
    short x, y;// coordinates on the screen. Controls the cursor, works alongside curr.
    int rowNum;
    int rowMax;
    int rowCount;// this is SEPARATE from row num, will keep a running total of rows IN USE.
    char c;// for taking inputs
    char save;// for saving to same file or another file
    Node* start;
    Node* end;
    Node* curr;// for inserting new nodes in custom positions
    Node* row[10];
    string filename;
    Notepad();
    void setFileName(string);
    void readf();
    void savef();
    void cleanPoint();
    void run();
    void gotoxy(short, short);
    void ShowConsoleCursor(bool);
    void Title();
    void Menu();
};
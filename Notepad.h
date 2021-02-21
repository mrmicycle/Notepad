#pragma once
#include <string>
#include "Node.h"
using namespace std;

class Notepad
{
public:
    int x, y;//coordinates on the screen. Controls the cursor, works alongside curr.
    int rowNum;
    int rowMax;
    int rowCount;// this is SEPARATE from row num, will keep a running total of rows IN USE.
    char c;//for taking inputs
    Node* start;
    Node* end;
    Node* curr;//for inserting new nodes in custom positions
    Node* row[10];
    string filename;
    Notepad();
    void setchar(char);
    void readf();
    void savef();
};
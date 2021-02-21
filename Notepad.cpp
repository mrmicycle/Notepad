#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include "Notepad.h"

Notepad::Notepad()
{
    short x, y;//coordinates on the screen. Controls the cursor, works alongside curr.
    Node* start = nullptr;
    Node* end = nullptr;
    Node* curr = nullptr;//for inserting new nodes in custom positions
    Node* row[10];
    // clean the row array to make it all nullptr
    for (int i = 0; i < 10; i++) {
        row[i] = nullptr;
    }
    char c;
    string filename;
    int rowNum = 0;
    int rowMax = 9;
    int rowCount = 0;// this is SEPARATE from row num, will keep a running total of rows IN USE.
    x = y = 0;
}

void Notepad::setchar(char c)
{
    c = _getch();
}

void Notepad::readf()
{
    //cout << "what is the name of your file?" << endl;
                //getline(cin, filename);
    ifstream openfile("myfile.txt");
    while (openfile >> noskipws >> c) {//read each character from file without skipping whitespaces
        //cout << c;
        //convert each character to a linked list
        if (c == '\n')//newline, specific to reading from file
        {
            // end row
            start = end = curr = nullptr;
            rowNum++;
            rowCount++;
            y++;
            x = 0;
        }
        else if (start == nullptr)//first character
        {
            Node* p = new Node(c);
            row[rowNum] = new Node(NULL);
            start = p;
            end = start;
            curr = end;
            x++;
            row[rowNum]->next = start;
            start->prev = row[rowNum];
        }
        else if (curr == end)//adding new characters at the end of the linked list (row?)
        {
            Node* p = new Node(c);
            end->next = p;
            p->prev = end;
            end = p;
            curr = end;
            x++;
        }
        else if (curr == NULL || curr->letter == '\0')//allow new character at beginning, BEFORE start. CURRENT CAN'T BE NULL HERE
        {
            // need to edit
            // make new p curr
            // make new p start
            Node* p = new Node(c);
            p->next = start;
            start->prev = p;
            p->prev = curr;//point new node to current row
            curr->next = p;// make row point to new node
            start = p;
            curr = p;
            x++;
        }
        else if ((curr->next != nullptr && curr->prev != nullptr) || curr == start)//is there anything to the left and right? (insert)
        {
            Node* p = new Node(c);//create new, Need to change 4 pointers.
            p->next = curr->next;// make new node point to the current next node
            curr->next->prev = p;// make the current next node point BACK to the new node p
            p->prev = curr;//make p point back to the current
            curr->next = p;//make the current point to p
            curr = p;//finally, make the new node the current node
            x++;
        }
    }
    openfile.close();
}

void Notepad::savef()
{
    ofstream savefile("myfile.txt");

    for (int i = 0; i < rowNum; i++)//only go up to rownum, otherwise will save with whitespace
    {
        if (row[i] != nullptr)
        {
            Node* T;
            T = row[i]->next;
            while (T != nullptr)
            {

                savefile << T->letter;
                T = T->next;
            }
        }
        savefile << endl;//need to actually print out on the next line, this isn't controlled by goto
    }

    savefile.close();
}

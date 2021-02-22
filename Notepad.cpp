#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include "Notepad.h"
#include "Node.h"
using namespace std;



Notepad::Notepad() // Notepad constructor.
{
    start = nullptr;
    end = nullptr;
    curr = nullptr;//for inserting new nodes in custom positions
    filename = "";
    rowNum = 0;
    rowMax = 9;
    rowCount = 0;// this is SEPARATE from row num, will keep a running total of rows IN USE.
    x = y = 0;// may need to change for borders

    // clean the row array to make it all nullptr
    for (int i = 0; i < 10; i++) {
        row[i] = nullptr;
    }
}

void Notepad::gotoxy(short hori, short vert)//used for placing cursor in proper location.
{
    COORD pos = { hori, vert };

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(output, pos);
}

void Notepad::setFileName(string name)
{
    filename = name;
}

void Notepad::ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;//this line toggles cursor visibility with showflag boolean
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Notepad::Title()
{
    gotoxy(50, 7);
    cout << "Welcome to" << endl;
    gotoxy(19, 10);
    cout << "##       #### ##    ## ##    ##         ##    ##    ##  #######  ######## ######## " << endl;
    gotoxy(19, 11);
    cout << "##        ##  ###   ## ##   ##           ##   ###   ## ##     ##    ##    ##       " << endl;
    gotoxy(19, 12);
    cout << "##        ##  ####  ## ##  ##             ##  ####  ## ##     ##    ##    ##       " << endl;
    gotoxy(19, 13);
    cout << "##        ##  ## ## ## #####    #######    ## ## ## ## ##     ##    ##    ######   " << endl;
    gotoxy(19, 14);
    cout << "##        ##  ##  #### ##  ##             ##  ##  #### ##     ##    ##    ##       " << endl;
    gotoxy(19, 15);
    cout << "##        ##  ##   ### ##   ##           ##   ##   ### ##     ##    ##    ##       " << endl;
    gotoxy(19, 16);
    cout << "######## #### ##    ## ##    ##         ##    ##    ##  #######     ##    ######## " << endl;
    gotoxy(25, 20);
    cout << "Press any key to start typing! Or open a file by pressing F1";
}

void Notepad::Menu()
{
    //display menu at the bottom of the screen, always
    //use y=27 or 28 to make a vim men
    gotoxy(0, 28);
    cout << "F1: Open File | F2: Save | Esc: exit" << endl;
}

void Notepad::readf()
{
    // possible asking for name of file
    // cout << "what is the name of your file?" << endl;
    // getline(cin, filename);
    ifstream openfile("myfile.txt");

    while (openfile >> noskipws >> c) {// read each character from file without skipping whitespaces
        // convert each character to a linked list
        if (c == '\n')// newline, specific to reading from file.
        {
            start = end = curr = nullptr;// back to beginning of row
            rowNum++;
            rowCount++;
            y++;
            x = 0;// cursor back to the beginning of the row
        }
        else if (start == nullptr)// First character in a row
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
        else if (curr == end)// adding new characters at the end of the linked list/ row
        {
            Node* p = new Node(c);
            end->next = p;
            p->prev = end;
            end = p;
            curr = end;
            x++;
        }
        else if (/*curr == NULL || */curr->letter == '\0')// allow new character at beginning, BEFORE start. NULL necessary?
        {
            // need to edit
            // make new p curr
            // make new p start
            Node* p = new Node(c);
            p->next = start;
            start->prev = p;
            p->prev = curr;// point new node to current row
            curr->next = p;// make row point to new node
            start = p;
            curr = p;
            x++;
        }
        else if ((curr->next != nullptr && curr->prev != nullptr) || curr == start)// is there anything to the left and right? (insert)
        {
            Node* p = new Node(c);// create new, Need to change 4 pointers.
            p->next = curr->next;// make new node point to the current next node
            curr->next->prev = p;// make the current next node point BACK to the new node p
            p->prev = curr;// make p point back to the current
            curr->next = p;// make the current point to p
            curr = p;// finally, make the new node the current node
            x++;
        }
    }
    openfile.close();
}

void Notepad::savef()
{
    // possible asking for name of file
    // cout << "what is the name of your file?" << endl;
    // getline(cin, filename);
    ofstream savefile("myfile.txt");

    for (int i = 0; i <= rowNum; i++)// only go up to rownum, otherwise will save with whitespace
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
        savefile << endl;// need to actually print out on the next line, this isn't controlled by goto
    }

    savefile.close();
    
    
}

void Notepad::run()
{
    Menu();//make sure the menu shows as soon as you enter the text editor
    gotoxy(0, 0);
    while (1)// loop will prob stay in main as well
    {
        c = _getch();
        // cout << c; get rid of alphas
        if (c == 27) // escape loop
        {
            break;
        }
        else if (c == 0)// special for F keys
        {
            c = _getch();
            if (c == 59)// f1 read file
            {
                readf();

            }
            if (c == 60)// f2 save to file
            {
                savef();
            }
        }
        else if (c == 13)// enter
        {
            if (rowNum > 8)
            {
                // do nothing!
            }
            else
            {
                rowNum++;
                start = end = nullptr;
                row[rowNum] = new Node();// create new row when you press enter
                curr = row[rowNum];
                x = 0;// in a new row, go all the way left
                y++;// and you go down one!
                rowCount++;
            }


        }
        else if (c == 8) // backspace
        {
            if (curr == nullptr || curr->letter == '\0')
            {
                // do nothing
            }

            else if (curr == start)// delete something located at "start" but its not the beginning of the linked list **PROBLEM HERE**
            // CURRENT DOES NOT END UP WHERE I THINK IT DOES
            {
                Node* del = curr;// mark curr? for deletion IS THIS NECESSARY????
                curr->prev = row[rowNum];// point current to row pointer
                curr->prev->next = curr->next;// point row pointer to after after current
                if (start->next != nullptr)// non-empty row
                {
                    start = start->next;// only move start to next node if there is more in the list
                    start->prev = row[rowNum];// doesn't hurt
                }
                else
                {
                    curr->next = nullptr;// row is empty after deleting, make it point to nullptr
                    start = nullptr;
                    end = nullptr;
                }
                curr = row[rowNum];// curr becomes row pointer, outside of the linked list
                x--;

            }
            else if (curr->next != nullptr && curr->prev != nullptr)// deleting something in the middle 
            {
                Node* del = new Node();
                del = curr;// marking curr for deletion
                curr->prev->next = curr->next;// connect previous to next
                curr->next->prev = curr->prev;// connect next to prev
                curr = curr->prev;
                delete(del);
                x--;
            }
            else// delete something at the end
            {
                end = end->prev;
                curr = curr->prev;
                delete(end->next);
                end->next = nullptr;
                x--;
            }

        }
        else if (c == -32)// arrow keys
        {
            c = _getch();
            if (c == 75)// left key
            {
                if (curr == NULL || start == nullptr || curr->letter == '\0')// null terminator means i'm currently in the row pointer.
                {
                    // do nothing!
                }
                else// I am missing another "filter" so to speak
                {
                    // this is all i need, since if i go left enough eventually curr will point to row pointer.
                    curr = curr->prev;
                    x--;
                }

            }
            if (c == 77)// right key
            {
                if (start == nullptr || curr == end)// we're at the start and there's nothing to go right to or at end of linked list
                {
                    // do nothing!
                }

                else if (curr == NULL)// curr is technically in start->prev, allows you to move back into linked list
                {
                    curr = start;
                    x++;
                }
                else if (curr->next != NULL)// curr==NULL by itself makes cursor go right endlessly
                {
                    curr = curr->next;
                    x++;
                }
                else
                {
                    curr = curr->next;
                    x++;
                }

            }
            if (c == 72)// up
            {
                // when going up cycle through the linked list up there starting with 
                if (rowNum == 0) // the only time you cannot go up is when you are in the first row. 
                {
                    // do nothing!
                }
                else
                {                    
                    y--;
                    rowNum--;
                    curr = row[rowNum];// this puts it at the start of the previous row
                    if (curr->next == nullptr)// empty row
                    {
                        start = end = nullptr;
                        x = 0;// puts cursor back at the start of the row since it is empty
                    }
                    else
                    {
                        if (curr->next != nullptr)
                            start = curr->next;// change start to first letter in row if that letter exists
                        // use check pointer to cycle through row and find where it ends
                        Node* check = start;
                        while (check->next != nullptr)
                            check = check->next;
                        end = check;// then set end to check
                        end->next = nullptr;// make sure that end is not pointing forward to anything just in case
                        // delete(check);


                        // move the cursor to the end of the current row.
                        for (int i = 0; i < x; i++)
                        {
                            if (curr == end)
                            {
                                x = i;// for cases where the row above has less characters
                                break;
                            }
                            else if (curr->next == nullptr)
                            {
                                break;// break loop when curr reaches end of row.
                            }
                            else
                            {
                                curr = curr->next;
                            }
                        }
                    }
                }
            }
            if (c == 80)// down
            {
                if (y == rowMax || rowNum == rowCount)
                {
                    // do nothing!
                }
                else
                {
                    y++;
                    rowNum++;
                    // arrows do not change rowCount
                    curr = row[rowNum];// pur curr at before start of next row
                    if (curr->next == nullptr)// if row is empty
                    {
                        start = end = nullptr;
                        x = 0;// puts cursor back at the start of the row since it is empty
                    }
                    else
                    {
                        if (curr->next != nullptr)
                            start = curr->next;// change start to first letter in row only if that letter exists
                        // use check pointer to cycle through row and find where it ends
                        Node* check = start;
                        while (check->next != nullptr)
                            check = check->next;
                        end = check;
                        end->next = nullptr;// make sure that end is not pointing to anything afterward just in case.

                        // now, move the cursor to the end of the current row.
                        for (int i = 0; i < x; i++)
                        {
                            if (curr == end)
                            {
                                x = i;// for cases where the row below has less characters
                                break;
                            }
                            else if (curr->next == nullptr)
                            {
                                break;// break loop when curr reaches end of row.
                            }
                            else
                            {
                                curr = curr->next;// move to next character in the row.
                            }
                        }
                    }
                }
            }
        }
        else // normal characters
        {
            if (start == nullptr)// first character in a given row
            {
                Node* p = new Node(c);
                if (row[rowNum] == nullptr)// has the user pressed enter for this row
                    row[rowNum] = new Node();// if they have not, add a pointer to row array
                row[rowNum]->next = p;
                p->prev = row[rowNum];
                x++;
                start = p;
                end = p;
                curr = p;
            }

            else if (curr == end)// adding new characters at the end of the linked list (row?)
            {
                Node* p = new Node(c);
                end->next = p;
                p->prev = end;
                end = p;
                curr = end;
                x++;
            }
            else if (curr == NULL || curr->letter == '\0')// allow new character at beginning (current can't be null here?)
            {
                // need to edit
                // make new p curr
                // make new p start
                Node* p = new Node(c);
                if (curr->next != nullptr)// if row is not empty
                {
                    p->next = start;// set new node next to start
                    start->prev = p;
                }
                p->prev = curr;// point new node to current row
                curr->next = p;// make row point to new node
                start = p;
                curr = p;
                x++;
            }
            else if (curr == start)
            {
                Node* p = new Node(c);
                p->next = curr->next;
                p->prev = curr;
                if (curr->next != nullptr)// if next node is not null
                    curr->next->prev = p;// make the current next node point BACK to the new node p
                curr->next = p;
                curr = p;
                x++;
            }
            else if (curr->next != nullptr && curr->prev != nullptr)// is there anything to the left and right? (insert)
            {
                Node* p = new Node(c);// create new, Need to change 4 pointers.
                p->next = curr->next;// make new node point to the current next node
                curr->next->prev = p;// make the current next node point BACK to the new node p
                p->prev = curr;// make p point back to the current
                curr->next = p;// make the current point to p
                curr = p;// finally, make the new node the current node
                x++;
            }
        }
        system("cls");
        for (int i = 0; i < 10; i++)
        {
            if (row[i] != nullptr)
            {
                Node* T;
                T = row[i]->next;// get first letter of row;

                while (T != nullptr)
                {

                    cout << T->letter;
                    T = T->next;
                }
            }
            cout << endl;// need to actually print out on the next line, this isn't controlled by goto
        }
        Menu();
        gotoxy(x, y);


    }
}

void Notepad::cleanPoint()
{
    cout << "\n deleting nodes";
    // garbage collection, freeing pointers?
    // need to free pointers in ROW ARRAY
    Node* T;
    for (int i = 0; i < 10; i++)
    {
        T = row[i];// could throw errors on empty rows :(
        while (T != nullptr)
        {
            if (T->next == nullptr)//reached end
            {
                delete(T);//delete current, will delete row pointer if the row is empty
                break;
            }
            T = T->next;
            delete(T->prev);//will also take care of deleting row pointers
        }
    }
}
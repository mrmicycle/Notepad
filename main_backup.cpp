#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>
#include "Node.h"

//#include <stdafx.h>
using namespace std;

void gotoxy(short, short);
//void ShowConsoleCursor(bool showFlag)
//{
//    HANDLE out = GetStdHandle()
//}

int main()
{
    /*while (1)
    {
        c = _getch();
        cout << (int)c << endl;
    }*/

    
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
    cout << "Start typing!" << endl;//stays in main

    
    


    while (1)// loop will prob stay in main as well
    {
        c = _getch();
        //cout << c; get rid of alphas
        if (c == 27) // escape loop
        {
            break;
        }
        else if (c == 0)//special for F keys
        {
            c = _getch();
            if (c == 59)//f1 open file
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
            if (c == 60)//f2 write to file
            {
                ofstream savefile("myfile.txt");

                for (int i = 0; i <= rowNum; i++)//only go up to rownum, otherwise will save with whitespace
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
        }
        else if (c == 13)//enter
        {
            if (rowNum > 8)
            {
                //do nothing!
            }
            else
            {
                rowNum++;
                start = end = nullptr;
                row[rowNum] = new Node();//create new row when you press enter
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
            
            else if (curr == start)//delete something located at "start" but its not the beginning of the linked list **PROBLEM HERE**
            // CURRENT DOES NOT END UP WHERE I THINK IT DOES
            {
                Node* del = curr;// mark curr? for deletion IS THIS NECESSARY????
                curr->prev = row[rowNum];// point current to row pointer
                curr->prev->next = curr->next;//point row pointer to after after current
                if (start->next != nullptr)//non-empty row
                {
                    start = start->next;// only move start to next node if there is more in the list
                    start->prev = row[rowNum];// doesn't hurt
                }    
                else 
                {
                    curr->next = nullptr;//row is empty after deleting, make it point to nullptr
                    start = nullptr;
                    end = nullptr;
                }
                curr = row[rowNum];// curr becomes row pointer, outside of the linked list
                
                /*if (start != nullptr)
                    start->prev = nullptr;*/
                //delete (del);//delete the node
                //delete(start->prev);
                //start->prev = nullptr;
                x--;

            }
            else if (curr->next != nullptr && curr->prev != nullptr)//deleting something in the middle 
            {
                Node* del = new Node();
                del = curr;//marking curr for deletion
                curr->prev->next = curr->next;//connect previous to next
                curr->next->prev = curr->prev;//connect next to prev
                curr = curr->prev;
                delete(del);
                x--;
            }
            else//delete something at the end
            {
                end = end->prev;
                curr = curr->prev;
                delete(end->next);
                end->next = nullptr;
                x--;
            }
            
        }
        else if (c == -32)
        {
            c = _getch();
            if (c == 75)//left key
            {
                if (curr == NULL || start == nullptr || curr->letter == '\0')//null terminator means i'm currently in the row pointer.
                {
                    //do nothing!
                }
                else// I am missing another "filter" so to speak
                {
                    //make null under certain condition?
                    curr = curr->prev;
                    x--;
                }
                
            }
            if (c == 77)//right key
            {
                if (start == nullptr || curr == end)//we're at the start and there's nothing to go right to or at end of linked list
                {
                    // do nothing!
                }
                
                else if (curr == NULL)// curr is technically in start->prev, allows you to move back into linked list
                {
                    curr = start;
                    x++;
                }
                else if (curr->next != NULL)//curr==NULL by itself makes cursor go right endlessly
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
                // row[rowNum]. Then go next up until the amount of x?
                if (rowNum == 0) //fix
                {
                    // do nothing!
                }
                //else if ()
                else 
                {
                    /*if (rowNum > 0)
                    {
                        y--;
                        rowNum--;
                        curr
                    }*/
                    y--;
                    rowNum--;
                    curr = row[rowNum];// this puts it at the start of the previous row
                    // use rowNum to determine whether the cursor can move or not
                    if (curr->next == nullptr)//empty row
                    {
                        start = end = nullptr;
                        x = 0;// puts cursor back at the start of the row since it is empty
                        // do nothing with curr or start, because there is nothing in that row 
                        // if curr->letter = '\0' then something was inserted
                        // bc when i add a letter, i create a pointer in that row array
                    }
                    else
                    {
                        if (curr->next != nullptr)
                            start = curr->next;//change start to first letter in row if that letter exists
                        // NEED TO SET END
                        Node* check = start;
                        while (check->next != nullptr)
                            check = check->next;
                        end = check;
                        end->next = nullptr;//not necessary?
                        //delete(check);


                        //set cursor
                        for (int i = 0; i < x; i++)
                        {
                            if (curr == end)
                            {
                                x = i;
                                break;
                            }
                            else if (curr->next == nullptr)
                            {
                                //set end of row, then
                                break;//break loop when curr reaches end of row.
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
                if (y == rowMax || rowNum == rowCount )//fix, might be able to take out rowNum
                {
                    // do nothing!
                }
                else
                {
                    //ARROW KEYS DO NOT CHANGE ROWCOUNT
                    y++;
                    rowNum++;
                    curr = row[rowNum];// this puts it at the start of the next row
                    if (curr->next == nullptr)//if row is empty
                    {
                        start = end = nullptr;
                        x = 0;// puts cursor back at the start of the row since it is empty
                        // do nothing with curr or start, because there is nothing in that row 
                        // if curr->letter = '\0' then something was inserted
                        // bc when i add a letter, i create a pointer in that row array
                    }
                    else
                    {
                        if (curr->next != nullptr)
                            start = curr->next;//change start to first letter in row if that letter exists
                        //if (curr == nullptr && curr == end) 
                        //{
                        //    // similar to presing enter
                        //    // if the row is empty, just move cursor to beginning of the row, set curr to start.
                        //    curr = start;
                        //    x = 0;
                        //}

                        // NEED TO SET END
                        Node* check = start;
                        while (check->next != nullptr)//if i delete a row between two populated rows, going down into it makes it crash
                            check = check->next;
                        end = check;
                        end->next = nullptr;
                        //delete(check);
                        // deleting check will make end disappear

                        //move the cursor to the end of the current row.
                        for (int i = 0; i < x; i++)
                        {
                            if (curr == end)
                            {
                                x = i;
                                break;
                            }
                            else if (curr->next == nullptr)
                            {
                                ;//set end of row, then
                                break;//break loop when curr reaches end of row.
                            }
                            else
                            {
                                curr = curr->next;
                            }

                        }
                        
                    }
                    
                }
            }
        }
        else //normal characters
        {
            if (start == nullptr)//first character in a given row
            {
                Node* p = new Node(c);
                //if statement here
                if (row[rowNum] == nullptr)//has the user pressed enter for this row
                    row[rowNum] = new Node();
                row[rowNum]->next = p;
                p->prev = row[rowNum];
                x++;

                start = p;
                end = p;
                curr = p;
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
            else if (curr == NULL || curr->letter == '\0')//allow new character at beginning CURRENT CAN'T BE NULL HERE
            {
                // need to edit
                // make new p curr
                // make new p start
                Node* p = new Node(c);
                if (curr->next != nullptr)//if row is not empty
                {
                    p->next = start;//set new node next to start
                    start->prev = p;
                }
                p->prev = curr;//point new node to current row
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
            else if (curr->next != nullptr && curr->prev != nullptr)//is there anything to the left and right? (insert)
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
        system("cls");
        for (int i = 0; i < 10; i++)
        {
            if (row[i] != nullptr)
            {
                Node* T;
                T = row[i]->next;//get first letter of row;
                
                while (T != nullptr)
                {
                    
                    cout << T->letter;
                    T = T->next;
                }
            }
            cout << endl;//need to actually print out on the next line, this isn't controlled by goto
        }
        gotoxy(x, y);


    }

    cout << "\n deleting nodes";

    // garbage collection, freeing pointers?
    // need to free pointers in ROW ARRAY
    Node* T;
    T = start;
    while (T != nullptr)
    {
        if (T->next == nullptr)//reached end
        {
            delete(T);//delete current
            break;
        }
        T = T->next;
        delete(T->prev);
    }
    for (int i = 0; i < 10; i++)
    {
        delete(row[i]);
    }
    //delete row;

    //delete start, end;// not everything
    /*cout << "\n checking start and end" << endl;
    cout << start->letter << endl;
    cout << end->letter << endl;*/


    return 0;
}

void gotoxy(short x, short y) {//move to editor??

    COORD pos = { x, y };

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(output, pos);

}
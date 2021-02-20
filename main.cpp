#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include "Node.h"
//#include <stdafx.h>
using namespace std;

void gotoxy(int, int);
//Nodes have a row indicator?
// node is a member with current value
// that passes on to followiing nodes? mebbe too complicated

//void ShowConsoleCursor(bool showFlag)
//{
//    HANDLE out = GetStdHandle()
//}

int main()
{
    int x, y;//coordinates on the screen. Controls the cursor, works alongside curr.
    Node* start = nullptr;
    Node* end = nullptr;
    Node* curr = nullptr;//for inserting new nodes in custom positions
    Node* row[10];
    // clean the row array to make it all nullptr, "clean"
    for (int i = 0; i < 10; i++) {
        row[i] = nullptr;
    }
    char c;
    int rowNum = 0;
    int rowMax = 9;
    int rowCount = 0;// this is SEPARATE from row num, will keep a running total of rows IN USE.


    x = y = 0;
    cout << "Start typing!" << endl;

    /*while (1)
    {
        c = _getch();
        cout << (int)c << endl;
    }*/


    while (1)
    {
        c = _getch();
        //cout << c; get rid of alphas
        if (c == 27) // escape loop
        {
            break;
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
                start = end = curr = nullptr;
                x = 0;// in a new row, go all the way left
                y++;// and you go down one!
                rowCount++;
            }
             
            
        }
        else if (c == 8) // backspace
        {
            if (curr == NULL || curr == nullptr || curr->letter == '\0') 
            {
                // do nothing
            }
            
            else if (curr == start)//delete something located at "start" but its not the beginning of the linked list **PROBLEM HERE**
            // CURRENT DOES NOT END UP WHERE I THINK IT DOES
            {
                Node* del = curr;// mark curr? for deletion
                curr->prev = row[rowNum];
                curr->prev->next = curr->next;
                start = start -> next;// move start to the next node **does this work???***
                curr = row[rowNum];// curr ends up outside of the linked list in this case only
                /*if (start != nullptr)
                    start->prev = nullptr;*/
                delete (del);//delete the node
                //delete(start->prev);
                //start->prev = nullptr;
                x--;

            }
            else if (curr->next != nullptr && curr->prev != nullptr)//deleting something in the middle 
            {
                Node* del = curr;
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
                    // use rowNum to determine whether the cursor can move or not
                    curr = row[rowNum];// this puts it at the start of the previous row
                    start = curr->next;
                    for (int i = 0; i < x ; i++)
                    {
                        if (curr->next == nullptr)
                        {
                            ;//set end of row, then
                            break;//break loop when curr reaches end of row.
                        }
                        else
                        {
                            curr = curr->next;
                        }

                    }
                    // NEED TO SET END
                    Node* check = start;
                    while (check->next != end)
                        check = check->next;
                    end = check;
                    delete(check);
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
                    start = curr->next;
                    //if (curr == nullptr && curr == end) 
                    //{
                    //    // similar to presing enter
                    //    // if the row is empty, just move cursor to beginning of the row, set curr to start.
                    //    curr = start;
                    //    x = 0;
                    //}
                    
                    //move the cursor to the end of the current row.
                    for (int i = 0; i < x+1; i++)
                    {
                        if (curr->next == nullptr)
                        {
                            ;//set end of row, then
                            break;//break loop when curr reaches end of row.
                        }
                        else 
                        {
                            curr = curr->next;
                        }
                            
                    }
                    // NEED TO SET END
                    Node* check = start;
                    while (check->next != end)
                        check = check->next;
                    end = check;
                    delete(check);
                }
            }
        }
        else //normal characters
        {
            if (start == nullptr)//first character
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
            /*if (curr == start) {

            }*/
            else if (curr == end)//adding new characters at the end of the linked list (row?)
            {
                    Node* p = new Node(c);
                    end->next = p;
                    p->prev = end;
                    end = p;
                    curr = end;
                    x++;
            }
            else if (curr == NULL)//allow new character at beginning, BEFORE start.
            {
                // need to edit
                // make new p curr
                // make new p start
                Node* p = new Node(c);
                p->next = start;
                start->prev = p;
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

    //delete start, end;// not everything
    /*cout << "\n checking start and end" << endl;
    cout << start->letter << endl;
    cout << end->letter << endl;*/


    return 0;
}

void gotoxy(int x, int y) {

    COORD pos = { x, y };

    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(output, pos);

}
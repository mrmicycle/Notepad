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
    char c;

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
        if (c == 8) // backspace
        {
            if (curr == NULL || curr == nullptr) 
            {
                // do nothing
            }
            
            else if (curr == start)//delete something located at "start" but its not the beginning of the linked list **PROBLEM HERE**
            // CURRENT DOES NOT END UP WHERE I THINK IT DOES
            {
                Node* del = curr;// mark curr? for deletion
                curr->prev = nullptr;
                start = start -> next;// move start to the next node **does this work???***
                curr = nullptr;// curr ends up outside of the linked list in this case only
                if (start != nullptr)
                    start->prev = nullptr;
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
                if (curr == NULL || start == nullptr)
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
                if (start == nullptr)//we're at the start and there's nothing to go right to
                {
                    // do nothing!
                }
                else if (curr == end)//if at the end of linked list
                {
                    //do nothing!
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
        }
        else //normal characters
        {
            if (start == nullptr)//first character
            {
                Node* p = new Node(c);
                start = p;
                end = start;
                curr = end;
                x++;
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
        Node* T;
        T = start;
        while (T != nullptr)
        {
            cout << T->letter;
            T = T->next;            
        }
        gotoxy(x, y);


    }

    cout << "\n deleting nodes";

    // garbage collection, freeing pointers?
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
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
        cout << c << endl;
    }*/


    while (1)
    {
        c = _getch();
        cout << c;
        if (c == 27) // escape loop
        {
            break;
        }
        if (c == 8) // backspace
        {
            if (curr->prev == nullptr)
            {
                //do nothing!
            }
            else
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
                if (curr->prev == nullptr)
                {
                    //do nothing!
                }
                else
                {
                    //
                    curr = curr->prev;
                    x--;
                }
                
            }
            if (c == 77)//right key
            {
                if (curr->next == nullptr)//if at the end of linked list
                {
                    //do nothing!
                }
                else
                {
                    curr = curr->next;
                    x++;
                }
                
            }
        }
        else 
        {
            if (start == nullptr)
            {
                Node* p = new Node(c);
                start = p;
                end = start;
                curr = end;
                x++;
            }
            else
            {
                if (curr == end)
                {
                    Node* p = new Node(c);
                    end->next = p;
                    p->prev = end;
                    end = p;
                    curr = end;
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
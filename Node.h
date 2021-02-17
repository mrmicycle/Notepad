#pragma once
class Node
{
public:
    char letter;
    Node* next;
    Node* prev;
    Node();
    Node(char);
};
#include "Node.h"

Node::Node() 
{
    next = nullptr;
    prev = nullptr;
    letter = '\0';
}
Node::Node(char c)
{
    next = nullptr;
    prev = nullptr;
    letter = c;
}
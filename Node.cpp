#include "Node.h"

Node::Node() 
{
    next = nullptr;
    prev = nullptr;
}
Node::Node(char c)
{
    next = nullptr;
    prev = nullptr;
    letter = c;
}
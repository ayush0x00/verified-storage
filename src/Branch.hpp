#ifndef BRANCH_NODE_H
#define BRANCH_NODE_H

#include<iostream>
#include<map>
#include "Node.hpp"

class Branch : Node
{
private:
    std::map<std::string, Node::Node*> branches;
    std::string value;
public:
    Branch();
    ~Branch();
};

#endif
#ifndef LEAF_NODE_H
#define LEAF_NODE_H
#include<iostream>
#include "Node.hpp"

class Leaf : Node
{
private:
    std::string path;
    std::string value;

public:
    Leaf(std::string path, std::string value);
    ~Leaf();
};

#endif
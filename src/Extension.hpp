#ifndef EXTENSION_NODE_H
#define EXTENSION_NODE_H

#include <iostream>
#include "Node.hpp"

class Extension : Node
{
private:
    std::string path;
    Node::Node *node;
public:
    Extension(std::string path, Node::Node *node);
    ~Extension();
};

#endif
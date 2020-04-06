#include <iostream>

#include "Node.hpp"
#include "Extension.hpp"

Extension::Extension(std::string path, Node::Node *node)
{
    type = EXTENSION_NODE;
    path = path;
    node = node;   
}

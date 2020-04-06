#include <iostream>

#include "Node.hpp"
#include "Leaf.hpp"

Leaf::Leaf(std::string path, std::string value) {
    type = LEAF_NODE;
    path = path;
    value = value;
}
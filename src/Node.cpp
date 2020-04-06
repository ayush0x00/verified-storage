#include <iostream>

#include "sha256.hpp"
#include "Node.hpp"
#include "NodeType.hpp"

Node::Node() {
    // Create an empty node
    type = BLANK_NODE;
    hash = computeHash("");
}

std::string Node::computeHash(std::string data)
{
    return sha256(data);
}

std::string Node::getHash() {
    return hash;
}

void Node::setHash(std::string data) {
    hash = sha256(data);
}
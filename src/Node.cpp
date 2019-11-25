#include <iostream>
#include "Node.hpp"

Node::Node(std::string hash)
{
    Node::hash = hash;
    Node::parent = NULL;
}

Node *Node::createNode(std::string hash)
{
    Node *node = new Node(hash);
    return node;
}

std::string Node::getHash()
{
    return this->hash;
}

void Node::assignType(std::string type) {
    this->type = type;
}

void Node::assignParent(Node *parent)
{
    this->parent = parent;
}


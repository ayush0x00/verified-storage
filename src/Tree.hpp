#ifndef TREE_H
#define TREE_H

#include <vector>
#include "Node.hpp"

class Tree
{
private:
    Node *root;
    SHA256 sha256;
public:
    Tree();
    std::string computeHash(std::string data);
    Node *create_parent(Node *leftChild, Node *rightChild);
    std::string *buildTree(std::vector<std::string> hashes, bool *mutated);
    void *insert();
    Node *select();
};

#endif
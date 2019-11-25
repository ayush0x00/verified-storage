#ifndef NODE_H
#define NODE_H
#include <iostream>

class Node
{
private:
    std::string type;
    std::string hash;
    Node *parent;

public:
    Node(std::string hash);
    static Node *createNode(std::string hash);
    std::string getHash();
    void assignType(std::string type);
    void assignParent(Node *parent);
};

#endif
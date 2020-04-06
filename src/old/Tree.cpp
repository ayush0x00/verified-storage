#include <iostream>
#include "sha256.hpp"
#include "Node.hpp"
#include "Tree.hpp"

Tree::Tree()
{
    root = NULL;
}

std::string Tree::computeHash(std::string data)
{
    return sha256(data);
}

Node *Tree::create_parent(Node *leftChild, Node *rightChild)
{
    std::string data = leftChild->getHash() + rightChild->getHash();
    Node *parent = Node::createNode(data);
    leftChild->assignParent(parent);
    rightChild->assignParent(parent);

    return parent;
}

std::string *Tree::buildTree(std::vector<std::string> hashes, bool *mutated)
{
    bool mutation = false;
    while (hashes.size() > 1)
    {
        if (mutated)
        {
            for (size_t pos = 0; pos + 1 < hashes.size(); pos += 2)
            {
                if (hashes[pos] == hashes[pos + 1])
                    mutation = true;
            }
        }
        if (hashes.size() & 1)
        {
            hashes.push_back(hashes.back());
        }

        hashes.resize(hashes.size() / 2);
    }
    if (mutated)
    {
        *mutated = mutation;
    }

    if (hashes.size() == 0)
    {
        // TODO: return empty 256 decode
    }

    return hashes[0];
}

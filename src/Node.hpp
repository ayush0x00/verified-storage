#ifndef NODE_H
#define NODE_H

#include "sha256.hpp"
#include "NodeType.hpp"

class Node {
    private:
        std::string hash;
        SHA256 sha256;
    public:
        NodeType type;
        std::string computeHash(std::string data);
        std::string getHash();
        void setHash(std::string data);
};

#endif
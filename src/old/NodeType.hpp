#ifndef NODE_TYPE_H
#define NODE_TYPE_H

#include <iostream>

class Leaf 
{
    private:
        std::string path;
        std::string data;

    public:
        std::string encode();
};

#endif
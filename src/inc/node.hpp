#ifndef PMT_NODE_H
#define PMT_NODE_H

#include <vector>

#include "alias.hpp"

class Node {
    protected:
        Buffer value_;

    public:
        Buffer GetValue();
        void SetValue(Buffer input);
        BufferArray Raw();
        Buffer Serialize();
        Buffer Hash();
};

#endif
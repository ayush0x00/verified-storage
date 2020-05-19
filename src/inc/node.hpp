#ifndef PMT_NODE_H
#define PMT_NODE_H

#include <vector>

#include "alias.hpp"

class Node {
    protected:
        buffer_t value_;

    public:
        buffer_t GetValue();
        void SetValue(buffer_t input);
        bufferarray_t Raw();
        buffer_t Serialize();
        buffer_t Hash();
};

#endif
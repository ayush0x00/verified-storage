#ifndef PMT_FOUND_NODE_H
#define PMT_FOUND_NODE_H


#include <constants/alias.hpp>
#include <storage/utils/aliasadvance.hpp>
#include <storage/nodes/node.hpp>

class FoundNode {
    private:
        buffer_t node_ref_;
        node_t node_;
        nibble_t key_;
};

#endif
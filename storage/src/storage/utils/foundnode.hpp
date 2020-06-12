#ifndef PMT_FOUND_NODE_H
#define PMT_FOUND_NODE_H

// #include <stdint.h>
// #include <string>
// #include <vector>
#include "alias.hpp"
#include "aliasadvance.hpp"
#include "node.hpp"

class FoundNode {
    private:
        buffer_t node_ref_;
        node_t node_;
        nibble_t key_;
};

#endif
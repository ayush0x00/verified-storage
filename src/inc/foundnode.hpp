#ifndef PMT_FOUND_NODE_H
#define PMT_FOUND_NODE_H

#include <stdint.h>
#include <string>
#include <vector>

#include "node.hpp"

class FoundNode {
    private:
        buffer_t node_ref_;
        Node node_;
        nibble_t key_;
};

#endif
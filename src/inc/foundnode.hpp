#ifndef PMT_FOUND_NODE_H
#define PMT_FOUND_NODE_H

#include <stdint.h>
#include <string>
#include <vector>

#include "node.hpp"

class FoundNode {
    private:
        Buffer node_ref_;
        Node node_;
        Nibble key_;
};

#endif
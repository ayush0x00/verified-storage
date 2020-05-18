#ifndef PMT_FOUND_NODE_H
#define PMT_FOUND_NODE_H

#include <stdint.h>
#include <string>
#include <vector>

#include "node.hpp"

class FoundNode {
    private:
        std::vector<uint64_t> node_ref_;
        Node node_;
        std::vector<uint> key_;
        

};

#endif
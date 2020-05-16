#ifndef PMT_NODE_UTILS_H
#define PMT_NODE_UTILS_H

#include "node.hpp"

static Node DecodeNode(const std::vector<uint64_t>& input);
static Node DecodeRawNode(const std::array<std::vector<uint64_t>, 17>& input);
static bool IsRawNode(const std::array<std::vector<uint64_t>, 17>& input);

#endif
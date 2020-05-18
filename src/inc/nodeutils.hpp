#ifndef PMT_NODE_UTILS_H
#define PMT_NODE_UTILS_H

#include <stdint.h>

#include "node.hpp"

static Node DecodeNode(const std::vector<uint64_t> &input);
static Node DecodeRawNode(const std::vector<std::vector<uint64_t>> &input);
static bool IsRawNode(const std::vector<std::vector<uint64_t>> &input);

#endif
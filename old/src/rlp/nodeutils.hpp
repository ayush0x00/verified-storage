#ifndef PMT_NODE_UTILS_H
#define PMT_NODE_UTILS_H

#include "alias.hpp"
#include "aliasadvance.hpp"
#include "node.hpp"


static node_t DecodeNode(const buffer_t &input);

static node_t DecodeRawNode(const bufferarray_t &input);

static bool IsRawNode(const embedded_t &input);

#endif
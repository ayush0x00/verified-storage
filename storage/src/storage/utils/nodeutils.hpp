#ifndef PMT_NODE_UTILS_H
#define PMT_NODE_UTILS_H

#include <utils/alias.hpp>
#include <storage/utils/aliasadvance.hpp>
#include <storage/nodes/node.hpp>


static node_t DecodeNode(const buffer_t &input);

static node_t DecodeRawNode(const bufferarray_t &input);

static bool IsRawNode(const embedded_t &input);

#endif
#ifndef PMT_NODE_UTILS_H
#define PMT_NODE_UTILS_H

#include <persistent/alias.hpp>
#include <storage/utils/aliasadvance.hpp>
#include <storage/nodes/node.hpp>


static node_t DecodeNode(const buffer_t &input);

static node_t DecodeRawNode(const buffer_array_t &input);

static bool IsRawNode(const embedded_t &input);

#endif
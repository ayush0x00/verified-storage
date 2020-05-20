#ifndef PMT_NODE_UTILS_H
#define PMT_NODE_UTILS_H

#include <stdint.h>

#include "node.hpp"

static Node DecodeNode(const buffer_t &input);
static Node DecodeRawNode(const bufferarray_t &input);
static bool IsRawNode(const bufferarray_t &input);

#endif
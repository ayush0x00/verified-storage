#ifndef PMT_ALIAS_H
#define PMT_ALIAS_H

#include <vector>
#include <stdint.h>

#include "batchdbop.hpp"

using uint = unsigned int;

using Nibble = std::vector<uint>;

using Buffer = std::vector<uint64_t>;

using BufferArray = std::vector<std::vector<uint64_t>>;

using BatchDBOpArray = std::vector<BatchDBOp>;

#endif
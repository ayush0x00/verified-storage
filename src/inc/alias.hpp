#ifndef PMT_ALIAS_H
#define PMT_ALIAS_H

#include <vector>
#include <stdint.h>

#include "batchdbop.hpp"

using uint_t = unsigned int;

using nibble_t = std::vector<uint_t>;

using buffer_t = std::vector<uint64_t>;

using bufferarray_t = std::vector<std::vector<uint64_t>>;

using batchdboparray_t = std::vector<BatchDBOp>;

#endif
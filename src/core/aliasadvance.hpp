#ifndef PMT_ALIAS_ADVANCE_H
#define PMT_ALIAS_ADVANCE_H

#include <boost/variant.hpp>
#include <vector>

#include "alias.hpp"
#include "leaf.hpp"
#include "branch.hpp"
#include "extension.hpp"
#include "batchdbop.hpp"

using embedded_t = boost::variant<buffer_t, bufferarray_t>;

using batchdboparray_t = std::vector<BatchDBOp>;

using node_t = boost::variant<Node, Branch, Extension, Leaf>;

#endif
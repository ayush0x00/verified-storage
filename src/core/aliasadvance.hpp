#ifndef PMT_ALIAS_ADVANCE_H
#define PMT_ALIAS_ADVANCE_H

#include <boost/variant.hpp>
#include <vector>

#include "leaf.hpp"
#include "branch.hpp"
#include "extension.hpp"
#include "batchdbop.hpp"

using batchdboparray_t = std::vector<BatchDBOp>;

using node_t = boost::variant<Node, Branch, Extension, Leaf>;

#endif
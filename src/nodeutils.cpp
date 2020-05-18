#include "inc/node.hpp"

#include <iostream>

#include "rlp/inc/rlpdecode.hpp"
#include "inc/branch.hpp"
#include "inc/extension.hpp"
#include "inc/leaf.hpp"
#include "utils/nibbles.hpp"
#include "utils/hex.hpp"


Node DecodeNode(const std::vector<uint64_t> &input) {
    std::vector<std::vector<uint64_t>> decode_ = RLPDecoder::DecodeByteList(input);

    if(typeid(decode_[0]) != typeid(std::vector<uint64_t>)) {
        // Todo Throw error
        return Node();
    }
    return DecodeRawNode(decode_);
}

Node DecodeRawNode(const std::vector<std::vector<uint64_t>> &input) {
    if(input.size() == 17) {
        return Branch::FromBuffer(input);
    } else if(input.size() == 2) {
        std::vector<uint> nibbles_ = BufferToNibble(BytesToString(input[0]));
        if(IsTerminator(nibbles_)) {
            return Leaf(Leaf::DecodeKey(nibbles_), input[1]);
        }
        return Extension(Extension::DecodeKey(nibbles_), input[1]);
    } else {
        // Todo Throw invalid error
        return Node();
    }
}

bool IsRawNode(const std::array<std::vector<uint64_t>, 17> &input) {
    bool status = true;
    for (auto node : input) {
        if(typeid(node) != typeid(std::vector<uint64_t>)) {
            status = false;
            break;
        }
    }

    return status;
 }

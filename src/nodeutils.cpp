#include "inc/node.hpp"

#include <iostream>

#include "rlp/inc/rlpdecode.hpp"
#include "inc/branch.hpp"
#include "inc/extension.hpp"
#include "inc/leaf.hpp"
#include "utils/nibbles.hpp"
#include "utils/hex.hpp"


Node DecodeNode(const buffer_t &input) {
    bufferarray_t decode_ = RLPDecoder::DecodeByteList(input);

    if(typeid(decode_.at(0)) != typeid(buffer_t)) {
        // Todo Throw error
        return Node();
    }

    return DecodeRawNode(decode_);
}

Node DecodeRawNode(const bufferarray_t &input) {
    if(input.size() == 17) {
        return Branch::FromBuffer(input);
    } else if(input.size() == 2) {
        nibble_t nibbles_ = StringToNibble(BytesToString(input.at(0)));
        
        if(IsTerminator(nibbles_)) {
            return Leaf(Leaf::DecodeKey(nibbles_), input[1]);
        }

        return Extension(Extension::DecodeKey(nibbles_), input.at(1));
    } else {
        // Todo Throw invalid error
        return Node();
    }
}

bool IsRawNode(const bufferarray_t &input) {
    bool status = true;
    for (auto node : input) {
        if(typeid(node) != typeid(buffer_t)) {
            status = false;
            break;
        }
    }

    return status;
 }

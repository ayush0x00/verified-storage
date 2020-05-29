#include "nodeutils.hpp"

#include "branch.hpp"
#include "extension.hpp"
#include "leaf.hpp"
#include "nodetype.hpp"
#include "rlp/inc/rlpdecode.hpp"
#include "utils/nibbles.hpp"
#include "utils/hex.hpp"


node_t DecodeNode(const buffer_t &input) {
    embedded_t decode_ = RLPDecoder::DecodeByteList(input);

    if(decode_.which() != BUFFER_ARRAY) {
        // Todo Throw error
        return Node();
    }

    return DecodeRawNode(boost::get<bufferarray_t>(decode_));
}

node_t DecodeRawNode(const bufferarray_t &input) {
    node_t decoded_node_;
    
    nibble_t nibbles_;
    switch (input.size()) {
        case BRANCH_NODE_SIZE: // It's a branch node
            decoded_node_ = Branch::FromBuffer(input);
            break;
        case OTHER_NODE_SIZE: // It can be either leaf node or extension node
            nibbles_ = BufferToNibble(input.at(0));
            
            if(IsTerminator(nibbles_)) {
                // It's a leaf node
                decoded_node_ = Leaf(Leaf::DecodeKey(nibbles_), input.at(1));
            } else {
                // It's a branch node
                decoded_node_ = Extension(Extension::DecodeKey(nibbles_), input.at(1));
            }
            break;
        default:
            // Todo Throw invalid error and remode node assignment
            decoded_node_ = Node();
            break;
    }

    return decoded_node_;
}

bool IsRawNode(const embedded_t &input) {
    return input.which() == BUFFER_ARRAY && input.which() != BUFFER;
}

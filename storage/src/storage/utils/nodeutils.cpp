#include "nodeutils.hpp"

#include "branch.hpp"
#include "extension.hpp"
#include "leaf.hpp"
#include "nodetype.hpp"
#include "rlp/inc/rlpdecode.hpp"
#include "hex.hpp"
#include "nibbles.hpp"


node_t DecodeNode(const buffer_t &input) {
    embedded_t decode_ = RLPDecoder::DecodeByteList(input);

    if(decode_.which() != BUFFER_ARRAY) {
        // Todo Throw error
        return Node();
    }

    return DecodeRawNode(boost::get<buffer_array_t>(decode_));
}

node_t DecodeRawNode(const buffer_array_t &input) {
    node_t decoded_node_;
    
    nibble_t nibbles_;
    switch (input.size()) {
        case BRANCH_NODE_SIZE: // It's a branch node
            decoded_node_ = Branch::FromBuffer(input);
            break;
        case OTHER_NODE_SIZE: // It can be either leaf node or extension node
            nibbles_ = verified::utils::ByteToNibble(input.at(0));
            
            if(verified::utils::IsTerminator(nibbles_)) {
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

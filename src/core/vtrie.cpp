#include "vtrie.hpp"

#include "nodetype.hpp"
#include "constants.hpp"
#include "batchdbop.hpp"
#include "nodeutils.hpp"
#include "leaf.hpp"
#include "branch.hpp"
#include "extension.hpp"
#include "../utils/hex.hpp"
#include "../utils/nibbles.hpp"
#include "../keccak/keccak_buffer.hpp"

VTrie::VTrie() {
    is_defined_ = false;
    EMPTY_TRIE_ROOT_ = EmptyByte();
    root_ = EMPTY_TRIE_ROOT_;
    db_ = DBConnection(DEFAULT_DB_FILE);
}

VTrie::VTrie(const buffer_t &root) {
    EMPTY_TRIE_ROOT_ = EmptyByte();
    root_ = EMPTY_TRIE_ROOT_;
    db_ = DBConnection(DEFAULT_DB_FILE);
    if(root.size()) {
        SetRoot(root);
    }

    is_defined_ = true;
}

VTrie::VTrie(DBConnection &db, const buffer_t &root) {
    EMPTY_TRIE_ROOT_ = EmptyByte();
    db_ = !db ? db : DBConnection(DEFAULT_DB_FILE);
    root_ = EMPTY_TRIE_ROOT_;
    if(root.size()) {
        SetRoot(root);
    }

    is_defined_ = true;
}

buffer_t VTrie::GetRoot() {
    return root_;
}

void VTrie::Root(const buffer_t &root) {
    SetRoot(root);
}

void VTrie::SetRoot(const buffer_t &root) {
    root_ = root.size() ? root : EMPTY_TRIE_ROOT_;
}

bool VTrie::IsDefined() {
    return is_defined_;
}

void VTrie::IsDefined(const bool is_defined) {
    is_defined_ = is_defined;
}

// bool VTrie::operator!() {
//     return root_ == EMPTY_TRIE_ROOT_;
// }

void VTrie::PutNode(node_t &node) {
    buffer_t hash_;
    buffer_t serialized_;
    switch (node.which()) {
        case BRANCH_NODE:
            hash_ = boost::get<Branch>(node).Hash();
            serialized_ = boost::get<Branch>(node).Serialize();
            break;
        case EXTENSION_NODE:
            hash_ = boost::get<Extension>(node).Hash();
            serialized_ = boost::get<Extension>(node).Serialize();
            break;
        case LEAF_NODE:
            hash_ = boost::get<Leaf>(node).Hash();
            serialized_ = boost::get<Leaf>(node).Serialize();
            break;
        default:
            hash_ = boost::get<Node>(node).Hash();
            serialized_ = boost::get<Node>(node).Serialize();
            break;
    }

    db_.Put(hash_, serialized_);
}

void VTrie::CreateInitilNode(const buffer_t &key, const buffer_t &value) {
    Leaf new_node_ = Leaf(BufferToNibble(key), value);
    root_ = new_node_.Hash();
    // Create a variant object
    node_t node_ = new_node_;
    PutNode(node_);
}

bool VTrie::Delet(const buffer_t &key) {
    // Todo Look for the lock and add lock before starting this process
    bool status_ = false;
    Path path_ = FindPath(key);
    if(path_.GetNode().empty()) {
        DeleteNode(key, path_.GetStack());
        status_ = true;
    }
    // Todo release the lock

    return status_;
}

buffer_t VTrie::Select(const buffer_t &key) {
    Path path_ = FindPath(key);
    buffer_t value_;
    if(!path_.GetNode().empty() && path_.GetRemaining().size() == 0) {
        switch (path_.GetNode().which()) {
            case BRANCH_NODE:
                value_ = boost::get<Branch>(path_.GetNode()).GetValue();
                break;
            case EXTENSION_NODE:
                value_ = boost::get<Extension>(path_.GetNode()).GetValue();
                break;
            case LEAF_NODE:
                value_ = boost::get<Leaf>(path_.GetNode()).GetValue();
                break;
            default:
                value_ = boost::get<Node>(path_.GetNode()).GetValue();
                break;
        }
    }

    return value_;
}

bool VTrie::Insert(const buffer_t &key, const buffer_t &value) {
    return Put(key, value);
}

bool VTrie::Put(const buffer_t &key, const buffer_t &value) {
    bool status_ = false;
    if(value.empty() || BytesToString(value).empty()) {
        // If value is empty delete
        status_ = Delet(key);
    }

    // Todo Look for the lock and add lock before starting this process
    // Todo check for Keccak-256 hash of the RLP of null
    if(root_ == EmptyByte()) {
        // No root, initialize this trie
        CreateInitilNode(key, value);
        status_ = true;
    } else {
        // Search for the given key or it's nearest node
        Path path_ = FindPath(key);
        // Now Update
        UpdateNode(key, value, path_.GetRemaining(), path_.GetStack());
        status_ = true;
    }
    // Todo release the lock

    return status_;
}

Path VTrie::FindPath(const buffer_t &key) {
    std::vector<Node> stack_;
    nibble_t target_key_ = BufferToNibble(key);

    nibble_t key_reminder_ = Slice(target_key_, MatchingNibbleLength());
}

void VTrie::UpdateNode(const buffer_t &key, const buffer_t &value, const nibble_t &key_reminder, std::vector<node_t> &stack) {
    batchdboparray_t to_save_;
    
    node_t last_node_ = stack.back();
    stack.pop_back();

    nibble_t key_nibbles_ = BufferToNibble(key);
    // Check if last node is leaf and the key matches to this
    bool match_leaf_ = false;

    if(last_node_.which() == LEAF_NODE) {
        int leaf_ = 0;
        for(std::string::size_type i = 0; i < stack.size(); i++) {
            node_t node_ = stack.at(i);
            if(node_.which() == BRANCH_NODE) {
                leaf_++;
            } else {
                switch (node_.which()) {
                    case EXTENSION_NODE:
                        leaf_ += boost::get<Extension>(node_).GetKey().size();
                        break;
                    case LEAF_NODE:
                        leaf_ += boost::get<Leaf>(node_).GetKey().size();
                        break;   
                    default:
                        break;
                }
            }
        }

        nibble_t last_node_key_(key_nibbles_.begin() + leaf_, key_nibbles_.end());
        nibble_t leaf_key_ = boost::get<Leaf>(last_node_).GetKey();
        if(MatchingNibbleLength(leaf_key_,  last_node_key_) == leaf_key_.size() &&
            !key_reminder.size()) {
                match_leaf_ = true;
        }
    }

    if(match_leaf_) {
        // Update the found value
        boost::get<Leaf>(last_node_).SetValue(value);
        stack.push_back(last_node_);
    } else if(last_node_.which() == BRANCH_NODE) {
        stack.push_back(last_node_);
        if(key_reminder.size()) {
            // Todo Add extension to the branch node
            key_reminder.shift();
            const Leaf new_leaf_ = Leaf(key_reminder, value);
            stack.push_back(new_leaf_);
        } else {
            boost::get<Branch>(last_node_).SetValue(value);
        }
    } else {
        // Create a branch node
        nibble_t last_key_ = boost::get<Extension>(last_node_).GetKey();
        bool matching_length_ = MatchingNibbleLength(last_key_, key_reminder);
        Branch new_branch_ = Branch();

        // Create a new extension node
        if(matching_length_) {
            nibble_t existing_key_ = boost::get<Extension>(last_node_).GetKey();
            nibble_t new_node_key_(existing_key_.begin(), existing_key_.begin() + matching_length_);
            Extension new_ext_node_ = Extension(new_node_key_, value);
            stack.push_back(new_ext_node_);
            last_key_.Splice(0, matching_length_);
            key_reminder.Splice(0, matching_length_);
        }

        stack.push_back(new_branch_);

        if(last_key_.size()) {
            
        }
    }
    
}

VTrie VTrie::FromProof(const bufferarray_t &proof_nodes, VTrie &proof_trie) {
    batchdboparray_t op_stack_;
    
    KeccakBuffer keccak_buffer_ = KeccakBuffer();
    for(buffer_t node : proof_nodes) {
        buffer_t key_ = keccak_buffer_(node);
        BatchDBOp put_batch_ = BatchDBOp("put", key_, node);
        op_stack_.push_back(put_batch_);
    }

    if(!proof_trie.IsDefined()) {
        proof_trie = VTrie();
        if(op_stack_.at(0).GetKey().size()) {
            proof_trie.SetRoot(op_stack_.at(0).GetKey());
        }
    }

    proof_trie.db_.BatchProcess(op_stack_);

    return proof_trie;
}

bufferarray_t VTrie::Prove(VTrie &trie, const buffer_t &key) {
    Path path_ = trie.FindPath(key);
    bufferarray_t proof_;
    for(std::string::size_type i = 0; i < path_.GetStack().size(); i++) {
        node_t element_ = path_.GetStack().at(i);
        switch (element_.which()) {
            case BRANCH_NODE:
                proof_.push_back(boost::get<Branch>(element_).Serialize());
                break;
            case EXTENSION_NODE:
                proof_.push_back(boost::get<Extension>(element_).Serialize());
                break;
            case LEAF_NODE:
                proof_.push_back(boost::get<Leaf>(element_).Serialize());
                break;
            default:
                proof_.push_back(boost::get<Node>(element_).Serialize());
                break;
        }
    }

    return proof_;
}

buffer_t VTrie::VerifyProof(const buffer_t &root_hash, const buffer_t &key, const bufferarray_t &proof_nodes) {
    VTrie proof_trie_ = VTrie(root_hash);
    // Todo use custom exception here
    try {
        proof_trie_ = FromProof(proof_nodes, proof_trie_);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return proof_trie_.Select(key);
}

node_t VTrie::LookupNode(const bufferarray_t &node) {
    if(IsRawNode(node)) {
        return DecodeRawNode(node);
    }

    buffer_t value_ = db_.Get(node.at(0));
    Node found_node_;
    if(value_.size()) {
        found_node_ = DecodeNode(value_);
    }

    return found_node_;
}

void VTrie::FindValueNodes() {

}

void VTrie::FindDbNodes() {

}

void VTrie::WalkTrie(const buffer_t &root) {

}

void VTrie::SaveStack(const nibble_t &key, const std::vector<node_t> &stack, const batchdboparray_t &op_stack) {

}

void VTrie::DeleteNode(const buffer_t &key, const std::vector<node_t> &stack) {

}

bufferarray_t VTrie::FormatNode(const node_t &node, const bool top_level, const batchdboparray_t &op_stack, const bool remove) {

}

VTrie VTrie::Copy() {

}

void VTrie::Batch(const batchdboparray_t &op_stack) {

}

bool VTrie::CheckRoot(const buffer_t &root) {

}

buffer_t VTrie::Select(const buffer_t &root_hash, const buffer_t &key) {

}

bool VTrie::Update(const buffer_t &key, const buffer_t &value) {

}

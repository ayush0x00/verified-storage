#include "vtrie.hpp"

#include "nodetype.hpp"
#include "constants.hpp"
// #include "batchdbop.hpp"
#include "nodeutils.hpp"
// #include "leaf.hpp"
// #include "branch.hpp"
// #include "extension.hpp"
#include "hex.hpp"
#include "nibbles.hpp"
#include "keccak_buffer.hpp"

VTrie::VTrie() {
    _is_defined = false;
    _EMPTY_TRIE_ROOT = EmptyByte();
    _root = _EMPTY_TRIE_ROOT;
    _db = DBConnection(DEFAULT_DB_FILE);
}

VTrie::VTrie(const buffer_t &root) {
    _EMPTY_TRIE_ROOT = EmptyByte();
    _root = _EMPTY_TRIE_ROOT;
    _db = DBConnection(DEFAULT_DB_FILE);
    if(root.size()) {
        SetRoot(root);
    }

    _is_defined = true;
}

VTrie::VTrie(DBConnection &db, const buffer_t &root) {
    _EMPTY_TRIE_ROOT = EmptyByte();
    _db = !db ? db : DBConnection(DEFAULT_DB_FILE);
    _root = _EMPTY_TRIE_ROOT;
    if(root.size()) {
        SetRoot(root);
    }

    _is_defined = true;
}

buffer_t VTrie::GetRoot() {
    return _root;
}

void VTrie::Root(const buffer_t &root) {
    SetRoot(root);
}

void VTrie::SetRoot(const buffer_t &root) {
    _root = root.size() ? root : _EMPTY_TRIE_ROOT;
}

bool VTrie::IsDefined() {
    return _is_defined;
}

void VTrie::IsDefined(const bool is_defined) {
    _is_defined = is_defined;
}

DBConnection VTrie::GetDB() {
    return _db;
}

void VTrie::SetDB(const DBConnection &db) {
    _db = db;
}

// bool VTrie::operator!() {
//     return root_ == _EMPTY_TRIE_ROOT;
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

    GetDB().Put(hash_, serialized_);
}

void VTrie::CreateInitilNode(const buffer_t &key, const buffer_t &value) {
    Leaf new_node_ = Leaf(BufferToNibble(key), value);
    _root = new_node_.Hash();
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
    if(_root == EmptyByte()) {
        // No root, initialize this trie
        CreateInitilNode(key, value);
        status_ = true;
    } else {
        // Search for the given key or it's nearest node
        Path path_ = FindPath(key);
        // Now Update
        nibble_t remaining_ = path_.GetRemaining();
        std::vector<node_t> stack_ = path_.GetStack();
        UpdateNode(key, value, remaining_, stack_);
        status_ = true;
    }
    // Todo release the lock

    return status_;
}

void VTrie::UpdateNode(const buffer_t &key, const buffer_t &value, nibble_t &key_reminder, std::vector<node_t> &stack) {
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

            switch (node_.which()) {
                case BRANCH_NODE:
                    leaf_++;
                    break;
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
            // Add extension to the branch node
            key_reminder.erase(key_reminder.begin());
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

            last_key_.erase(last_key_.begin(), last_key_.begin() + matching_length_);
            key_reminder.erase(key_reminder.begin(), key_reminder.begin() + matching_length_);
        }

        stack.push_back(new_branch_);

        if(last_key_.size()) {
            const uint_t branch_key_ = last_key_.at(0);
            last_key_.erase(last_key_.begin());
            
            if(last_key_.size() || last_node_.which() == LEAF_NODE) {
                // Shrink extension of leaf
                boost::get<Leaf>(last_node_).SetKey(last_key_);
                const embedded_t farmatted_node_ = FormatNode(last_node_, to_save_, false);
                if(farmatted_node_.which() == BUFFER) {
                    new_branch_.SetBranch(branch_key_, boost::get<buffer_t>(farmatted_node_));
                } else {
                    // Todo Throw error
                }
            } else {
                // remove extension of attaching
                FormatNode(last_node_, to_save_, false, true);
                new_branch_.SetBranch(branch_key_, boost::get<Extension>(last_node_).GetValue());
            }
        } else {
            new_branch_.SetValue(boost::get<Branch>(last_node_).GetValue());
        }

        if(key_reminder.size()) {
            key_reminder.erase(key_reminder.begin());
            // Add leaf node to the branch node
            const Leaf new_leaf_node_ = Leaf(key_reminder, value);
            stack.push_back(new_leaf_node_);
        } else {
            new_branch_.SetValue(value);
        }
    }
    
    SaveStack(key_nibbles_, stack, to_save_);
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

    proof_trie.GetDB().BatchProcess(op_stack_);

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

node_t VTrie::LookupNode(const embedded_t &node) {
    node_t found_node_;
    if(IsRawNode(node)) {
        return DecodeRawNode(boost::get<bufferarray_t>(node));
    } else {
        buffer_t value_ = GetDB().Get(boost::get<buffer_t>(node));

        if(value_.size()) {
            found_node_ = DecodeNode(value_);
        }
    }

    return found_node_;
}

embedded_t VTrie::FormatNode(node_t &node, batchdboparray_t &op_stack, const bool top_level, const bool remove) {
    buffer_t rlp_node_;
    switch (node.which()) {
        case BRANCH_NODE:
            rlp_node_ = boost::get<Branch>(node).Serialize();
            break;
        case EXTENSION_NODE:
            rlp_node_ = boost::get<Extension>(node).Serialize();
            break;
        case LEAF_NODE:
            rlp_node_ = boost::get<Leaf>(node).Serialize();
            break;
        default:
            rlp_node_ = boost::get<Node>(node).Serialize();
            break;
    }
    
    if(rlp_node_.size() >= 32 || top_level) {
        const buffer_t hash_root_ = boost::get<Node>(node).Hash();
        BatchDBOp  batch_db__op_ = BatchDBOp("put", hash_root_, rlp_node_);
        op_stack.push_back(batch_db__op_);

        return hash_root_;
    }

    return boost::get<Node>(node).Raw();
}

void VTrie::SaveStack(nibble_t &key, std::vector<node_t> &stack, batchdboparray_t &op_stack) {
    buffer_t last_root_;
    while(stack.size()) {
        auto node_ = stack.back();
        stack.pop_back();

        switch (node_.which()) {
            case LEAF_NODE:
                nibble_t::iterator start_ = key.begin() + (key.size() - boost::get<Leaf>(node_).GetKey().size());
                nibble_t::iterator end_ = key.end();
                key.erase(start_, end_);
                break;
            case EXTENSION_NODE:
                nibble_t::iterator start_ = key.begin() + (key.size() - boost::get<Extension>(node_).GetKey().size());
                nibble_t::iterator end_ = key.end();
                key.erase(start_, end_);
                if(last_root_.size()) {
                    boost::get<Extension>(node_).SetValue(last_root_);
                }
                break;
            case BRANCH_NODE:
                if(last_root_.size()) {
                    const uint_t branch_key_ = key.back();
                    key.pop_back();
                    boost::get<Branch>(node_).SetBranch(branch_key_, last_root_);
                }
                break;
            default:
                // Todo Throw error
                break;
        }

        // Recheck this
        embedded_t formatted_root_ = FormatNode(node_, op_stack, stack.empty());
        switch (formatted_root_.which()) {
            case BUFFER:
                last_root_ = boost::get<buffer_t>(formatted_root_);
                break;
            case BUFFER_ARRAY:
                last_root_ = boost::get<bufferarray_t>(formatted_root_).at(0);
                break;
            default:
                // Todo throw error
                break;
        }
    }

    if(last_root_.size()) {
        SetRoot(last_root_);
    }

    Batch(op_stack);
}

void VTrie::DeleteNode(const buffer_t &key, const std::vector<node_t> &stack) {

}

VTrie VTrie::Copy() {
    DBConnection db_ = GetDB().Copy();
    buffer_t root_ = GetRoot();
    return VTrie(db_, root_);
}

void VTrie::Batch(const batchdboparray_t &op_stack) {
    GetDB().BatchProcess(op_stack);
}

bool VTrie::CheckRoot(const buffer_t &root) {
    bufferarray_t array_root_;
    array_root_.push_back(root);
    const node_t node_ = LookupNode(array_root_);
    return !node_.empty();
}

Path VTrie::FindPath(const buffer_t &key) {
    std::vector<node_t> stack_;
    nibble_t target_key_ = BufferToNibble(key);

    nibble_t key_reminder_ = Slice(target_key_, MatchingNibbleLength());
}

void VTrie::FindValueNodes() {

}

void VTrie::FindDbNodes() {

}

void VTrie::WalkTrie(const buffer_t &root) {

}

buffer_t VTrie::Select(const buffer_t &root_hash, const buffer_t &key) {

}

bool VTrie::Update(const buffer_t &key, const buffer_t &value) {

}

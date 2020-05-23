#include "vtrie.hpp"

#include "includes/nodetype.hpp"
#include "includes/constants.hpp"
#include "includes/batchdbop.hpp"
#include "includes/nodeutils.hpp"
#include "includes/leaf.hpp"
#include "includes/branch.hpp"
#include "includes/extension.hpp"
#include "utils/hex.hpp"
#include "utils/nibbles.hpp"
#include "keccak/keccak_buffer.hpp"

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

void VTrie::PutNode(Node &node) {
    buffer_t hash_ = node.Hash();
    buffer_t serialized_ = node.Serialize();
    db_.Put(hash_, serialized_);
}

void VTrie::CreateInitilNode(const buffer_t &key, const buffer_t &value) {
    Leaf new_node = Leaf(BufferToNibble(key), value);
    root_ = new_node.Hash()
    PutNode(new_node);
}

bool VTrie::Delet(const buffer_t &key) {
    // Todo Look for the lock and add lock before starting this process
    bool status_ = false;
    Path path_ = FindPath(key);
    if(path_.GetNode() != NULL) {
        DeleteNode(key, path_.GetStack())
        status_ = true;
    }
    // Todo release the lock

    return status_;
}

buffer_t VTrie::Select(const buffer_t &key) {
    Path path_ = FindPath(key);
    buffer_t value_;
    if(path_.GetNode() && path_.GetRemaining().size() == 0) {
        value_ = path_.GetNode().GetValue();
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
    std::stack<Node> stack_;
    nibble_t target_key_ = BufferToNibble(key);

    nibble_t key_reminder_ = Slice(target_key_, MatchingNibbleLength());
}

void VTrie::UpdateNode(const buffer_t &key, const buffer_t &value, const nibble_t &key_reminder, std::vector<Node> &stack) {
    batchdboparray_t to_save_;
    
    Node last_node_ = stack.back();
    stack.pop_back();

    nibble_t key_nibbles_ = BufferToNibble(key);
    bool match_leaf_ = false;

    if(last_node_.GetNodeType() == LEAF_NODE) {
        int leaf_ = 0;
        for(std::string::size_type i = 0; i < stack.size(); i++) {
            Node node_ = stack.at(i);
            if(node_.GetNodeType() == BRANCH_NODE) {
                leaf_++;
            } else {
                leaf_ += 
            }
            
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

bufferarray_t VTrie::Prove(const VTrie &trie, const buffer_t &key) {
    Path path_ = trie.FindPath(key);
    bufferarray_t proof_;
    for(Node element_ : path_.GetStack()) {
        proof_.push_back(element_.Serialize());
    }

    return proof_;
}

buffer_t VTrie::VerifyProof(const buffer_t &root_hash, const buffer_t &key, const bufferarray_t &proof_nodes) {
    VTrie proof_trie_ = VTrie(root_hash);
    // Todo use try catch here
    proof_trie_ = VTrie.FromProof(proof_nodes, proof_trie_);

    return proof_trie_.Select(key);
}

Node VTrie::LookupNode(const bufferarray_t &node) {
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

void VTrie::SaveStack(const nibble_t &key, const std::stack<Node> &stack, const batchdboparray_t &op_stack) {

}

void VTrie::DeleteNode(const buffer_t &key, const std::stack<Node> &stack) {

}

bufferarray_t VTrie::FormatNode(const Node &node, const bool top_level, const batchdboparray_t &op_stack, const bool remove) {

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

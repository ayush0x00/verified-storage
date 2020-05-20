#include "vtrie.hpp"

#include "utils/hex.hpp"
#include "inc/constants.inc"
#include "inc/batchdbop.hpp"
#include "keccak/keccak_buffer.hpp"
#include "inc/nodeutils.hpp"

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
            // proof_trie.root_ = op_stack_.at(0).GetKey();
        }
    }

    proof_trie.db_.BatchProcess(op_stack_);

    return proof_trie;
}

bufferarray_t VTrie::Prove(const VTrie &trie, const buffer_t &key) {
    // Todo Need to look into this stage
    Path stack_ = trie.FindPath(key);
}

buffer_t VTrie::VerifyProof(const buffer_t &root_hash, const buffer_t &key, const bufferarray_t &proof_nodes) {
    VTrie proof_trie_ = VTrie(root_hash);
    // Todo use try catch here
    proof_trie_ = VTrie.FromProof(proof_nodes, proof_trie_);

    return proof_trie_.Select(key);
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
    if(value.empty() || value.data() == '') {
        // If value is empty delete
        Delet(key);
    }

    if(root_ == EmptyByte()) {
        // No root, initialize this trie
        CreateInitilNode(key, value);
    } else {
        // Search for the given key or it's nearest node
        Path path_ = FindPath(key);
        // Now Update
        UpdateNode(key, value, path_.GetRemaining(), path_.GetStack());
    }
    

}

bool VTrie::Delet(const buffer_t &key) {
    bool status_ = false;
    Path path_ = FindPath(key);
    if(path_.GetNode() != NULL) {
        DeleteNode(key, path_.GetStack())
        status_ = true;
    }

    return status_;
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

void VTrie::PutNode(const Node &node) {

}

void VTrie::FindValueNodes() {

}

void VTrie::FindDbNodes() {

}

void VTrie::UpdateNode(const buffer_t &key, const buffer_t &value, const nibble_t &key_reminder, const Node stack[]) {

}

void VTrie::WalkTrie(const buffer_t &root) {

}

void VTrie::SaveStack(const nibble_t &key, const std::stack<Node> &stack, const batchdboparray_t &op_stack) {

}

void VTrie::DeleteNode(const buffer_t &key, const std::stack<Node> &stack) {

}

void VTrie::CreateInitilNode(const buffer_t &key, const buffer_t &value) {

}

bufferarray_t VTrie::FormatNode(const Node &node, const bool top_level, const batchdboparray_t &op_stack, const bool remove) {

}

Path VTrie::FindPath(const buffer_t &key) {

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

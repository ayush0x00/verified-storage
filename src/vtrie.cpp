#include "vtrie.hpp"

#include "utils/hex.hpp"
#include "inc/constants.inc"

VTrie::VTrie(DBConnection &db, const buffer_t &root) {
    EMPTY_TRIE_ROOT_ = EmptyByte();
    db_ = !db ? db : DBConnection(DEFAULT_DB_FILE);
    root_ = EMPTY_TRIE_ROOT_;
    if(root.size()) {
        SetRoot(root);
    }
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

Node VTrie::LookupNode(const bufferarray_t &node) {

}

void VTrie::PutNode(const Node &node) {

}

void VTrie::FindValueNodes() {

}

void VTrie::FindDbNodes() {

}

void VTrie::UpdateNode(const buffer_t &key, const buffer_t &value, const nibble_t &key_reminder, const Node stack[]) {

}

void VTrie::WalkTree(const buffer_t &root) {

}

void VTrie::SaveStack(const nibble_t &key, const std::stack<Node> &stack, const batchdboparray_t &op_stack) {

}

void VTrie::DeleteNode(const buffer_t &key, const Node stack[]) {

}

void VTrie::CreateInitilNode(const buffer_t &key, const buffer_t &value) {

}

bufferarray_t VTrie::FormatNode(const Node &node, const bool top_level, const batchdboparray_t &op_stack, const bool remove) {

}

VTrie VTrie::FromProof(const bufferarray_t &proof_nodes, const VTrie &proof_trie) {

}

bufferarray_t VTrie::Prove(const VTrie &trie, const buffer_t &key) {

}

buffer_t VTrie::VerifyProof(const buffer_t &root_hash, const buffer_t &key, const bufferarray_t &proof_nodes) {

}

Path VTrie::FindPath(const buffer_t &key) {

}

VTrie VTrie::Copy() {

}

void VTrie::Batch(const batchdboparray_t &op_stack) {

}

bool VTrie::CheckRoot(const buffer_t &root) {

}

buffer_t VTrie::Select(const buffer_t &key) {

}

buffer_t VTrie::Select(const buffer_t &root_hash, const buffer_t &key) {

}

bool VTrie::Insert(const buffer_t &key, const buffer_t &value) {

}

bool VTrie::Delet(const buffer_t &key) {

}

bool VTrie::Update(const buffer_t &key, const buffer_t &value) {

}

#include "vtrie.hpp"

#include "utils/hex.hpp"
#include "inc/constants.inc"

VTrie::VTrie(DBConnection &db, const Buffer &root) {
    EMPTY_TRIE_ROOT_ = EmptyByte();
    db_ = !db ? db : DBConnection(DEFAULT_DB_FILE);
    root_ = EMPTY_TRIE_ROOT_;
    if(root.size()) {
        SetRoot(root);
    }
}

Buffer VTrie::GetRoot() {
    return root_;
}

void VTrie::Root(const Buffer &root) {
    SetRoot(root);
}

void VTrie::SetRoot(const Buffer &root) {
    root_ = root.size() ? root : EMPTY_TRIE_ROOT_;
}

Node VTrie::LookupNode(const BufferArray &node) {

}

void VTrie::PutNode(const Node &node) {

}

void VTrie::FindValueNodes() {

}

void VTrie::FindDbNodes() {

}

void VTrie::UpdateNode(const Buffer &key, const Buffer &value, const Nibble &key_reminder, const Node stack[]) {

}

void VTrie::WalkTree(const Buffer &root) {

}

void VTrie::SaveStack(const Nibble &key, const std::stack<Node> &stack, const BatchDBOpArray &op_stack) {

}

void VTrie::DeleteNode(const Buffer &key, const Node stack[]) {

}

void VTrie::CreateInitilNode(const Buffer &key, const Buffer &value) {

}

BufferArray VTrie::FormatNode(const Node &node, const bool top_level, const BatchDBOpArray &op_stack, const bool remove) {

}

VTrie VTrie::FromProof(const BufferArray &proof_nodes, const VTrie &proof_trie) {

}

BufferArray VTrie::Prove(const VTrie &trie, const Buffer &key) {

}

Buffer VTrie::VerifyProof(const Buffer &root_hash, const Buffer &key, const BufferArray &proof_nodes) {

}

Path VTrie::FindPath(const Buffer &key) {

}

VTrie VTrie::Copy() {

}

void VTrie::Batch(const BatchDBOpArray &op_stack) {

}

bool VTrie::CheckRoot(const Buffer &root) {

}

Buffer VTrie::Select(const Buffer &key) {

}

Buffer VTrie::Select(const Buffer &root_hash, const Buffer &key) {

}

bool VTrie::Insert(const Buffer &key, const Buffer &value) {

}

bool VTrie::Delet(const Buffer &key) {

}

bool VTrie::Update(const Buffer &key, const Buffer &value) {

}

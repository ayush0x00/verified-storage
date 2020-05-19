#ifndef PMT_VTRIE_H
#define PMT_VTRIE_H

#include <stack>

#include "node.hpp"
#include "path.hpp"
#include "db.hpp"
#include "batchdbop.hpp"

class VTrie {
    private:
        Buffer EMPTY_TRIE_ROOT_;
        Buffer root_;
        DBConnection db_;
        // Todo Add Semaphore for locking the resource under processing

        Node LookupNode(const BufferArray &node);
        void PutNode(const Node &node);
        void FindValueNodes(); // Todo need to check what should be passed as parameter
        void FindDbNodes(); // Todo need to check what should be passed as parameter
        void UpdateNode(const Buffer &key, const Buffer &value, const Nibble &key_reminder, const Node stack[]);
        void WalkTree(const Buffer &root); // Todo need to check what should be passed as parameter
        void SaveStack(const Nibble &key, const std::stack<Node> &stack, const BatchDBOpArray &op_stack);
        void DeleteNode(const Buffer &key, const Node stack[]);
        void CreateInitilNode(const Buffer &key, const Buffer &value);
        BufferArray FormatNode(const Node &node, const bool top_level, const BatchDBOpArray &op_stack, const bool remove=false);

    public:
        // VTrie();
        // ~VTrie();

        VTrie(DBConnection &db, const Buffer &root);
        Buffer GetRoot();
        void Root(const Buffer &root);
        void SetRoot(const Buffer &root);

        VTrie FromProof(const BufferArray &proof_nodes, const VTrie &proof_trie);
        BufferArray Prove(const VTrie &trie, const Buffer &key);
        Buffer VerifyProof(const Buffer &root_hash, const Buffer &key, const BufferArray &proof_nodes);

        Path FindPath(const Buffer &key);
        VTrie Copy();
        void Batch(const BatchDBOpArray &op_stack);
        bool CheckRoot(const Buffer &root);
        
        Buffer Select(const Buffer &key);
        Buffer Select(const Buffer &root_hash, const Buffer &key);
        bool Insert(const Buffer &key, const Buffer &value);
        bool Delet(const Buffer &key);
        bool Update(const Buffer &key, const Buffer &value);
};

#endif

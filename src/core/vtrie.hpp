#ifndef PMT_VTRIE_H
#define PMT_VTRIE_H

#include <boost/variant.hpp>

#include "aliasadvance.hpp"
#include "node.hpp"
#include "leaf.hpp"
#include "branch.hpp"
#include "extension.hpp"
#include "path.hpp"
#include "db.hpp"
#include "batchdbop.hpp"

class VTrie {
    private:
        bool _is_defined;
        buffer_t _EMPTY_TRIE_ROOT;
        buffer_t _root;
        DBConnection _db;
        // Todo Add Semaphore for locking the resource under processing

        node_t LookupNode(const bufferarray_t &node);
        void PutNode(node_t &node);
        void FindValueNodes(); // Todo need to check what should be passed as parameter
        void FindDbNodes(); // Todo need to check what should be passed as parameter
        void UpdateNode(const buffer_t &key, const buffer_t &value, nibble_t &key_reminder, std::vector<node_t> &stack);
        void WalkTrie(const buffer_t &root); // Todo need to check what should be passed as parameter
        void SaveStack(nibble_t &key, std::vector<node_t> &stack, batchdboparray_t &op_stack);
        void DeleteNode(const buffer_t &key, const std::vector<node_t> &stack);
        void CreateInitilNode(const buffer_t &key, const buffer_t &value);
        bufferarray_t FormatNode(node_t &node, const bool top_level, batchdboparray_t &op_stack, const bool remove=false);

    public:
        VTrie();
        // ~VTrie();
        VTrie(const buffer_t &root);
        VTrie(DBConnection &db, const buffer_t &root);
        buffer_t GetRoot();
        void Root(const buffer_t &root);
        void SetRoot(const buffer_t &root);
        bool IsDefined();
        void IsDefined(const bool is_defined);
        DBConnection GetDB();
        void SetDB(const DBConnection &db);

        static VTrie FromProof(const bufferarray_t &proof_nodes, VTrie &proof_trie);
        bufferarray_t Prove(VTrie &trie, const buffer_t &key);
        buffer_t VerifyProof(const buffer_t &root_hash, const buffer_t &key, const bufferarray_t &proof_nodes);

        Path FindPath(const buffer_t &key);
        VTrie Copy();
        void Batch(const batchdboparray_t &op_stack);
        bool CheckRoot(const buffer_t &root);
        
        buffer_t Select(const buffer_t &key);
        buffer_t Select(const buffer_t &root_hash, const buffer_t &key);
        bool Put(const buffer_t &key, const buffer_t &value);
        bool Insert(const buffer_t &key, const buffer_t &value);
        bool Delet(const buffer_t &key);
        bool Update(const buffer_t &key, const buffer_t &value);

        // Operators
        // bool operator!();
};

#endif
